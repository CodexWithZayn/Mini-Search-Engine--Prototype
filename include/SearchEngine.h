#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "DataStructures/BST.h"
#include "DataStructures/LinkedList.h"
#include "DataStructures/Queue.h"
#include "DataStructures/Stack.h"
#include "Document.h"
#include "Index.h"
#include "SearchHistory.h"

class SearchEngine {
private:
  LinkedList documents;
  Index index;
  SearchHistory history;
  int nextDocID;

  // New Data Structures
  Stack undoStack;
  Queue indexQueue;
  BST docTree;

  // Helper: intersect two LinkedLists of int* (doc IDs)
  LinkedList intersect(LinkedList &list1, LinkedList &list2);

  // Helper: sort documents by score using bubble sort
  void sortByScore(Document **docs, int *scores, int size);

public:
  SearchEngine();

  // === Document Management ===
  void addDocument(const string &title, const string &content,
                   bool isUndoable = true);
  void removeDocument(int id);
  void updateDocument(int id, const string &newContent);
  Document *findDocumentById(int id);
  void displayAllDocuments();

  // === DS Demos ===
  void addToQueue(const string &title, const string &content);
  void processQueue();
  void undoLastAction();
  void displaySortedDocuments();

  // === Search Functionality ===
  void search(const string &keyword);          // single keyword
  void searchMultiple(const string &keywords); // multiple keywords (AND)
  void searchPrefix(const string &prefix);     // prefix/partial search

  // === Ranked Search ===
  void searchRanked(const string &keyword);          // ranked by frequency
  void searchRankedByRecency(const string &keyword); // ranked by update time
  void searchRankedByAccess(const string &keyword);  // ranked by access count

  // === Search Analytics ===
  void displaySearchHistory();
  void displayTopSearches(int n);
  int getTotalSearchCount();
  int getNextDocID();
  string getTopSearchTerm();
};

#endif