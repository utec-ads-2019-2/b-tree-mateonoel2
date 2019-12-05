#ifndef NODE_H
#define NODE_H
#include "btree.h"
#include <vector>

using namespace std;

template <typename T>
class Node {
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T>*> childs;
    bool isLeaf;

    public: 
        explicit Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            childs.resize(size);
        }

        void clearNode(){
            keys.clear();
            delete this;
            this = nullptr;
        }

        friend class Tree;
};

#endif