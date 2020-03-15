#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include "BST.hpp"
#include "list.hpp"
using namespace std;


struct letras{
    char l;
    int cantidad=0;
};

void leer(sebas::list<string> &l){//lee el archivo
    string s;
    ifstream archivo_entrada("Entrada.txt");
    if(archivo_entrada.fail()){
         cout<<"Error en la apertura del archivo.\n";
          archivo_entrada.close();
    }
    sebas::list<string>::pos position=l.last();
    while(getline(archivo_entrada, s))
        l.insert(s,position);
    archivo_entrada.close();
}

void print(sebas::list<string> &l){//imprime el contenido de la lista
    sebas::list<string>::pos position=l.first();
    printf("%s","\nlista de palabras: \n");
    while(position != l.last()){
      cout << *(l.get(position)) << endl;
      l.next(position);
   }
   printf("%s","\n\n");
}

void print(sebas::list<char> &l){//imprime el contenido de la lista
    sebas::list<char>::pos position=l.first();
    printf("%s","\nlista de enteros: \n");
    while(position != l.last()){
      cout << *(l.get(position)) << endl;
      l.next(position);
   }
   printf("%s","\n\n");
}

void impL(sebas::list<letras> &le){//imprimir contenido de la lista struct
    sebas::queue<letras>::pos pos=le.first();
    letras aux;
    printf("%s","\nlista de letras:\n");
    while(pos!=le.last()){
        aux=*(le.get(pos));
        cout<<aux.l<<" "<<aux.cantidad<<endl;
        le.next(pos);
    }
    printf("%s","\n");
}

bool isHere (string s, char c){
    auto isChar = find(s.begin(), s.end(), c);
    if(isChar == s.end()){
      return false;
    }else{
      return true;
    }
}

void huffman(string &s,sebas::queue<letras> &l){
  int c[50];
  string order="";
  for(int i=0;i<50;++i){//se iguala todo el arr a 0
    c[i]=0;
  }
    for(int i=0;i<s.length();++i){//se verifica cuantas veces se repite cada letra
      if(s[i]<'a'){
        ++c[s[i]-'A'];
      }else
        ++c[s[i]-'a'];
    }
  letras aux;
  for(int i=0;i<s.length();++i){
    if(!isHere(order,s[i]))
      order+=s[i];
  }
  for(int ii=0;ii<order.length();++ii){
    if( l.size() < order.length() )
      for(int i=0;i<50;++i){
        if(c[i]>0){
          if(i<25){
            aux.l=i+'A';
            aux.cantidad=c[i];
            c[i]=0;
          }else{
            aux.l=i+'a';
            aux.cantidad=c[i];
            c[i]=0;
          }
          l.enqueue(aux);
        }
      }
  }
}

void printQueue(sebas::queue<letras> &q){
  if(!q.isEmpty()){
    letras aux=*(q.head());
    q.dequeue();
    printQueue(q);
    q.enqueue(aux);
  }
}

void CastingEst(sebas::queue<letras> &q,sebas::list<letras> &l){
  while(!q.isEmpty()){
    letras temp=*(q.head());
      l.insert(temp,l.last());
      q.dequeue();
  }
}

void plantar(sebas::list<letras> &l, BST<string> &t){
    if(!l.isEmpty()){
        sebas::list<letras>::pos pos=l.first();
        int c=0;
        letras aux;
        while(pos!=l.last()){
            aux=*(l.get(pos));
            c+=aux.cantidad;
            l.next(pos);
        }
        string node;
        if(l.size()>1){
        node="$" + to_string(c);
        t.insert(node);
        }

        aux=*(l.get(l.first()));
        node=aux.l + to_string(aux.cantidad);

        t.insert(node);
        l.erase(l.first());
        plantar(l,t);
    }
}

void path(node<string> &Pnode, char ToFind, string &sol){//codigo binario
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

void algo(string s, sebas::list<string> &code, node<string> &Pnode){
    for(int i=0;i< s.length() ;++i){
        string sol="";
        path( Pnode, s[i] ,sol );
        code.insert(sol,code.last());
    }
}

void casting(sebas::list<string> &l1, sebas::list<char> &l2){
    if(!l1.isEmpty()){
        string aux=*(l1.get(l1.first()));
        for(int i=0;i<aux.length();++i){
            char c=aux[i];
            l2.insert(c,l2.last());
        }
    }
}

void way(node<string> &Pnode, sebas::list<char> &l,string &sol){
    string aux= Pnode.getInfo();
    char ToFind= '/';
    if(!l.isEmpty())
        ToFind= *(l.get(l.first()));
    if( l.isEmpty() ){
        sol+=aux[0];
    }else if(Pnode.left!=NULL and ToFind == '0'){
        l.erase(l.first());
        way( *(Pnode.getLeftChild()), l, sol );
        l.insert(ToFind,l.first());
    }else if(Pnode.right!=NULL and ToFind == '1'){
        l.erase(l.first());
        way( *(Pnode.getRightChild()),l, sol );
        l.insert(ToFind,l.first());
    }
}

void decodi(sebas::list<string>&l, sebas::list<char> l2, node<string> &Pnode, string &s){
    while(!l.isEmpty()){
        casting(l,l2);
        way( Pnode , l2, s );
        l.erase(l.first());
    }
}

int main(){
    sebas::list<string> l;             //creación de la lista
    sebas::list<char> lc;
    sebas::list<string> code;
    sebas::queue<letras> q;            //creación de la cola de letas
    sebas::list<letras> li;            //creación de la lista de letras
    BST<string> codi;                  //creación gdel BST de CODIficacion
    BST<string> deco;                  //creación del BST de DECOdificacion


    leer(l);                           //se lee el archivo y se guarda en una lista

    huffman(*(l.get(l.first())),q);   //se aplica el codigo huffman a la primera lista y luego se le pasa a lasegunda
    l.erase(l.first());
    CastingEst(q,li);
    plantar(li,codi);

    huffman(*(l.get(l.first())),q);    //se aplica el codigo huffman a la primera lista y luego se le pasa a lasegunda
    l.erase(l.first());
    CastingEst(q,li);
    plantar(li,deco);



    printf("\ninorder: ");
    codi.inorder();

    printf("\ninorder: ");
    deco.inorder();


    algo(*(l.get(l.first())),code, *(codi.getRoot()) );
    l.erase(l.first());
    string s="";
    decodi(l,lc,*(deco.getRoot()),s);

    cout<<"\nsol: "<<s<<endl;






    printf("\nfin\n");
    return 0;
}
