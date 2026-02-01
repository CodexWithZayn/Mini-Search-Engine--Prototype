#include "DataStructures/IndexNode.h"

DocFrequency::DocFrequency(int id) : docId(id), frequency(1) {}

IndexNode::IndexNode(std::string w) : word(w) {}

DocFrequency *IndexNode::findDoc(int docId) {
  Node *cur = docFrequencies.head;
  while (cur) {
    DocFrequency *df = (DocFrequency *)cur->data;
    if (df->docId == docId) {
      return df;
    }
    cur = cur->next;
  }
  return nullptr;
}

void IndexNode::addDocOccurrence(int docId) {
  DocFrequency *existing = findDoc(docId);
  if (existing) {
    existing->frequency++; // word appears again in same doc
  } else {
    DocFrequency *newDoc = new DocFrequency(docId);
    docFrequencies.addNode(newDoc);
  }
}