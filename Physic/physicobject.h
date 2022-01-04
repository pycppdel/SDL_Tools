/*
*
*
* Implementation of the superclass of all physic objects
*
*
*/

#ifndef __SDL_TOOLS_PHYSIC_OBJECT__
#define __SDL_TOOLS_PHYSIC_OBJECT__

#ifndef __SDL_TOOLS_PHYSIC_HITBOX__
#include <hitbox.h>
#endif

#include <vector>

class PhysicObject{

public:

  int x, y;
  float x_vel, y_vel; //velocity
  int size;
  int width, height;
  int slow_down;
  bool sliding;
  bool can_slide;

  std::vector<Hitbox> hitboxes;

  PhysicObject();
  PhysicObject(int, int, int, int, int);
  PhysicObject(int, int, int, int, int, int);
  PhysicObject(int, int, int, int, int, bool);

  virtual ~PhysicObject();

  bool hits(PhysicObject&);
  void add_hitbox(int, int, int, int);

  virtual void move_left(int);
  virtual void move_right(int);
  virtual void draw(SDL_Renderer*)=0;
  virtual void on_frame();

};

PhysicObject::PhysicObject(int x, int y, int w, int h, int size){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->size = size;

  slow_down = 0;
  sliding = false;
  can_slide = true;

}

PhysicObject::PhysicObject(int x, int y, int w, int h, int slow, int size){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->slow_down = slow;
  this->size = size;

  slow_down = 0;
  sliding = false;
  can_slide = true;

}

PhysicObject::PhysicObject(int x, int y, int w, int h, int size, bool can_slide){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->size = size;

  slow_down = 0;
  sliding = false;
  this->can_slide = can_slide;

}

PhysicObject::~PhysicObject(){

  for(Hitbox& h : hitboxes){

    h.~Hitbox();
    delete &h;

  }

  hitboxes.clear();

}

bool PhysicObject::hits(PhysicObject& other){

  for(Hitbox& oh : other.hitboxes){

    for(Hitbox& h : hitboxes){

      if(h.hits(oh)){

        return true;

      }

    }

  }

  return false;

}

void PhysicObject::add_hitbox(int x_, int y_, int w, int h){

  Hitbox* neu = new Hitbox(x_, y_, w, h);

  hitboxes.push_back(*neu);


}

void PhysicObject::move_left(int speed){

  x_vel -= speed;

}

void PhysicObject::move_right(int speed){

  x_vel += speed;

}

void PhysicObject::on_frame(){

  x += static_cast<int>(x_vel);
  y += static_cast<int>(y_vel);

  if (!can_slide){

    x_vel = y_vel = 0;

  }

  else{

    x_vel -= slow_down;
    y_vel -= slow_down;

    x_vel = (x_vel < 0) ? 0 : x_vel;
    y_vel = (y_vel < 0) ? 0 : y_vel;

  }

}


#endif
