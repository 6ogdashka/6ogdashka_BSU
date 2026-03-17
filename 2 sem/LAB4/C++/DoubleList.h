#ifndef DLIST
#define DLIST
#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoubleList {
private:

    Node* head;
    Node* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}

    DoubleList(const DoubleList&) = delete;
    DoubleList& operator=(const DoubleList&) = delete;

    ~DoubleList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif