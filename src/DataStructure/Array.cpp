#include "../../include/DataStructures/Array.h"

Array::Array(int initCapacity) {
  capacity = initCapacity;
  length = 0;
  data = new DocData[capacity];
}

Array::~Array() { delete[] data; }

void Array::resize(int newCapacity) {
  DocData *newData = new DocData[newCapacity];
  for (int i = 0; i < length; i++) {
    newData[i] = data[i];
  }
  delete[] data;
  data = newData;
  capacity = newCapacity;
}

void Array::push_back(DocData value) {
  if (length == capacity) {
    resize(capacity * 2);
  }
  data[length++] = value;
}

DocData Array::get(int index) const {
  if (index < 0 || index >= length) {
    throw out_of_range("Index out of bounds");
  }
  return data[index];
}

int Array::size() const { return length; }

bool Array::isEmpty() const { return length == 0; }

void Array::clear() {
  delete[] data;
  capacity = 2;
  length = 0;
  data = new DocData[capacity];
}
