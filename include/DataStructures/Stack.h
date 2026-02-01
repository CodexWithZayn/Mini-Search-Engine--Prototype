#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>


using namespace std;

struct StackNode {
  string action; // Description of action, e.g., "Added Doc 5"
  int docId;     // ID associated with the action
  StackNode *next;

  StackNode(string act, int id) : action(act), docId(id), next(nullptr) {}
};

class Stack {
private:
  StackNode *top;

public:
  Stack();
  ~Stack();

  void push(string action, int docId);
  bool pop(string &action, int &docId); // Returns false if empty
  bool peek(string &action, int &docId);
  bool isEmpty();
  void displayStack(); // Helper to show history
};

#endif
