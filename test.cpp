#include <iostream>
#include <bits/stdc++.h>
using namespace std;


bool isHere (char c, string temp){
    auto isChar = std::find(temp.begin(), temp.end(), c);
    if(isChar == temp.end()){
      return false;
    }else{
      return true;
    }
}

int main(){
  string s="AAABBB";
if(isHere('a',s))
  cout<<"yes"<<endl;
else
  cout<<"NO"<<endl;
  return 0;
}
//--std=c++11^C
