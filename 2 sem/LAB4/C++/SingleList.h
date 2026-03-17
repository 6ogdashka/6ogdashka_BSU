#ifndef LIST
#define LIST
#include <iostream>
#include <cstring>

struct Node {
    char* data;
    Node* next;

    Node(const char* str) {
        data = new char[std::strlen(str) + 1];
        std::strcpy(data, str);
        next = nullptr;
    }

    ~Node() {
        delete[] data;
    }
};

class List {
private:
    Node* head;

public:
    List() : head(nullptr) {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(const char* str) {
        Node* newNode = new Node(str);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
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