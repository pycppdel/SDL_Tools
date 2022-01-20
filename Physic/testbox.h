/*
*
* Testobject for groundobject
*
*
*
*/


#ifndef __SDL_TOOLS_PHYSIC_TESTBOX__
#define __SDL_TOOLS_PHYSIC_TESTBOX__

#ifndef __SDL_TOOLS_PHYSIC_GROUNDOBJECT__
#include "groundobject.h"
#endif

#ifndef __SDL_TOOLS_CAMERA__
#include "../camera.h"
#endif

class Testbox : public GroundObject{

public:

  SDL_Rect pos;
  SDL_Color c;

  Testbox(int, int, int, int, int, SDL_Color&);
  Testbox();
  virtual ~Testbox();
  void draw(void*);

  void on_frame();

};

Testbox::Testbox() : GroundObject(0, 0, 0, 0, 0){

}


Testbox::Testbox(int x, int y, int w, int h, int ground, SDL_Color& cl) : GroundObject(x, y, w, h, ground){

  c = cl;
  pos.x = x;
  pos.y = y;
  pos.w = w;
  pos.h = h;
  gravity = 0.5F;

}

Testbox::~Testbox(){

}



void Testbox::draw(void* re){

  SDL_Renderer* r = static_cast<SDL_Renderer*>(re);

  SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 0x0);
  SDL_RenderFillRect(r, &pos);

}

void Testbox::on_frame(){

  GroundObject::on_frame();
  pos.x = x-main_camera.x;
  pos.y = y-main_camera.y;
  pos.w = width;
  pos.h = height;

}


#endif
