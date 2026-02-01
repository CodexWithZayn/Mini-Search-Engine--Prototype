#include "DataStructures/Queue.h"
#include "Colors.h"

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
  while (!isEmpty()) {
    string t, c;
    dequeue(t, c);
  }
}

void Queue::enqueue(string title, string content) {
  QueueNode *newNode = new QueueNode(title, content);
  if (isEmpty()) {
    front = rear = newNode;
  } else {
    rear->next = newNode;
    rear = newNode;
  }
}

bool Queue::dequeue(string &title, string &content) {
  if (isEmpty())
    return false;

  QueueNode *temp = front;
  title = temp->title;
  content = temp->content;

  front = front->next;
  if (front == nullptr) {
    rear = nullptr;
  }
  delete temp;
  return true;
}

bool Queue::isEmpty() { return front == nullptr; }

void Queue::displayQueue() {
  if (isEmpty()) {
    cout << YELLOW << "  (Empty)" << RESET << endl;
    return;
  }
  QueueNode *current = front;
  int i = 1;
  while (current) {
    cout << CYAN << "  " << i++ << ". " << current->title << RESET << endl;
    current = current->next;
  }
}
