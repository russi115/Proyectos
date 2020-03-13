#include <iostream>


template <class T>
class node {
    public:
        T info;
        node<T> *left;
        node<T> *right;
        node(){
            this->left = NULL;
            this->right = NULL;
        }
        node(T value){
           this->info = value;
        }
        ~node(){
        }
        void setInfo(T value){
            this->info = value;
        }
        void setLeftChild(node<T> *left){
            this->left = left;
        }
        void setRightChild(node<T> *right){
            this->right = right;
        }
        T getInfo(){
            return this->info;
        }
        node<T>* getLeftChild(){
            return this->left;
        }
        node<T>* getRightChild(){
            return this->right;
        }
};

template <class T>
class BST {
    private:
        node<T> *root;

        bool lookup(node<T> *pNode, T value){
            if (pNode == NULL)
                return false;
            else {
                if (value < pNode->getInfo())
                    return this->lookup(pNode->getLeftChild(), value);
                else if (value > pNode->getInfo())
                    return this->lookup(pNode->getRightChild(), value);
                else if (value == pNode->getInfo())
                    return true;
            }
        }
        node<T>* isHere(node<T> *pNode, T value){
            if (pNode == NULL)
                return NULL;
            else {
                if (value < pNode->getInfo())
                    return this->lookup(pNode->getLeftChild(), value);
                else if (value > pNode->getInfo())
                    return this->lookup(pNode->getRightChild(), value);
                else if (value == pNode->getInfo())
                    return pNode;
            }
        }

        node<T>* insert(node<T> *pNode, T value){
            if (pNode == NULL) {
                node<T> *pNew = new node<T>();
                pNew->setInfo(value);
                return pNew;
            }

            if (value < pNode->getInfo())
                pNode->setLeftChild(this->insert(pNode->getLeftChild(), value));
            else
                pNode->setRightChild(this->insert(pNode->getRightChild(), value));

            return pNode;
        }
        node<T>* erase(node<T> *pNode, T value){
            if (pNode == NULL)
                return pNode;

            if (value < pNode->getInfo())
                pNode->setLeftChild(this->erase(pNode->getLeftChild(), value));
            else if (value > pNode->getInfo())
                pNode->setRightChild(this->erase(pNode->getRightChild(), value));
            else {

                if (pNode->getLeftChild() == NULL) {
                    node<T> *temp = pNode->getRightChild();
                    delete pNode;
                    return temp;
                } else if (pNode->getRightChild() == NULL){
                    node<T> *temp = pNode->getLeftChild();
                    delete pNode;
                    return temp;
                }

                node<T> *temp = minValueNode(pNode->getRightChild());
                pNode->setInfo(temp->getInfo());
                pNode->setRightChild(erase(pNode->getRightChild(), temp->getInfo()));
            }
        }
        node<T>* minValueNode(node<T> *pNode){
            if (pNode->getLeftChild() != NULL)
                return minValueNode(pNode->getLeftChild());
            else
                return pNode;
        }

        void preorder(node<T> *pNode) {
            if (pNode != NULL) {
                std::cout << pNode->getInfo() << " ";
                preorder(pNode->getLeftChild());
                preorder(pNode->getRightChild());
            }
        }
        void inorder(node<T> *pNode){
            if (pNode != NULL) {
                inorder(pNode->getLeftChild());
                std::cout << pNode->getInfo() << " ";
                inorder(pNode->getRightChild());
            }
        }
        void postorder(node<T> *pNode){
            if (pNode != NULL) {
                postorder(pNode->getLeftChild());
                postorder(pNode->getRightChild());
                std::cout << pNode->getInfo() << " ";
            }
        }

    public:
        BST(){
           this->root = NULL;
        }
        ~BST(){
        }
        node<T>* getRoot() {
            return this->root;
        }
        bool isEmpty(){
            return this->root == NULL;
        }

        bool lookup(T value){
            return this->lookup(this->root, value);
        }
        node<T>* isHere(T value){
            return this->isHere(this->root, value);
        }

        void insert(T value){
            this->root = this->insert(this->root, value);
        }
        void erase(T value){
            this->root = this->erase(this->root, value);
        }

        void preorder(){
            preorder(this->root);
        }
        void inorder(){
            inorder(this->root);
        }
        void postorder(){
            postorder(this->root);
        }
};
