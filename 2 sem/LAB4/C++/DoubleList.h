#ifndef DLIST
#define DLIST
#include <iostream>

struct DNode {
    int data;
    DNode* next;
    DNode* prev;

    DNode(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoubleList {
private:

    DNode* head;
    DNode* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}

    DoubleList(const DoubleList&) = delete;
    DoubleList& operator=(const DoubleList&) = delete;

    ~DoubleList() {
        DNode* current = head;
        while (current != nullptr) {
            DNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(int value) {
        DNode* newNode = new DNode(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void Delete() {
        int index = 0;
        DNode* current = head;
        while (current != nullptr) {
            if (index % 2 == 0) {
                DNode* toDelete = current;
                DNode* nextNode = current->next;
                if (toDelete->prev) {
                    toDelete->prev->next = nextNode;
                } else {
                    head = nextNode;
                }
                if (nextNode) {
                    nextNode->prev = toDelete->prev;
                } else {
                    tail = toDelete->prev;
                }
                delete toDelete;
                current = nextNode;
                index++;
            } else {
                current = current->next;
                index++;
            }
        }
    }

    void print() const {
        DNode* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif