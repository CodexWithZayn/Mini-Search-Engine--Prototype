#ifndef INDEXNODE_H
#define INDEXNODE_H

#include "LinkedList.h"
#include <string>

// Stores document ID and word frequency in that document
class DocFrequency {
public:
  int docId;
  int frequency; // how many times word appears in this doc

  DocFrequency(int id);
};

// Stores a word and all documents containing it
class IndexNode {
public:
  std::string word;
  LinkedList docFrequencies; // stores DocFrequency*

  IndexNode(std::string w);

  // Find DocFrequency for a specific document
  DocFrequency *findDoc(int docId);

  // Add or increment frequency for a document
  void addDocOccurrence(int docId);
};

#endif