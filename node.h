#ifndef NODE_H
#define NODE_H
#include "btree.h"
#include <vector>
#include <queue> 
#include <iostream> 

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
                    split(i+1, childs[i+1]);

                    if (keys[i+1] < k)
                        i++;
                }
                childs[i+1]->insertNonFull(k);
            }

        }

        void split(int i, Node<T>* y){
            // Qué es t?
            auto newNode = new Node<T>(y->t, y->leaf);
            newNode->n = size - 1;

            for (int j = 0; j < size-1; j++)
                newNode->keys[j] = y->keys[j+size];
            // leaf??
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

        int findKey(int k){
            int index=0;
            while (index<n && keys[index] < k)
                ++index;
            return index;
        }

        void remove(int k){
            int index = findKey(k);
            if (index < n and keys[index] == k){
                if (isLeaf)
                    removeLeaf(index);
                else
                    removeNonLeaf(index);
            }
            else{
                bool flag = index == n;
                if (childs[index]->n < size)
                    fill(index);

                if (flag and index > n)
                    childs[index-1]->remove(k);
                else
                    childs[index]->remove(k);
            }
        }

        void removeLeaf (int index){
            for (int i=index+1; i<n; ++i)
                keys[i-1] = keys[i];
            n--;
        }

        void removeNonLeaf(int index){
            int k = keys[index];
            if (childs[index]->n >= size){
                int pred = getPred(index);
                keys[index] = pred;
                childs[index]->remove(pred);
            }
            else if  (childs[index+1]->n >= size){
                int succ = getSucc(index);
                keys[index] = succ;
                childs[index+1]->remove(succ);
            }
            else{
                merge(index);
                childs[index]->remove(k);
            }
        }

        int getPred(int index){
            Node<T>* curent=childs[index];
            while (!curent->isLeaf)
                curent = curent->childs[curent->n];

            return curent->keys[curent->n-1];
        }

        int getSucc(int index){
            Node<T>* curent = childs[index+1];
            while (!curent->isLeaf)
                curent = curent->childs[0];

            return curent->keys[0];
        }

        void fill(int index){
            if (index!=0 and childs[index-1]->n>=size)
                FromPrev(index);

            else if (index!=n && childs[index+1]->n>=size)
                FromNext(index);

            else{
                if (index != n)
                    merge(index);
                else
                    merge(index-1);
            }
        }

    void FromPrev(int index){
        Node<T>* child = childs[index];
        Node<T>* sibling = childs[index-1];

        for (int i=child->n-1; i>=0; --i)
            child->keys[i+1] = child->keys[i];

        if (!child->isLeaf){
            for(int i=child->n; i>=0; --i)
                child->childs[i+1] = child->childs[i];
        }

        child->keys[0] = keys[index-1];

        if(!child->isLeaf)
            child->childs[0] = sibling->childs[sibling->n];

        keys[index-1] = sibling->keys[sibling->n-1];

        child->n += 1;
        sibling->n -= 1;
    }

    void FromNext(int index){
        Node<T>* child=childs[index];
        Node<T>* sibling=childs[index+1];

        child->keys[(child->n)] = keys[index];

        if (!(child->isLeaf))
            child->childs[(child->n)+1] = sibling->childs[0];

        keys[index] = sibling->keys[0];

        for (int i=1; i<sibling->n; ++i)
            sibling->keys[i-1] = sibling->keys[i];

        if (!sibling->isLeaf){
            for(int i=1; i<=sibling->n; ++i)
                sibling->childs[i-1] = sibling->childs[i];
        }

        child->n += 1;
        sibling->n -= 1;
    }

    void merge(int index){
        Node<T>* child = childs[index];
        Node<T>* sibling = childs[index+1];

        child->keys[size-1] = keys[index];

        for (int i=0; i<sibling->n; ++i)
            child->keys[i+size] = sibling->keys[i];

        if (!child->isLeaf){
            for(int i=0; i<=sibling->n; ++i)
                child->childs[i+size] = sibling->childs[i];
        }

        for (int i=index+1; i<n; ++i)
            keys[i-1] = keys[i];

        for (int i=index+2; i<=n; ++i)
            childs[i-1] = childs[i];

        child->n += sibling->n+1;
        n--;

        delete(sibling);
    }

    void print() {
        queue<Node<T>*> next;
        next.push(this);

        while (!next.empty()) {
            Node<T>* temp = next.front();
            next.pop();

            temp->printKeys();

            for (int i = 0; i < temp->childs.size(); i++) {
                next.push(temp->childs[i]);
            }

            cout << endl << endl;
        } 
    }
    
    void printKeys() {
        for (int i = 0; i < keys.size(); i++) {
            cout << keys[i] << " ";
        }
    }

    void clearNode(){
                keys.clear();
                delete this;
                //this = nullptr;
            }

        friend class Tree;

        ~Node() = default;
};

#endif