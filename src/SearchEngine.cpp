#include "SearchEngine.h"
#include "Tokenizer.h"
#include "UI.h"
#include <iomanip> // for std::setw
#include <iostream>
#include <string>

using namespace std;

SearchEngine::SearchEngine() : nextDocID(1) {}

// ==================== DOCUMENT MANAGEMENT ====================

void SearchEngine::addDocument(const string &title, const string &content,
                               bool isUndoable) {
  if (title.empty() || content.empty()) {
    UI::printError("Title and content cannot be empty.");
    return;
  }

  Document *doc = new Document(nextDocID, title, content);
  documents.addNode(doc);
  index.addDocument(nextDocID, content);

  docTree.insert(doc);

  if (isUndoable) {
    undoStack.push("Added: " + title, nextDocID);
  }

  UI::printSuccess("Document added successfully (ID: " + to_string(nextDocID) +
                   ")");
  nextDocID++;
}

Document *SearchEngine::findDocumentById(int id) {
  Node *current = documents.head;
  while (current != nullptr) {
    Document *doc = (Document *)current->data;
    if (doc->id == id) {
      return doc;
    }
    current = current->next;
  }
  return nullptr;
}

void SearchEngine::removeDocument(int id) {
  Document *doc = findDocumentById(id);
  if (!doc) {
    UI::printError("Document with ID " + to_string(id) + " not found.");
    return;
  }

  index.removeDocument(id);
  documents.removeNode(doc);
  delete doc;

  UI::printSuccess("Document " + to_string(id) + " removed successfully.");
}

void SearchEngine::updateDocument(int id, const string &newContent) {
  if (newContent.empty()) {
    UI::printError("New content cannot be empty.");
    return;
  }

  Document *doc = findDocumentById(id);
  if (!doc) {
    UI::printError("Document with ID " + to_string(id) + " not found.");
    return;
  }

  index.removeDocument(id);
  doc->content = newContent;
  doc->updated_at = time(nullptr);
  doc->accessCount++;
  index.addDocument(id, newContent);

  UI::printSuccess("Document " + to_string(id) + " updated successfully.");
}

void SearchEngine::displayAllDocuments() {
  Node *current = documents.head;

  if (!current) {
    UI::printWarning("No documents found in the system.");
    return;
  }

  UI::printTableStart();
  while (current != nullptr) {
    Document *doc = (Document *)current->data;
    UI::printTableRow(to_string(doc->id), doc->title);
    current = current->next;
  }
  UI::printTableEnd();
}

// ==================== SEARCH HELPERS ====================

void displayDocResult(Document *doc, string highlight = "") {
  if (!doc)
    return;
  UI::printResultCard(doc->title, doc->content, doc->id, highlight);
}

// ==================== BASIC SEARCH ====================

void SearchEngine::search(const string &keyword) {
  string word = "";
  for (char c : keyword) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      word += tolower(c);
  }

  if (word.empty()) {
    UI::printError("Invalid keyword.");
    return;
  }

  history.addSearch(word);

  cout << "\n"
       << MAGENTA << " [SEARCH RESULT] \"" << word << "\"" << RESET << endl;

  LinkedList results = index.searchWord(word);

  if (results.size == 0) {
    UI::printWarning("No documents found.");
    return;
  }

  Node *cur = results.head;
  while (cur) {
    int *docId = (int *)cur->data;
    Document *doc = findDocumentById(*docId);

    if (doc) {
      doc->accessCount++;
      displayDocResult(doc, word);
    }
    cur = cur->next;
  }
}

// ==================== MULTI-KEYWORD SEARCH ====================

LinkedList SearchEngine::intersect(LinkedList &list1, LinkedList &list2) {
  LinkedList result;
  Node *cur1 = list1.head;
  while (cur1) {
    int *id1 = (int *)cur1->data;
    Node *cur2 = list2.head;
    while (cur2) {
      int *id2 = (int *)cur2->data;
      if (*id1 == *id2) {
        result.addNode(new int(*id1));
        break;
      }
      cur2 = cur2->next;
    }
    cur1 = cur1->next;
  }
  return result;
}

