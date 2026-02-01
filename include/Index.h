#ifndef INDEX_H
#define INDEX_H

#include "DataStructures/IndexNode.h"
#include "DataStructures/LinkedList.h"
#include "Tokenizer.h"
#include <string>


using namespace std;

class Index {
private:
  LinkedList indexList; // stores IndexNode*

public:
  // Add document to index
  void addDocument(int docId, const string &text);

  // Remove document from index (cleanup)
  void removeDocument(int docId);

  // Search for exact word match
  LinkedList searchWord(const string &word);

  // Search for words starting with prefix
  LinkedList searchPrefix(const string &prefix);

  // Get frequency of word in a document
  int getWordFrequency(const string &word, int docId);

  // Find IndexNode for a word
  IndexNode *findWord(const string &word);
};

#endif
