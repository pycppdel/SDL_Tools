#include "sorts.h"
#include <iostream>
#include <ctime>

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

  srand(time(NULL));
  std::vector<int> val;

  for(int i = 0; i < 100; i++){

    val.push_back(rand()%400);

  }

  Comparator<int, int>* comp = new Integer();

  insertion_sort(&val, comp);

  print(val);

  delete comp;
  return 0;
}