void SearchEngine::searchMultiple(const string &keywords) {
  LinkedList tokens = Tokenizer::tokenize(keywords);

  if (!tokens.head) {
    UI::printError("No valid keywords provided.");
    return;
  }

  cout << "\n"
       << MAGENTA << " [MULTI-KEYWORD SEARCH] \"" << keywords << "\"" << RESET
       << endl;

  Node *first = tokens.head;
  string *word1 = (string *)first->data;
  LinkedList results = index.searchWord(*word1);
  history.addSearch(*word1);

  Node *cur = first->next;
  while (cur) {
    string *word = (string *)cur->data;
    LinkedList wordResults = index.searchWord(*word);
    history.addSearch(*word);
    results = intersect(results, wordResults);
    cur = cur->next;
  }

  if (results.size == 0) {
    UI::printWarning("No documents match ALL keywords.");
    return;
  }

  cout << GREEN << " Found " << results.size
       << " matching document(s):" << RESET << endl;

  Node *resCur = results.head;
  while (resCur) {
    int *docId = (int *)resCur->data;
    Document *doc = findDocumentById(*docId);
    if (doc) {
      doc->accessCount++;
      displayDocResult(doc);
    }
    resCur = resCur->next;
  }
}

// ==================== PREFIX SEARCH ====================

void SearchEngine::searchPrefix(const string &prefix) {
  string normalizedPrefix = "";
  for (char c : prefix) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      normalizedPrefix += tolower(c);
  }

  if (normalizedPrefix.empty()) {
    UI::printError("Invalid prefix.");
    return;
  }

  history.addSearch(normalizedPrefix + "*");

  cout << "\n"
       << MAGENTA << " [PREFIX SEARCH] \"" << normalizedPrefix << "...\""
       << RESET << endl;

  LinkedList results = index.searchPrefix(normalizedPrefix);

  if (results.size == 0) {
    UI::printWarning("No documents found.");
    return;
  }

  cout << GREEN << " Found " << results.size
       << " matching document(s):" << RESET << endl;

  Node *cur = results.head;
  while (cur) {
    int *docId = (int *)cur->data;
    Document *doc = findDocumentById(*docId);
    if (doc) {
      doc->accessCount++;
      displayDocResult(doc);
    }
    cur = cur->next;
  }
}

// ==================== RANKED SEARCH ====================

void SearchEngine::sortByScore(Document **docs, int *scores, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (scores[j] < scores[j + 1]) {
        int tempScore = scores[j];
        scores[j] = scores[j + 1];
        scores[j + 1] = tempScore;
        Document *tempDoc = docs[j];
        docs[j] = docs[j + 1];
        docs[j + 1] = tempDoc;
      }
    }
  }
}

void SearchEngine::searchRanked(const string &keyword) {
  string word = "";
  for (char c : keyword) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      word += tolower(c);
  }

  if (word.empty()) {
    UI::printError("Invalid keyword.");
    return;
  }

  history.addSearch(word);

  cout << "\n"
       << MAGENTA << " [RANKED BY FREQUENCY] \"" << word << "\"" << RESET
       << endl;

  LinkedList results = index.searchWord(word);

  if (results.size == 0) {
    UI::printWarning("No documents found.");
    return;
  }

  int size = results.size;
  Document **docs = new Document *[size];
  int *scores = new int[size];

  Node *cur = results.head;
  int i = 0;
  while (cur) {
    int *docId = (int *)cur->data;
    docs[i] = findDocumentById(*docId);
    scores[i] = index.getWordFrequency(word, *docId);
    i++;
    cur = cur->next;
  }

  sortByScore(docs, scores, size);

  for (int i = 0; i < size; i++) {
    if (docs[i]) {
      docs[i]->accessCount++;
      cout << "\n"
           << YELLOW << " Rank #" << (i + 1) << RESET << " (Freq: " << scores[i]
           << ")" << endl;
      displayDocResult(docs[i]);
    }
  }

  delete[] docs;
  delete[] scores;
}

