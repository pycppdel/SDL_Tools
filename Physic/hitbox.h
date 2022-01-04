/*
*
*
* File for hitbox. Can be used to detect other hitting hitboxes
*
*/

#ifndef __SDL_TOOLS_PHYSIC_HITBOX__
#define __SDL_TOOLS_PHYSIC_HITBOX__


class Hitbox{

public:

  int x, y, width, height;

  Hitbox(int, int, int, int);
  virtual ~Hitbox();

  bool hits(Hitbox&);

};


Hitbox::Hitbox(int x, int y, int w, int h){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;

}

Hitbox::~Hitbox(){

}

bool Hitbox::hits(Hitbox& other){

  bool st1, st2, st3, st4;


  st1 = (x >= other.x && x <= other.x+other.width && y >= other.y && y <= other.y+other.height);
  st2 = (x+width >= other.x && x+width <= other.x+other.width && y >= other.y && y <= other.y+other.height);
  st3 = (x >= other.x && x <= other.x+other.width && y+height >= other.y && y+height <= other.y+other.height);
  st4 = (x+width >= other.x && x+width <= other.x+other.width && y+height >= other.y && y+height <= other.y+other.height);

  return (st1 || st2 || st3 || st4);

}


#endif
