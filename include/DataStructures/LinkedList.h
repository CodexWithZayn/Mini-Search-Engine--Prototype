#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    void* data; // can be of any type
    Node* next;

    Node(void* d, Node* n);
    Node(void* d);
};

class LinkedList {
public:
    Node* head;
    Node* tail;
    int size;
    
    // Basic operations
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList();
    void addNode(void* data);
    void removeNode(void* data);
    Node* findNode(void* data);
    void printList();
};

#endif