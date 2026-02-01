#include "LinkedList.h"
#include <iostream>

Node::Node(void* d, Node* n) : data(d), next(n) {}
Node::Node(void* d) : data(d), next(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void LinkedList::addNode(void* data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void LinkedList::removeNode(void* data) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr && current->data != data) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        return;
    }
    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;
    size--;
}

Node* LinkedList::findNode(void* data) {
    Node* current = head;
    while (current != nullptr && current->data != data) {
        current = current->next;
    }
    return current;
}

void LinkedList::printList() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

