#ifndef BTREE_H
#define BTREE_H
#include "node.h"

template <typename T>
class BTree {
    private:
        Node<T>* root;
        unsigned int degree;

        void killTree(Node<T>* node){
            if(!node->childs.empty()){
                for(auto c : node->childs){
                    killTree(c);
                    node->childs.clear();}
            }
            node->clearNode();
        }
    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {};

        Node<T>* search(int k){
            return (root == NULL)? NULL : root->search(k);
        }

        bool insert(int k, T data) {}

        bool remove(int k) {}

        void print() {}

        ~BTree(){
            killTree(root);
        };
};

#endif