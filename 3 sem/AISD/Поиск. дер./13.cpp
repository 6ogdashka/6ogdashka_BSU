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

    Node(int value, Node* parent_ = nullptr)
        : data(value), parent(parent_), way{}, left(nullptr), right(nullptr) {}
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

bool Go(Node* current) {
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

    if (Go(current))
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

    if (Go(current))
        FindFinish(current->right, result);
    else
        FindFinish(current->left, result);
}

void LeftFind(Node* current, Node*& result) {
    if (current == nullptr) return;

    if (result == nullptr || current->way > result->way) {
        result = current;
    }

    LeftFind(current->left, result);
    LeftFind(current->right, result);
}

void CollectCandidates(Node* current, int max_way, std::vector<Node*>& candidates) {
    if (current == nullptr) return;
    if (current->way == max_way) {
        candidates.push_back(current);
    }
    CollectCandidates(current->left, max_way, candidates);
    CollectCandidates(current->right, max_way, candidates);
}

void ResetInWay(Node* current) {
    if (current == nullptr) return;
    current->inWay = false;
    ResetInWay(current->left);
    ResetInWay(current->right);
}

void PathUp(Node* current, std::vector<int>& result) {
    if (current == nullptr || !current->inWay) return;

    if (current->left && current->left->inWay)
        PathUp(current->left, result);
    else if (current->right && current->right->inWay)
        PathUp(current->right, result);

    result.push_back(current->data);
}

void PathDown(Node* current, std::vector<int>& result) {
    if (current == nullptr || !current->inWay) return;

    result.push_back(current->data);

    if (current->left && current->left->inWay)
        PathDown(current->left, result);
    else if (current->right && current->right->inWay)
        PathDown(current->right, result);
}

void HalfWayBuild(Node* current, std::vector<int>& result) {
    if (current == nullptr || !current->inWay) return;

    if (current->left && current->left->inWay)
        PathUp(current->left, result);

    result.push_back(current->data);

    if (current->right && current->right->inWay)
        PathDown(current->right, result);
}

void Final(Node*& BinTree, int way_size, std::vector<int> HalfWay) {
    std::sort(HalfWay.begin(), HalfWay.end());
    int median = HalfWay[HalfWay.size() / 2];

    if (way_size % 2 == 0) {
        TryRightDelete(BinTree, BinTree, median);
    }

    Left(BinTree);
}

long long GetHalfWayMinSum(Node* cand, Node* BinTree) {
    ResetInWay(BinTree);
    cand->inWay = true;
    Node* start = cand;
    Node* finish = cand;

    FindStart(cand->left, start);
    FindFinish(cand->right, finish);

    if (start == finish) return -1;

    if (start == cand || finish == cand) {
        return (start == cand) ? (long long)cand->data + finish->data : (long long)start->data + cand->data;
    } else {
        long long sum1 = (long long)start->parent->data + finish->data;
        long long sum2 = (long long)finish->parent->data + start->data;
        return std::min(sum1, sum2);
    }
}

bool ProcessPathAndExecute(Node*& BinTree, Node* result) {
    if (result == nullptr) return false;

    ResetInWay(BinTree);
    result->inWay = true;

    Node* start = result;
    Node* finish = result;

    FindStart(result->left, start);
    FindFinish(result->right, finish);

    if (start == finish) {
        Left(BinTree);
        return true;
    }

    std::vector<int> HalfWay{};
    HalfWayBuild(result, HalfWay);

    if ( (start == result) || (finish == result) ) {
        Final(BinTree, result->way, HalfWay);
        return true;
    }

    int start_parent_value = start->parent->data;
    int finish_parent_value = finish->parent->data;
    long long sum1 = (long long)start_parent_value + finish->data;
    long long sum2 = (long long)finish_parent_value + start->data;

    if ( sum1 < sum2 ) {
        HalfWay.erase(HalfWay.begin());
        Final(BinTree, result->way, HalfWay);
        return true;
    }

    if ( sum2 < sum1 ) {
        HalfWay.pop_back();
        Final(BinTree, result->way, HalfWay);
        return true;
    }

    if ( sum1 == sum2 ) {
        std::vector<int> HalfWay_copy = HalfWay;
        HalfWay_copy.pop_back();
        HalfWay.erase(HalfWay.begin());
        std::sort(HalfWay_copy.begin(),HalfWay_copy.end());
        std::sort(HalfWay.begin(),HalfWay.end());
        if ( HalfWay[HalfWay.size()/2] == HalfWay_copy[HalfWay_copy.size()/2] ) {
            TryRightDelete(BinTree, BinTree, HalfWay[HalfWay.size()/2]);
        }
        Left(BinTree);
        return true;
    }

    return false;
}

Node* FindBestRoot(Node* BinTree) {
    Node* max_node = nullptr;
    LeftFind(BinTree, max_node);
    if (max_node == nullptr) return nullptr;

    int max_way = max_node->way;
    std::vector<Node*> candidates;
    CollectCandidates(BinTree, max_way, candidates);

    if (candidates.empty()) return nullptr;

    std::sort(candidates.begin(), candidates.end(), [](Node* a, Node* b) {
        return a->data < b->data;
    });

    Node* best_result = nullptr;
    long long best_sum = -1;

    for (Node* cand : candidates) {
        long long current_sum = GetHalfWayMinSum(cand, BinTree);
        if (current_sum == -1) continue;

        if (best_result == nullptr || current_sum < best_sum) {
            best_sum = current_sum;
            best_result = cand;
        }
    }

    return best_result;
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

    Node* result = FindBestRoot(BinTree);
    if (result == nullptr) {
        Left(BinTree);
        return 0;
    }

    ProcessPathAndExecute(BinTree, result);

    return 0;
}