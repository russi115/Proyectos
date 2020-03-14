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

void print(sebas::list<int> &l){//imprime el contenido de la lista
    sebas::list<int>::pos position=l.first();
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
  //cout<<s<<endl;
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
  //cout<<"order: "<<order<<" order.lenght: "<<order.length()<<endl;
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
          /*if(aux.l==order[i]){
            aux.cantidad=c[i];
            cout<<"this is aux.c: "<<aux.cantidad<<endl;
            c[i]=0;
          }*/
          //cout<<aux.l<<" -pre_enqueue: "<<aux.cantidad<<endl;
          l.enqueue(aux);
        }
      }
  }
}

void printQueue(sebas::queue<letras> &q){
  if(!q.isEmpty()){
    letras aux=*(q.head());
    //cout<<aux.l<<" -hey- "<<aux.cantidad<<endl;
    q.dequeue();
    printQueue(q);
    q.enqueue(aux);
  }
}

void CastingEst(sebas::queue<letras> &q,sebas::list<letras> &l){
  while(!q.isEmpty()){
    //cout<<q.size()<<endl;
    letras temp=*(q.head());
    //cout<<endl<<temp.l<<" -hi- "<<temp.cantidad<<endl;
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

void algo(string s, sebas::list<string> &code, node<string> &Pnode){
    for(int i=0;i< s.length() ;++i){
        string sol="";
        path( Pnode, s[i] ,sol );
        code.insert(sol,code.last());
    }
}

int main(){
    sebas::list<string> l;             //creación de la lista
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


    algo(*(l.get(l.first())),code, *(codi.getRoot()));
    l.erase(l.first());
    print(code);





    printf("\nfin\n");
    return 0;
}
