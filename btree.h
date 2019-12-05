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

        T search(int k) { 
            // TODO
        } 

        bool insert(int k, T data) {
        }

        bool remove(int k) {
            // TODO
        }

        void print() {
            // TODO
        }

        ~BTree(){
            killTree(root);
        };
};

#endif