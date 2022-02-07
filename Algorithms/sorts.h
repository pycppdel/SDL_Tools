/*
*
*
* File for sorting purposes
*
*
*/

#ifndef __SDL_TOOLS_SORTS__
#define __SDL_TOOLS_SORTS__

#include <vector>

//comparator for objects to sort
template<class A, class B>
class Comparator{

public:

  Comparator();

  virtual int compare(A, B)=0; //returns 0 if the objects are equal, -1 if A < B, 1 if A > B

};

template<class A, class B>
Comparator<A, B>::Comparator(){

}
//merge sort in place
template<class T>
void merge_sort(int start, int end, std::vector<T>* vec, Comparator<T, T>* comp){

}

#endif
