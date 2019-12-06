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

        bool insert(int k, T data) {
            if (!search(k))
                return false;
            if (root == NULL){
                root = new Node<T>(degree, true);
                root->keys[0] = k;
                root->n = 1;
            }
            else{
                if (root->n == 2*degree-1){
                    auto temp = new Node<T>(degree, false);
                    temp->childs[0] = root;
                    temp->split(0, root);

                    int i = 0;
                    if (temp->keys[0] < k)
                        i++;

                    temp->childs[i]->insertNonFull(k);

                    root = temp;
                }
                else{
                    root->insertNonFull(k);
                }
            }
            return true;
        }

        bool remove(int k) {
            if (!root){
                return false;
            }

            root->remove(k);

            if (root->n==0){
                Node<T>* temp = root;
                if (root->isLeaf)
                    root = NULL;
                else
                    root = root->childs[0];
                delete temp;
            }
            return true;
        }

        ~BTree(){
            killTree(root);
        };
};

#endif