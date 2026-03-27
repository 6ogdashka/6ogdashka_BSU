#ifndef LIST
#define LIST
#include <iostream>
#include <cstring>

struct SNode {
    char* data_type;
    SNode* next;

    SNode(const char* str) {
        data_type = new char[std::strlen(str) + 1];
        std::strcpy(data_type, str);
        next = nullptr;
    }

    ~SNode() {
        delete[] data_type;
    }
};

class List {
private:
    SNode* head;

public:
    List() : head(nullptr) {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    ~List() {
        SNode* current = head;
        while (current != nullptr) {
            SNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(const char* str, int index = -1) {
        SNode* newNode = new SNode(str);

        if (index < 0) {
            if (head == nullptr) {
                head = newNode;
            } else {
                SNode* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            return;
        }

        if (head == nullptr) {
            head = newNode;
            return;
        }

        SNode* current = head;
        int i = 0;
        while (i < index && current != nullptr) {
            current = current->next;
            i++;
        }

        if (current == nullptr) {
            current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void print() const {
        SNode* current = head;
        while (current != nullptr) {
            std::cout << current->data_type;
            if (current->next != nullptr) std::cout << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif