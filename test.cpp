#include <iostream>
#include "BST.hpp"
#include "list.hpp"

using namespace std;

int main(){

    BST<string> tree;

    tree.insert("root");

    node<string> node= *(tree.getRoot());
    cout<< "tree: "<<  node.getInfo() <<endl;

  return 0;
}
//--std=c++11^C