void SearchEngine::searchRankedByRecency(const string &keyword) {
  string word = "";
  for (char c : keyword) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      word += tolower(c);
  }

  if (word.empty()) {
    UI::printError("Invalid keyword.");
    return;
  }

  history.addSearch(word);

  cout << "\n"
       << MAGENTA << " [RANKED BY RECENCY] \"" << word << "\"" << RESET << endl;

  LinkedList results = index.searchWord(word);

  if (results.size == 0) {
    UI::printWarning("No documents found.");
    return;
  }

  int size = results.size;
  Document **docs = new Document *[size];
  int *scores = new int[size];

  Node *cur = results.head;
  int i = 0;
  while (cur) {
    int *docId = (int *)cur->data;
    docs[i] = findDocumentById(*docId);
    scores[i] = (int)docs[i]->updated_at;
    i++;
    cur = cur->next;
  }

  sortByScore(docs, scores, size);

  for (int i = 0; i < size; i++) {
    if (docs[i]) {
      docs[i]->accessCount++;
      cout << "\n" << YELLOW << " Rank #" << (i + 1) << RESET << endl;
      displayDocResult(docs[i]);
    }
  }

  delete[] docs;
  delete[] scores;
}

void SearchEngine::searchRankedByAccess(const string &keyword) {
  string word = "";
  for (char c : keyword) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      word += tolower(c);
  }

  if (word.empty()) {
    UI::printError("Invalid keyword.");
    return;
  }

  history.addSearch(word);

  cout << "\n"
       << MAGENTA << " [RANKED BY ACCESS] \"" << word << "\"" << RESET << endl;

  LinkedList results = index.searchWord(word);

  if (results.size == 0) {
    UI::printWarning("No documents found.");
    return;
  }

  int size = results.size;
  Document **docs = new Document *[size];
  int *scores = new int[size];

  Node *cur = results.head;
  int i = 0;
  while (cur) {
    int *docId = (int *)cur->data;
    docs[i] = findDocumentById(*docId);
    scores[i] = docs[i]->accessCount;
    i++;
    cur = cur->next;
  }

  sortByScore(docs, scores, size);

  for (int i = 0; i < size; i++) {
    if (docs[i]) {
      docs[i]->accessCount++;
      cout << "\n"
           << YELLOW << " Rank #" << (i + 1) << RESET
           << " (Accesses: " << scores[i] << ")" << endl;
      displayDocResult(docs[i]);
    }
  }

  delete[] docs;
  delete[] scores;
}

// ==================== SEARCH ANALYTICS ====================

void SearchEngine::displaySearchHistory() { history.displayHistory(); }

void SearchEngine::displayTopSearches(int n) {
  if (n <= 0) {
    UI::printError("Number must be positive.");
    return;
  }
  history.displayTopSearches(n);
}

int SearchEngine::getTotalSearchCount() { return history.getTotalSearches(); }

int SearchEngine::getNextDocID() { return nextDocID; }

string SearchEngine::getTopSearchTerm() { return history.getTopSearchTerm(); }

// ==================== DS DEMOS ====================

void SearchEngine::addToQueue(const string &title, const string &content) {
  indexQueue.enqueue(title, content);
  UI::printSuccess("Document added to Index Queue. (Pending Processing)");
}

void SearchEngine::processQueue() {
  if (indexQueue.isEmpty()) {
    UI::printWarning("Queue is empty. Nothing to process.");
    return;
  }

  UI::printSuccess("Processing Index Queue...");
  string title, content;
  int count = 0;
  while (indexQueue.dequeue(title, content)) {
    addDocument(title, content);
    count++;
  }
  UI::printSuccess("Processed " + to_string(count) + " queued documents.");
}

void SearchEngine::undoLastAction() {
  if (undoStack.isEmpty()) {
    UI::printWarning("Undo Stack is empty. Nothing to undo.");
    return;
  }

  string action;
  int docId;
  undoStack.pop(action, docId);

  cout << YELLOW << " Undoing action: " << action << " (ID: " << docId << ")"
       << RESET << endl;
  removeDocument(docId);
}

void SearchEngine::displaySortedDocuments() { docTree.displayTreeGraphical(); }
