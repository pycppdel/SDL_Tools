#include "sorts.h"
#include <iostream>

class Integer : public Comparator<int, int>{

public:

  Integer();
  int compare(int a, int b);

};

Integer::Integer(){

}

int Integer::compare(int a, int b){

  if( a < b )return -1;
  else if (a > b)return 1;
  else return 0;

}

void print(std::vector<int>& v){

  for(int g : v){
    std::cout << g << " ";
  }
  std::cout << std::endl;

}

int main(){
  std::vector<int> val = {3, 5, 6, 3, 2, 6};

  Comparator<int, int>* comp = new Integer();

  merge_sort<int>(0, val.size(), &val, comp);

  print(val);

  delete comp;
  return 0;
}
