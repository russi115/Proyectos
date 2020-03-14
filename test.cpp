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
   printf("%s","\n\n");
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

void way(node<string> &Pnode, sebas::list<char> &l){
    string aux= Pnode.getInfo();
    char ToFind= *(l.get(l.first()));
    if(Pnode.isLeef()){
        cout<<"found: "<<aux[0]<<endl;
    }else if(Pnode.left!=NULL and ToFind == '0'){
        l.erase(l.first());
        way( *(Pnode.getLeftChild()), l );
        l.insert(ToFind,l.first());
    }else if(Pnode.right!=NULL and ToFind == '1'){
        l.erase(l.first());
        way( *(Pnode.getRightChild()),l );
        l.insert(ToFind,l.first());
    }
}

int main(){

    BST<string> tree;
    tree.insert("A5");
    tree.insert("B2");
    tree.insert("R2");
    tree.insert("C1");
    tree.insert("D1");
    string sol="";


    sebas::list<char> l;
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

    //for(int i=0;i<sol.length();++i) cout<<sol.erase(0,1)<<endl;
    print(l);
    way( *(tree.getRoot()), l );

    printf("\nfin\n");


  return 0;
}
//--std=c++11^C
