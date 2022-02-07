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

  if(end <= start)return;
  int middle = (end-start)/2;

  if(middle <= 1){

    merge<T>(start, start+middle, start+middle, end, vec, comp);
    return;
  }

  merge_sort<T>(start, start+middle, vec, comp);
  merge_sort<T>(start+middle, end, vec, comp);

  merge<T>(start, start+middle, start+middle, end, vec, comp);


}

template<class T>
void merge(int start1, int end1, int start2, int end2, std::vector<T>* vec, Comparator<T, T>* comp){

  int insert_place = (start1 < start2) ? start1 : start2;

  std::cout << start1 << " " << end1 << " " << start2 << " " << end2 << std::endl;

  std::vector<T> help;

  while (start1 < end1 && start2 < end2){

    T val1, val2;

    val1 = (*vec)[start1];
    val2 = (*vec)[start2];

    int compared = comp->compare(val1, val2);

    if (compared <= 0){


      //smaller, so it needs to be inserted left
      help.push_back(val1);
      start1++;

    }
    else{
      //smaller, so it needs to be inserted left
      help.push_back(val2);

      start2++;
    }

  }

  while (start1 < end1){

    T val1 = (*vec)[start1];
    help.push_back(val1);

    start1++;

  }

  while (start2 < end2){
    T val2 = (*vec)[start2];
    help.push_back(val2);

    start2++;

  }

  for(T& val : help){

    (*vec)[insert_place] = val;
    insert_place++;

  }




}

#endif
