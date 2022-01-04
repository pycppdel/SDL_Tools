/*
*
*
* Implementation of thegroundobject
*
*
*/

#ifndef __SDL_TOOLS_PHYSIC_GROUNDOBJECT__
#define __SDL_TOOLS_PHYSIC_GROUNDOBJECT__

#ifndef __SDL_TOOLS_PHYSIC_OBJECT__
#include <physicobject.h>
#endif

#define GROUND_OBJECT_STANDARD_GRAVITY 1.1F

class GroundObject : public PhysicObject{

public:

  bool is_jumping;
  bool can_jump;
  bool is_falling = false;
  bool can_fall = true;
  float jumpheight, jumpsave;
  float gravity;
  int groundlevel;

  GroundObject(int, int, int, int, int, int);
  GroundObject(int, int, int, int, int, int, int);
  GroundObject(int, int, int, int, int, int, bool);

  virtual void jump(float);
  virtual void fall();

  virtual void on_frame();

};

GroundObject::GroundObject(int x, int y, int h, int w, int size, int ground) : PhysicObject(x, y, w, h, size){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, int slow, int size, int ground) : PhysicObject(x, y, w, h, slow, size){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, int size, int ground, bool can_slow) : PhysicObject(x, y, w, h, can_slow, size){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

void GroundObject::jump(float jumpinit){

  if(!can_jump)return;

  jumpsave = jumpheight = jumpinit;
  is_jumping = true;
  is_falling = true;


}

void GroundObject::fall(){

  if (!can_fall)return;

  if (is_falling){

    if ((y+size+y_vel) > groundlevel){

      is_falling = false;
      is_jumping = false;
      jumpheight = jumpsave = 0;
      y_vel = 0;
      y = groundlevel-size;


    }

    else{

      y_vel += jumpheight+gravity;
      jumpheight += gravity;

    }

  }




}

void GroundObject::on_frame(){

  if ((y+size) < groundlevel){

    is_falling = true;

  }

  if (is_falling){

    fall();

  }

  PhysicObject::on_frame();

}



#endif
