#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void clear(TreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    TreeNode* buildBalanced(int n) {
        if (n <= 0) return nullptr;
        
        int left_n = n / 2;
        int right_n = n - left_n - 1;
        
        int value = std::rand() % 100; 
        
        TreeNode* newNode = new TreeNode(value);
        newNode->left = buildBalanced(left_n);
        newNode->right = buildBalanced(right_n);
        
        return newNode;
    }

    void printTree(TreeNode* node, int level = 0) const {
        if (node != nullptr) {
            printTree(node->right, level + 1);
            for (int i = 0; i < level; ++i) {
                std::cout << "      ";
            }
            std::cout << node->data << std::endl;
            printTree(node->left, level + 1);
        }
    }

    void calculateSumAndCount(TreeNode* node, int& sum, int& count) const {
        if (node != nullptr) {
            sum += node->data;
            count++;
            calculateSumAndCount(node->left, sum, count);
            calculateSumAndCount(node->right, sum, count);
        }
    }

    void collectValues(TreeNode* node, std::vector<int>& values) const {
        if (node != nullptr) {
            collectValues(node->left, values);
            values.push_back(node->data);
            collectValues(node->right, values);
        }
    }

    void assignValuesInOrder(TreeNode* node, const std::vector<int>& values, int& index) {
        if (node != nullptr) {
            assignValuesInOrder(node->left, values, index);
            node->data = values[index++];
            assignValuesInOrder(node->right, values, index);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    ~BinaryTree() {
        clear(root);
    }

    void createPerfectlyBalanced(int numberOfNodes) {
        clear(root);
        root = buildBalanced(numberOfNodes);
    }

    void print() const {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        std::cout << "--------------------------------" << std::endl;
        printTree(root);
        std::cout << "--------------------------------" << std::endl;
    }

    double getArithmeticMean() const {
        if (root == nullptr) return 0.0;
        
        int sum = 0;
        int count = 0;
        calculateSumAndCount(root, sum, count);
        
        return static_cast<double>(sum) / count;
    }

    void convertToSearchTree() {
        if (root == nullptr) return;
        
        std::vector<int> values;
        collectValues(root, values);
        
        std::sort(values.begin(), values.end());
        
        int index = 0;
        assignValuesInOrder(root, values, index);
    }
};

#endif