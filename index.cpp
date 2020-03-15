#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include "BST.hpp"
#include "list.hpp"
using namespace std;

struct letras
{
    char l;
    int c=0;
};

template <class T>
void leer(sebas::list<T> &l)
{//lee el archivo
    string s;
    ifstream archivo_entrada("Entrada.txt");
    if(archivo_entrada.fail()){
         cout<<"Error en la apertura del archivo.\n";
          archivo_entrada.close();
    }
    while(getline(archivo_entrada, s))
        l.insert(s,l.last());
    archivo_entrada.close();
}

void printQueue(sebas::queue<letras> &q)
{//imprime una cola de structs
  if(!q.isEmpty()){
    letras aux=*(q.head());
    q.dequeue();
    printQueue(q);
    printf("char: %c cantidad:%d\n",aux.l,aux.c);
    q.enqueue(aux);
  }
}

bool isHere (string s, char c)
{//verifica si un char esta en un string
    auto isChar = find(s.begin(), s.end(), c);
    if(isChar == s.end())
      return false;
     return true;
}

void huffman(string &s,sebas::queue<letras> &q)
{//se consigue el codigo huffman para crear el arbol
  int c[50];
  string order="";
  for(int i=0;i<50;++i) //se iguala todo el arr a 0
    c[i]=0;

    for(int i=0;i<s.length();++i){//se verifica cuantas veces se repite cada letra
      if(s[i]<'a')
        ++c[s[i]-'A'];
      else
        ++c[s[i]-'a'];
    }
  letras aux;
  for(int i=0;i<s.length();++i){
    if(!isHere(order,s[i]))
      order+=s[i];
  }
  for(int ii=0;ii<order.length();++ii){
    if( q.size() < order.length() )
      for(int i=0;i<50;++i){
        if(c[i]>0){
          if(i<25){
            aux.l=i+'A';
            aux.c=c[i];
            c[i]=0;
          }else{
            aux.l=i+'a';
            aux.c=c[i];
            c[i]=0;
          }
          q.enqueue(aux);
        }
      }
  }
}

void CastingEst(sebas::queue<letras> &q,sebas::list<letras> &l)
{//Casting de una cola a una lista
  while(!q.isEmpty()){
    letras temp=*(q.head());
      l.insert(temp,l.last());
      q.dequeue();
  }
}

void plantar(sebas::list<letras> &l, node<string> &Pnode)
{//Se utliza el codigo huffman para construir el arbol
    if(!l.isEmpty()){
        sebas::list<letras>::pos pos=l.first();
        int c=0;
        letras aux;
        while(pos!=l.last()){//sumatoria de todos lo nodos c++
            aux=*(l.get(pos));
            c+=aux.c;
            l.next(pos);
        }

        string pValue;
        if(l.size()>1)
            pValue="$" + to_string(c);

        if(Pnode == NULL)
            Pnode.setInfo(Pvalue);
        if(Pnode.info[1]> Pvalue[1])
            Pnode.setRightChild(Pvalue);
        if(Pnode.info[1]<Pvalue[1])
            Pnode.setLeftChild(Pvalue);

        t.insert(node);

        aux=*(l.get(l.first()));
        pValue=aux.l + to_string(aux.c );
        Pnode.left=pValue

        tree.insert(node);
        l.erase(l.first());
        plantar(l,t);
    }
}

void path(node<string> &Pnode, char ToFind, string &sol
){//codigo binario
    string aux= Pnode.getInfo();
    if(Pnode.left == NULL and Pnode.right == NULL and aux[0] != ToFind ){
        cout<< "\nKEOPS\n"<<endl;
    }else if(aux[0] == ToFind){
        sol=sol;
    }else if(Pnode.left!=NULL){
        path( *(Pnode.getLeftChild()), ToFind, sol+="0");
    }else if(Pnode.right!=NULL){
        path( *(Pnode.getRightChild()),ToFind, sol+="1");
    }
}

void way(node<string> &Pnode, sebas::list<char> &l,string &sol)
{//sigue el camino indicado por el codigo binario//convierte el codigo binario en una lista
    string aux= Pnode.getInfo();
    char ToFind= '/';
    if(!l.isEmpty())
        ToFind= *(l.get(l.first()));
    if( l.isEmpty() ){
        sol+=aux[0];
    }else if(Pnode.left!=NULL and ToFind == '0'){
        l.erase(l.first());
        way( *(Pnode.getLeftChild()), l, sol );
    }else if(Pnode.right!=NULL and ToFind == '1'){
        l.erase(l.first());
        way( *(Pnode.getRightChild()),l, sol );
    }
}

void castingBinario(string s, sebas::list<char> &l)
{//convierte el codigo binario en una lista
    for(int i=0;i<s.length();++i){
        l.insert(s[i], l.last() );
    }
}

void output(sebas::list<string> &l)
{
    FILE *archivo_salida=fopen("salida.txt","w");
    while(!l.isEmpty()){
        string s=*(l.get(l.first()));
        fprintf (archivo_salida, "%s\n", s.c_str()  );
        l.erase(l.first());
    }
    fclose(archivo_salida);
}
int main(){

    sebas::list<string> l;
    sebas::queue<letras> q;
    sebas::list<letras> ll;
    sebas::list<char> lc;
    sebas::list<string> out;
    BST<string> codi;
    BST<string> deco;
    string s="";
    string sol="";

    leer(l);
    if(!l.isEmpty())
    {//creación del primer arbol
        huffman( *(l.get(l.first())), q);
        l.erase(l.first());

        CastingEst(q,ll);
        plantar(ll,*(codi.getRoot()));
    }

    if(!l.isEmpty())
    {//creación del segundo arbol
        huffman( *(l.get(l.first())), q);
        l.erase(l.first());

        CastingEst(q,ll);
        plantar(ll,*(deco.getRoot()));
    }


    while(!l.isEmpty())
    {
        string pTemp= *(l.get(l.first()));
        for(int i=0;i<pTemp.length();++i ){
            path(*(codi.getRoot()),pTemp[i],s );

            castingBinario(s, lc);
            way(*(deco.getRoot()), lc, sol );
            s="";
        }
        out.insert(sol,out.last());



        l.erase(l.first());
    }

    output(out);
    return 0;
}
