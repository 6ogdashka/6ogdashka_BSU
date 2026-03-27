#include "BinaryTree.h"
#include "DoubleList.h"
#include "SingleList.h"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    BinaryTree tree;
    tree.createPerfectlyBalanced(7);
    tree.print();
    std::cout << "Arithmetic mean: " << tree.getArithmeticMean() << "\n";
    tree.convertToSearchTree();
    tree.print();

    DoubleList dlist;
    dlist.push_back(10);
    dlist.push_back(20);
    dlist.push_back(30);
    dlist.push_back(40);
    dlist.print();
    dlist.Delete();
    dlist.print();


    List slist;
    slist.push_back("Hello");
    slist.push_back("world");
    slist.push_back("from");
    slist.push_back("C++");
    slist.print();

    return 0;
}