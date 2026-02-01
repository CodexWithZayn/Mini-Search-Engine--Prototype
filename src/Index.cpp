#include "Index.h"
#include "Tokenizer.h"

using namespace std;

IndexNode *Index::findWord(const string &word) {
  Node *cur = indexList.head;
  while (cur) {
    IndexNode *idx = (IndexNode *)cur->data;
    if (idx->word == word) {
      return idx;
    }
    cur = cur->next;
  }
  return nullptr;
}

LinkedList Index::searchWord(const string &word) {
  LinkedList results;
  IndexNode *idx = findWord(word);

  if (idx) {

    Node *cur = idx->docFrequencies.head;
    while (cur) {
      DocFrequency *df = (DocFrequency *)cur->data;
      results.addNode(new int(df->docId));
      cur = cur->next;
    }
  }

  return results;
}

LinkedList Index::searchPrefix(const string &prefix) {
  LinkedList results;
  Node *cur = indexList.head;

  while (cur) {
    IndexNode *idx = (IndexNode *)cur->data;

    if (idx->word.length() >= prefix.length() &&
        idx->word.substr(0, prefix.length()) == prefix) {

      Node *docNode = idx->docFrequencies.head;
      while (docNode) {
        DocFrequency *df = (DocFrequency *)docNode->data;

        // Check if docId already in results (avoid duplicates)
        bool found = false;
        Node *check = results.head;
        while (check) {
          int *existingId = (int *)check->data;
          if (*existingId == df->docId) {
            found = true;
            break;
          }
          check = check->next;
        }

        if (!found) {
          results.addNode(new int(df->docId));
        }
        docNode = docNode->next;
      }
    }
    cur = cur->next;
  }

  return results;
}

int Index::getWordFrequency(const string &word, int docId) {
  IndexNode *idx = findWord(word);
  if (idx) {
    DocFrequency *df = idx->findDoc(docId);
    if (df) {
      return df->frequency;
    }
  }
  return 0;
}

void Index::addDocument(int docId, const string &text) {

  LinkedList tokens = Tokenizer::tokenize(text);

  Node *tokenNode = tokens.head;
  while (tokenNode) {
    string *word = (string *)tokenNode->data;

    IndexNode *idx = findWord(*word);

    if (!idx) {
      idx = new IndexNode(*word);
      indexList.addNode(idx);
    }

    idx->addDocOccurrence(docId);

    tokenNode = tokenNode->next;
  }
}

void Index::removeDocument(int docId) {
  Node *cur = indexList.head;

  while (cur) {
    IndexNode *idx = (IndexNode *)cur->data;

    // Find and remove document from this word's list
    Node *docNode = idx->docFrequencies.head;
    while (docNode) {
      DocFrequency *df = (DocFrequency *)docNode->data;
      if (df->docId == docId) {
        idx->docFrequencies.removeNode(df);
        delete df;
        break;
      }
      docNode = docNode->next;
    }

    cur = cur->next;
  }
}