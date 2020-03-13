#include <iostream>
#include <fstream>
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

string backtree(node<string> n, string searching, string &sol)
{
    string aux=*(n.info);
  if( aux[0] ==searching )//condicional para encontrar la solucion
    return sol;
  else{//exploracion de las posibles soluciones
    backtree(n.getLeftChild(),searching,sol+"0");//llamadas recursivas
    sol.erase(sol.lenght()-1,1);//actualizacion de los parametros
  }else{
    backtree(n.getRightChild(),searching,sol+"1");//llamadas recursivas
    sol.erase(sol.lenght()-1,1);//actualizacion de los parametros
  }
}

int main(){
    sebas::list<string> l;             //creación de la lista
    sebas::queue<letras> q;            //creación de la cola de letas
    sebas::list<letras> li;            //creación de la lista de letras
    BST<string> codi;                  //creación del BST de CODIficacion
    BST<string> deco;                  //creación del BST de DECOdificacion
    string way="";


    leer(l);                           //se lee el archivo y se guarda en una lista

    huffman(*(l.get(l.first())),q);   //se aplica el codigo huffman a la primera lista y luego se le pasa a lasegunda
    l.erase(l.first());
    CastingEst(q,li);
    plantar(li,codi);
    printf("\ninorder: ");
    codi.inorder();



    huffman(*(l.get(l.first())),q);    //se aplica el codigo huffman a la primera lista y luego se le pasa a lasegunda
    l.erase(l.first());
    CastingEst(q,li);
    plantar(li,deco);
    printf("\ninorder: ");
    deco.inorder();

    //backtree retorna un string el cual se usara para recorrer deco
    way=backtree(codi.getRoot(),way);
    cout<<way<<endl;

    printf("\nfin\n");
    return 0;
}
