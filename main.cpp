#include "btree.h"
using namespace std;

int main() {

    BTree<int> tree(3);
    for (int i = 0; i < 30; i++) {
        tree.insert(i, i);
    }
    
    tree.print();

    return EXIT_SUCCESS;
}