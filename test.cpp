#include <iostream>
#include "BST.hpp"

using namespace std;


void path(node<string> &Pnode, char ToFind, string &sol){
    string aux= Pnode.getInfo();
    if(Pnode.left == NULL and Pnode.right == NULL and aux[0] != ToFind ){
        cout<< "\nestoy en una hoja.\ncamino: "<<sol<<endl;
    }else if(aux[0] == ToFind){
        sol=sol;
    }else if(Pnode.left!=NULL){
        path( *(Pnode.getLeftChild()), ToFind, sol+="0");
    }else if(Pnode.right!=NULL){
        path( *(Pnode.getRightChild()),ToFind, sol+="1");
    }
}

int main(){

    /*
    A5
    B2
    R2
    C1
    D1
    */

    BST<string> tree;
    tree.insert("A5");
    tree.insert("B2");
    tree.insert("R2");
    tree.insert("C1");
    tree.insert("D1");
    printf("\ninorder: ");
    tree.inorder();
    printf("\npreorder: ");
    tree.preorder();

    string sol="";
    path( *(tree.getRoot()), 'D',sol );
    cout<<sol<<endl;

  return 0;
}
//--std=c++11^C
