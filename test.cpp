#include <iostream>
#include "BST.hpp"
#include "list.hpp"

using namespace std;

void print(sebas::list<char> &l){//imprime el contenido de la lista
    sebas::list<char>::pos position=l.first();
    printf("%s","\nlista de chars: \n");
    while(position != l.last()){
      cout << *(l.get(position)) << endl;
      l.next(position);
   }
   printf("%s","\n");
}

void path(node<string> &Pnode, char ToFind, string &sol){
    string aux= Pnode.getInfo();
    if(Pnode.isLeef() and aux[0] != ToFind ){
        cout<< "\nestoy en una hoja.\ncamino: "<<sol<<endl;
    }else if(aux[0] == ToFind){
        sol=sol;
    }else if(Pnode.left!=NULL){
        path( *(Pnode.getLeftChild()), ToFind, sol+="0");
    }else if(Pnode.right!=NULL){
        path( *(Pnode.getRightChild()),ToFind, sol+="1");
    }
}

void way(node<string> &Pnode, sebas::list<char> &l,string &sol){
    string aux= Pnode.getInfo();//A5
    char ToFind= '/';
    if(!l.isEmpty())
        ToFind= *(l.get(l.first()));//1
    //cout<<"\naux in way :"<<aux;
    //cout<<"\nToFind in way :"<<ToFind;
    if( l.isEmpty() ){
        sol+=aux[0];
    }else if(Pnode.left!=NULL and ToFind == '0'){
        //cout<<"\nleft->\n";
        l.erase(l.first());
        way( *(Pnode.getLeftChild()), l, sol );
        l.insert(ToFind,l.first());
    }else if(Pnode.right!=NULL and ToFind == '1'){
        //cout<<"\nright->\n";
        l.erase(l.first());
        way( *(Pnode.getRightChild()),l, sol );
        l.insert(ToFind,l.first());
    }
}

int main(){

    BST<string> tree;
    sebas::list<char> l;
    string sol="";

    tree.insert("A5");
    tree.insert("B2");
    tree.insert("R2");
    tree.insert("C1");
    tree.insert("D1");

    l.insert('1',l.last());
    l.insert('1',l.last());
    l.insert('0',l.last());
    l.insert('1',l.last());


    printf("\ninorder: ");
    tree.inorder();
    printf("\npreorder: ");
    tree.preorder();

    path( *(tree.getRoot()), 'D',sol );
    cout<<endl<<"sol :"<<sol<<endl;

    print(l);
    way( *(tree.getRoot()), l, sol );
    cout<<"\nsol way: "<<sol<<endl;
    printf("\nfin\n");


  return 0;
}
//--std=c++11^C
