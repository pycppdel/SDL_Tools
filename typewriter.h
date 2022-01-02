/*
* Typewriter for storing text input from the user
*
*
*
*/

#ifndef __TYPEWRITER__
#define __TYPEWRITER__

#ifndef _SDL_H
#include <SDL.h>
#endif

#include <string>
#include <cstddef>
#include <cstring>
#include <algorithm>

class Typewriter{

  /*
  *
  * Functions of Typewriter:
  *
  * gets an pointer to an event and everytime check() is called, the input will be checked
  *
  */
private:
  SDL_Event* event_ptr;
  //actually contained text
  std::string contained_text;

public:

  //Methods for the typewriter:
  Typewriter();//empty constructor
  Typewriter(SDL_Event*);//event for clearness
  Typewriter(SDL_Event*, char*);//constructor for previously made text

  virtual ~Typewriter();

  void check(); // most important method, checks and changes inputs
  char* clear(); //clears the string and gives back what was cleared
  char* set_text(char*);//sets the text to text and gives back overwritten text
  char* get_text();
  char pop(); // pops last text

};

Typewriter::Typewriter(){

  contained_text = "";
  event_ptr = NULL;

}

Typewriter::Typewriter(SDL_Event* e){

  event_ptr = e;
  contained_text = "";

}

Typewriter::Typewriter(SDL_Event* e, char* t){

  contained_text = t;
  event_ptr = e;

}

Typewriter::~Typewriter(){


}

void Typewriter::check(){

  switch(event_ptr->type){

    case SDL_KEYDOWN:

                //take action
                if (SDL_GetModState() & KMOD_LSHIFT){

                  switch(event_ptr->key.keysym.sym){

                    case SDLK_a:
                                  contained_text.push_back('A');
                                  break;
                    case SDLK_b:
                                  contained_text.push_back('B');
                                  break ;
                    case SDLK_c:
                                  contained_text.push_back('C');
                                  break;
                    case SDLK_d:
                                  contained_text.push_back('D');
                                  break;

                    case SDLK_e:
                                  contained_text.push_back('E');
                                  break;
                    case SDLK_f:
                                  contained_text.push_back('F');
                                  break ;
                    case SDLK_g:
                                  contained_text.push_back('G');
                                  break;
                    case SDLK_h:
                                  contained_text.push_back('H');
                                  break;
                    case SDLK_i:
                                  contained_text.push_back('I');
                                  break;
                    case SDLK_j:
                                  contained_text.push_back('J');
                                  break ;
                    case SDLK_k:
                                  contained_text.push_back('K');
                                  break;
                    case SDLK_l:
                                  contained_text.push_back('L');
                                  break;

                    case SDLK_m:
                                  contained_text.push_back('M');
                                  break;
                    case SDLK_n:
                                  contained_text.push_back('N');
                                  break ;
                    case SDLK_o:
                                  contained_text.push_back('O');
                                  break;
                    case SDLK_p:
                                  contained_text.push_back('P');
                                  break;
                    case SDLK_q:
                                  contained_text.push_back('Q');
                                  break;
                    case SDLK_r:
                                  contained_text.push_back('R');
                                  break ;
                    case SDLK_s:
                                  contained_text.push_back('S');
                                  break;
                    case SDLK_t:
                                  contained_text.push_back('T');
                                  break;

                    case SDLK_u:
                                  contained_text.push_back('U');
                                  break;
                    case SDLK_v:
                                  contained_text.push_back('V');
                                  break ;
                    case SDLK_w:
                                  contained_text.push_back('W');
                                  break;
                    case SDLK_x:
                                  contained_text.push_back('X');
                                  break;
                    case SDLK_y:
                                  contained_text.push_back('Y');
                                  break;
                    case SDLK_z:
                                  contained_text.push_back('Z');
                                  break;
                    case SDLK_SPACE:
                                  contained_text.push_back(' ');
                                  break;
                    case SDLK_BACKSPACE:
                                  pop();
                                  break;



                  }


                }
                else{

                  switch(event_ptr->key.keysym.sym){

                    case SDLK_a:
                                  contained_text.push_back('a');
                                  break;
                    case SDLK_b:
                                  contained_text.push_back('b');
                                  break ;
                    case SDLK_c:
                                  contained_text.push_back('c');
                                  break;
                    case SDLK_d:
                                  contained_text.push_back('d');
                                  break;

                    case SDLK_e:
                                  contained_text.push_back('e');
                                  break;
                    case SDLK_f:
                                  contained_text.push_back('f');
                                  break ;
                    case SDLK_g:
                                  contained_text.push_back('g');
                                  break;
                    case SDLK_h:
                                  contained_text.push_back('h');
                                  break;
                    case SDLK_i:
                                  contained_text.push_back('i');
                                  break;
                    case SDLK_j:
                                  contained_text.push_back('j');
                                  break ;
                    case SDLK_k:
                                  contained_text.push_back('k');
                                  break;
                    case SDLK_l:
                                  contained_text.push_back('l');
                                  break;

                    case SDLK_m:
                                  contained_text.push_back('m');
                                  break;
                    case SDLK_n:
                                  contained_text.push_back('n');
                                  break ;
                    case SDLK_o:
                                  contained_text.push_back('o');
                                  break;
                    case SDLK_p:
                                  contained_text.push_back('p');
                                  break;
                    case SDLK_q:
                                  contained_text.push_back('q');
                                  break;
                    case SDLK_r:
                                  contained_text.push_back('r');
                                  break ;
                    case SDLK_s:
                                  contained_text.push_back('s');
                                  break;
                    case SDLK_t:
                                  contained_text.push_back('t');
                                  break;

                    case SDLK_u:
                                  contained_text.push_back('u');
                                  break;
                    case SDLK_v:
                                  contained_text.push_back('v');
                                  break ;
                    case SDLK_w:
                                  contained_text.push_back('w');
                                  break;
                    case SDLK_x:
                                  contained_text.push_back('x');
                                  break;
                    case SDLK_y:
                                  contained_text.push_back('y');
                                  break;
                    case SDLK_z:
                                  contained_text.push_back('z');
                                  break;
                    case SDLK_SPACE:
                                  contained_text.push_back(' ');
                                  break;
                    case SDLK_BACKSPACE:
                                    pop();
                                  break;



                  }
                }
                break;
  }

}

char* Typewriter::clear(){

  int full_length = strlen(contained_text.c_str());
  char* back = new char[full_length];
  strncpy(back, contained_text.c_str(), full_length);
  contained_text = "";
  return back;
}

char* Typewriter::set_text(char* t){

  int full_length = strlen(contained_text.c_str());
  char* back = new char[full_length];
  strncpy(back, contained_text.c_str(), full_length);
  contained_text = t;
  return back;
}

char* Typewriter::get_text(){

  return const_cast<char*>(contained_text.c_str());
}

char Typewriter::pop(){
  char back = contained_text.c_str()[contained_text.size()-1];
  if(contained_text.size() > 0){
    contained_text.pop_back();
  }
  return back;
}


#endif
