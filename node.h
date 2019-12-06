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
    int n;

    public: 
        explicit Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            childs.resize(size);
            n=0;
        }

        void insertNonFull(int k) {
            int i = n - 1;

            if (isLeaf){
                while (i >= 0 and keys[i] > k){
                    keys[i+1] = keys[i];
                    i--;
                }
                keys[i+1] = k;
                n = n+1;
            }
            else{
                while (i >= 0 and keys[i] > k)
                    i--;

                if (childs[i+1]->n == 2*size-1){
                    splitChild(i+1, childs[i+1]);

                    if (keys[i+1] < k)
                        i++;
                }
                childs[i+1]->insertNonFull(k);
            }

        }

        void splitChild(int i, Node<T>* y){
            auto newNode = new Node<T>(y->t, y->leaf);
            newNode->n = size - 1;

            for (int j = 0; j < size-1; j++)
                newNode->keys[j] = y->keys[j+size];

            if (y->leaf == false){
                for (int j = 0; j < size; j++)
                    newNode->childs[j] = y->childs[j+size];
            }

            y->n = size - 1;

            for (int j = n; j >= i+1; j--)
                childs[j+1] = childs[j];

            childs[i+1] = newNode;

            for (int j = n-1; j >= i; j--)
                keys[j+1] = keys[j];

            keys[i] = y->keys[size-1];

            n = n + 1;
        }

        Node<T>* search(int k){
            int i = 0;
            while (i < n and k > keys[i])
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