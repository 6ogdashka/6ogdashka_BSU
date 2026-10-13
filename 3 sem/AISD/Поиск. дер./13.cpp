#include <algorithm>
#include <fstream>
#include <vector>

struct Node {
    int data;
    Node* parent;
    int way;
    Node* left;
    Node* right;
    bool inWay = false;

    Node(int value, Node* parent_ = nullptr) : data(value), parent(parent_), way{}, left(nullptr), right(nullptr) {}
};

std::ofstream out("tst.out");

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

bool GoRight(Node* current) {
    int LeftWay  = (current->left  != nullptr) ? current->left->way  : -1;
    int RightWay = (current->right != nullptr) ? current->right->way : -1;

    if (RightWay != LeftWay)
        return RightWay > LeftWay;

    if (current->left  == nullptr) return true;
    if (current->right == nullptr) return false;
    return current->right->data < current->left->data;
}

void FindStart(Node* current, Node*& result) {
    if (current == nullptr) return;

    current->inWay = true;

    if (current->left == nullptr && current->right == nullptr) {
        result = current;
        return;
    }

    if (GoRight(current))
        FindStart(current->right, result);
    else
        FindStart(current->left, result);
}

void FindFinish(Node* current, Node*& result) {
    if (current == nullptr) return;

    current->inWay = true;

    if (current->left == nullptr && current->right == nullptr) {
        result = current;
        return;
    }

    if (GoRight(current))
        FindFinish(current->right, result);
    else
        FindFinish(current->left, result);
}

void LeftFind(Node* current,Node* result,int current_max = 0) {
    if (current != nullptr) {
        if ( current->way > result->way) {
            result = current;
        }
        LeftFind(current->left, result, result->way);
        LeftFind(current->right, result, result->way);
    }
}

int LeftWay(Node* node) {
    if (node == nullptr) {
        return -1;
    }

    int leftHigh = LeftWay(node->left);
    int rightHigh = LeftWay(node->right);

    int left = (node->left != nullptr) ? leftHigh + 1 : 0;
    int right = (node->right != nullptr) ? rightHigh + 1 : 0;

    node->way = left + right;

    if (node->left != nullptr && node->right != nullptr) {
        node->way -= 1;
    }

    return std::max(left, right);
}

void LeftWayBuild(Node* current, std::vector<int>& result) {
    if ( current != nullptr) {
        LeftWayBuild(current->left, result);
        if ( current->inWay == true) {
            result.push_back(current->data);
        }
        LeftWayBuild(current->right,result);
    }
}

int main() {
    std::ifstream in("tst.in");

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

    LeftWay(BinTree);
    Node* result = BinTree;
    Node* start = result;
    Node* finish;
    LeftFind(BinTree,result);
    out << result->data << " " << result->way << "\n\n";
    result->inWay = true;
    FindStart(result->left, start);
    FindFinish(result->right, finish);
    std::vector<int> HalfWay{};
    LeftWayBuild(BinTree,HalfWay);
    if ( start != result) {
        HalfWay.pop_back();
    }
    for ( int i : HalfWay ) { out << i << "\n";}
    if ( result->way % 2 == 0) {
        int median = HalfWay[HalfWay.size()/2];
        TryRightDelete(BinTree,BinTree,median);
    }
    //Left(BinTree);
}
