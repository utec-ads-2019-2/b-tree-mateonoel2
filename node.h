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
    int degree;

    public: 
        explicit Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            childs.resize(size);
        }

        void insertNonFull(int k){}

        void splitChild(int i, Node<T>* y){}

        Node<T>* search(int k){
            int i = 0;
            while (i < size and k > keys[i])
                i++;

            if (keys[i] == k)
                return this;

            if (isLeaf)
                return NULL;

            return childs[i]->search(k);
        }

        void clearNode(){
                keys.clear();
                delete this;
                this = nullptr;
            }

        friend class Tree;

        ~Node() = default;
};

#endif