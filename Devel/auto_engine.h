/*
*
*
* Automated object_engine specifically for SDL
*
*
*/

#ifndef __SDL_TOOLS_AUTO_ENGINE__
#define __SDL_TOOLS_AUTO_ENGINE__

#ifndef _SDL_H
#include "SDL.h"
#endif

#ifndef __SDL_TOOLS_OBJECT_ENGINE__
#include "../Physic/object_engine.h"
#endif

#ifndef __SDL_TOOLS_TIMER__
#include "../timer.h"
#endif

#include <iostream>

#define STANDARD_FPS 60
#define STANDARD_COLOR {0xFF,0xFF,0xFF}



class Auto_Engine : public Object_Engine{

protected:

  SDL_Color background_color = STANDARD_COLOR;
  SDL_Renderer* intern_renderer = NULL;

public:


  Auto_Engine();
  Auto_Engine(Camera*);
  Auto_Engine(SDL_Color&);
  Auto_Engine(SDL_Color&, SDL_Renderer*);
  Auto_Engine(Camera*, SDL_Color&, SDL_Renderer*);
  //for copying from vector
  Auto_Engine(std::vector<PhysicObject*>&);
  Auto_Engine(std::vector<PhysicObject*>&, Camera*);
  Auto_Engine(std::vector<PhysicObject*>&, Camera*, SDL_Color&);
  Auto_Engine(std::vector<PhysicObject*>&, Camera*, SDL_Color&, SDL_Renderer*);

  virtual void execute_all();
  void set_renderer(SDL_Renderer*);
  void set_color(SDL_Color&);

};

Auto_Engine::Auto_Engine() : Object_Engine(){

}

Auto_Engine::Auto_Engine(Camera* cam) : Object_Engine(cam){

}

Auto_Engine::Auto_Engine(Camera* cam, SDL_Color& c, SDL_Renderer* r) : Object_Engine(cam){

  background_color = c;
  intern_renderer = r;

}

Auto_Engine::Auto_Engine(SDL_Color& c) : Object_Engine(){

  background_color = c;

}

Auto_Engine::Auto_Engine(std::vector<PhysicObject*>& obj) : Object_Engine(obj){

}

Auto_Engine::Auto_Engine(std::vector<PhysicObject*>& obj, Camera* cam) : Object_Engine(obj, cam){

}

Auto_Engine::Auto_Engine(std::vector<PhysicObject*>& obj, Camera* cam, SDL_Color& c) : Object_Engine(obj, cam){

background_color = c;

}

Auto_Engine::Auto_Engine(SDL_Color& c, SDL_Renderer* r) : Object_Engine(){

  background_color = c;
  intern_renderer = r;

}

Auto_Engine::Auto_Engine(std::vector<PhysicObject*>& obj, Camera* cam, SDL_Color& c , SDL_Renderer* r) : Object_Engine(obj, cam){

  background_color = c;
  intern_renderer = r;

}

void Auto_Engine::execute_all(){

  load_unload();
  interact();
  on_frame_loaded_objects();

  if(intern_renderer != NULL){
    SDL_SetRenderDrawColor(intern_renderer, background_color.r, background_color.g, background_color.b, 0x0);
    draw_loaded_objects((void*)intern_renderer);
    SDL_SetRenderDrawColor(intern_renderer, background_color.r, background_color.g, background_color.b, 0x0);

  }


}

void Auto_Engine::set_renderer(SDL_Renderer* r){
  intern_renderer = r;
}

void Auto_Engine::set_color(SDL_Color& c){

  background_color = c;

}



Auto_Engine auto_engine(&main_camera);

#endif
