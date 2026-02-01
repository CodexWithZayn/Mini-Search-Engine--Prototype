#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>


using namespace std;

struct QueueNode {
  string title;
  string content;
  QueueNode *next;

  QueueNode(string t, string c) : title(t), content(c), next(nullptr) {}
};

class Queue {
private:
  QueueNode *front;
  QueueNode *rear;

public:
  Queue();
  ~Queue();

  void enqueue(string title, string content);
  bool dequeue(string &title, string &content);
  bool isEmpty();
  void displayQueue();
};

#endif
