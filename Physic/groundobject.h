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

#define GROUND_OBJECT_STANDARD_GRAVITY 0.1F
#define STANDARD_GROUND_BOUNCE_STOP 8.0F

class GroundObject : public PhysicObject{

public:

  bool is_jumping;
  bool can_jump = true;
  bool is_falling = false;
  bool can_fall = true;
  bool can_bounce = true;
  float ground_bounce_stop = STANDARD_GROUND_BOUNCE_STOP;
  float jumpheight, jumpsave;
  float gravity;
  int groundlevel;

  GroundObject(int, int, int, int, int, int);
  GroundObject(int, int, int, int, float, int, int);
  GroundObject(int, int, int, int, int, int, bool);

  virtual void jump(float);
  virtual void fall();

  virtual void on_frame();

};

GroundObject::GroundObject(int x, int y, int h, int w, int size, int ground) : PhysicObject(x, y, w, h, size){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, float slow, int size, int ground) : PhysicObject(x, y, w, h, slow, size){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, int size, int ground, bool can_slow) : PhysicObject(x, y, w, h, size, can_slow){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

void GroundObject::jump(float jumpinit){

  if(!can_jump)return;

  jumpheight = jumpinit;
  jumpsave = -jumpheight;
  y_vel = jumpinit;
  is_jumping = true;
  is_falling = true;


}

void GroundObject::fall(){

  if (!can_fall)return;

  if(is_jumping){

    jumpheight += gravity;


  }

  if (is_falling){

    if ((y+size+y_vel) > groundlevel){

      if(!can_bounce){
        is_falling = false;
        is_jumping = false;
        jumpheight = jumpsave = 0;
        y_vel = 0;
        y = groundlevel-size;
      }
      else{
        float pos_y_vel = (y_vel < 0) ? -y_vel : y_vel;
        if(pos_y_vel < ground_bounce_stop*gravity){
          y_vel = 0;
          is_falling = false;
          jumpheight = jumpsave = 0;
          y = groundlevel-size;
          is_jumping = false;

        }
        else{
          y_vel = -y_vel;
          jumpheight = jumpsave = 0;
          is_jumping = false;
        }
      }


    }

    else{

      y_vel += gravity;

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

  if(!is_jumping){
    y_vel = (y_vel <= 0) ? 0 : y_vel;
  }

}



#endif
