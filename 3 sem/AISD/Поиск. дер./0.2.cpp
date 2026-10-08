#include <fstream>
#include <string>

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;

    Node(int value, Node* parent_ = nullptr) : data(value), parent(parent_), left(nullptr), right(nullptr) {}
};

std::ofstream out("output.txt");

void TryRightDelete(Node*& BinTree, Node* current, int value) {
    if (current != nullptr) {
        if (current->data == value) {
            if (current->left == nullptr && current->right == nullptr) {
                if (current->parent != nullptr) {
                    if (current->parent->left == current) {
                        current->parent->left = nullptr;
                    } else {
                        current->parent->right = nullptr;
                    }
                } else {
                    BinTree = nullptr;
                }
                delete current;
                return;
            }

            if (current->left == nullptr || current->right == nullptr) {
                Node* child = (current->left != nullptr) ? current->left : current->right;

                if (current->parent != nullptr) {
                    if (current->parent->left == current) {
                        current->parent->left = child;
                    } else {
                        current->parent->right = child;
                    }
                } else {
                    BinTree = child;
                }
                
                if (child != nullptr) {
                    child->parent = current->parent;
                }
                delete current;
                return;
            } else {
                Node* buff = current->right;

                if (buff->left == nullptr) {
                    current->data = buff->data;
                    current->right = buff->right;
                    if (buff->right != nullptr) {
                        buff->right->parent = current;
                    }
                    delete buff;
                    return;
                } else {
                    while (buff->left != nullptr) {
                        buff = buff->left;
                    }
                    current->data = buff->data;
                    if (buff->parent != nullptr) {
                        buff->parent->left = buff->right;
                    }
                    if (buff->right != nullptr) {
                        buff->right->parent = buff->parent;
                    }
                    delete buff;
                    return;
                }
            }
        }
        if (value < current->data) TryRightDelete(BinTree, current->left, value);
        else TryRightDelete(BinTree, current->right, value);
    }
}

void Left(Node* current) {
    if (current != nullptr) {
        out << current->data << "\n";
        Left(current->left);
        Left(current->right);
    }
}

int main() {
    std::ifstream in("input.txt");

    int value;
    in >> value;
    
    std::string Balt;
    std::getline(in, Balt);

    int n;
    in >> n;

    Node* BinTree = new Node(n);

    while (in >> n) {
        Node* current = BinTree;
        while (current != nullptr) {
            if (n > current->data) {
                if (current->right == nullptr) {
                    current->right = new Node(n, current);
                    break;
                } else {
                    current = current->right;
                }
            } else if (n < current->data) {
                if (current->left == nullptr) {
                    current->left = new Node(n, current);
                    break;
                } else {
                    current = current->left;
                }
            } else {
                break;
            }
        }
    }

    TryRightDelete(BinTree, BinTree, value);    
    Left(BinTree);

    return 0;
}