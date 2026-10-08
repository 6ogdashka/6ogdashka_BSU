#include <fstream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

std::ofstream out ("output.txt");

void Left(Node* current) {
    if (current != nullptr) {
    out << current->data << "\n";
    Left(current->left);
    Left(current->right);
    }
}

int main() {

    std::ifstream in("input.txt");
    int n;
    in >> n;
    Node BinTree(n);

    while (in >> n) {
        Node* current = &BinTree;
        while (current != nullptr) {
            if (n > current->data) {
                if (current->right == nullptr) {
                    Node* buff = new Node(n);
                    current->right = buff;
                    break;
                } else {
                    current = current->right;
                }
            } else if (n < current->data) {
                if (current->left == nullptr) {
                    Node* buff = new Node(n);
                    current->left = buff;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                break;
            }
        }
    }

    Left(&BinTree);

}