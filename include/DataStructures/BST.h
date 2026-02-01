#ifndef BST_H
#define BST_H

#include "Document.h"
#include <iostream>

using namespace std;

struct BSTNode {
  Document *doc;
  BSTNode *left;
  BSTNode *right;

  BSTNode(Document *d) : doc(d), left(nullptr), right(nullptr) {}
};

class BST {
private:
  BSTNode *root;

  void insert(BSTNode *&node, Document *doc);
  void inOrder(BSTNode *node);
  void destroy(BSTNode *node);
  // Graphical Helper
  void printTree(BSTNode *node, string prefix, bool isLeft);

public:
  BST();
  ~BST();

  void insert(Document *doc);
  void displayInOrder();
  void displayTreeGraphical(); // New Graphical Display
  void clear();
};

#endif
