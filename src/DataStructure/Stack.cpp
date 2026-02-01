#include "DataStructures/Stack.h"
#include "Colors.h"

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
  while (!isEmpty()) {
    string act;
    int id;
    pop(act, id);
  }
}

void Stack::push(string action, int docId) {
  StackNode *newNode = new StackNode(action, docId);
  newNode->next = top;
  top = newNode;
}

bool Stack::pop(string &action, int &docId) {
  if (isEmpty())
    return false;

  StackNode *temp = top;
  action = temp->action;
  docId = temp->docId;

  top = top->next;
  delete temp;
  return true;
}

bool Stack::peek(string &action, int &docId) {
  if (isEmpty())
    return false;
  action = top->action;
  docId = top->docId;
  return true;
}

bool Stack::isEmpty() { return top == nullptr; }

void Stack::displayStack() {
  if (isEmpty()) {
    cout << YELLOW << "  (Empty)" << RESET << endl;
    return;
  }
  StackNode *current = top;
  while (current) {
    cout << CYAN << "  [ " << current->action << " (ID: " << current->docId
         << ") ]" << RESET << endl;
    current = current->next;
  }
}
