#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <string>


using namespace std;

// Define specific data structure for the Array to handle
struct DocData {
  string title;
  string content;
};

class Array {
private:
  DocData *data;
  int capacity;
  int length;

  void resize(int newCapacity);

public:
  Array(int initCapacity = 2);
  ~Array();

  void push_back(DocData value);
  DocData get(int index) const;
  int size() const;
  bool isEmpty() const;
  void clear();
};

#endif
