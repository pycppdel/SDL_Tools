/*
*
*
*
* Main class for Frame. Every level, loading screen usw. can be treated as a Frame.
* All the logic can be extracted and the main file can be simplified to loading all frames in and checking dependencies
*
*
*/

#ifndef __SDL_TOOLS_DEVEL_FRAME__
#define _SDL_TOOLS_DEVEL_FRAME__

//dependencies: physics
#ifndef __ALL_PHYSICS_IMPORT__
#include "../Physic/physic.h"
#endif

#ifndef __SDL_TOOLS_AUTO_ENGINE__
#include "auto_engine.h"
#endif

//superclass frame for all subframes
class Frame : public General_Frame{

protected:

  //container for all objects
  SDL_Event* main_event = NULL;
  SDL_Renderer* intern_renderer = NULL;
  SDL_Color background_color;

public:

  Frame* next_frame = NULL;

  //constructors
  Frame();
  Frame(SDL_Event*, SDL_Renderer*, SDL_Color&);
  Frame(std::vector<PhysicObject*>&, SDL_Event*, SDL_Renderer*, SDL_Color&);

  virtual ~Frame();

};

Frame::Frame() : General_Frame(){

}

Frame::Frame(SDL_Event* evt, SDL_Renderer* r, SDL_Color& c) : General_Frame(){

  main_event = evt;
  intern_renderer = r;
  background_color = c;

}

Frame::Frame(std::vector<PhysicObject*>& objs, SDL_Event* evt, SDL_Renderer* r, SDL_Color& c) : General_Frame(objs){

  main_event = evt;
  intern_renderer = r;
  background_color = c;

}

Frame::~Frame(){

}



#endif
