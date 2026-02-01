#include "DataStructures/BST.h"
#include "Colors.h"
#include "UI.h"

BST::BST() : root(nullptr) {}

BST::~BST() { clear(); }

void BST::clear() {
  destroy(root);
  root = nullptr;
}

void BST::destroy(BSTNode *node) {
  if (node) {
    destroy(node->left);
    destroy(node->right);
    delete node; // We do NOT delete the Document* here, as it's owned by
                 // LinkedList/SearchEngine
  }
}

void BST::insert(Document *doc) { insert(root, doc); }

void BST::insert(BSTNode *&node, Document *doc) {
  if (node == nullptr) {
    node = new BSTNode(doc);
  } else if (doc->id < node->doc->id) {
    insert(node->left, doc);
  } else {
    insert(node->right, doc);
  }
}

void BST::displayInOrder() {
  if (root == nullptr) {
    cout << YELLOW << "  (Empty Tree)" << RESET << endl;
    return;
  }
  UI::printTableStart();
  inOrder(root);
  UI::printTableEnd();
}

void BST::inOrder(BSTNode *node) {
  if (node) {
    inOrder(node->left);
    UI::printTableRow(to_string(node->doc->id), node->doc->title);
    inOrder(node->right);
  }
}

// ==================== GRAPHICAL DISPLAY ====================

void BST::displayTreeGraphical() {
  if (root == nullptr) {
    cout << YELLOW << "  (Empty Tree)" << RESET << endl;
    return;
  }
  cout << endl;
  printTree(root, "", false);
  cout << endl;
}

void BST::printTree(BSTNode *node, string prefix, bool isLeft) {
  if (node == nullptr)
    return;

  cout << CYAN << prefix;
  cout << (isLeft ? "|-- " : "|-- ");

  cout << BOLD << WHITE << "[ID:" << node->doc->id << "] " << RESET
       << node->doc->title.substr(0, 20) << endl;

  printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
  printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
}
