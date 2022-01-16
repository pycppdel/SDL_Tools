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
#include "physicobject.h"
#endif


//standard definitions
#define GROUND_OBJECT_STANDARD_GRAVITY 1.1F
#define STANDARD_GROUND_BOUNCE_STOP 8.0F
#define STANDARD_MAX_FALL_SPEED 60.0F

class GroundObject : public PhysicObject{

public:

  //jumping vairables
  bool is_jumping;
  bool can_jump = true;

  //falling variables
  bool is_falling = false;
  bool can_fall = true;

  //for ground bouncing
  bool can_bounce = true;
  float ground_bounce_stop = STANDARD_GROUND_BOUNCE_STOP;

  //definition variables for ground
  float gravity;
  int groundlevel;

  //max speed for falling
  float has_max_fall_speed = false;
  float max_fall_speed = STANDARD_MAX_FALL_SPEED;

  //constructors

  GroundObject(int, int, int, int, int);
  GroundObject(int, int, int, int, float, int);
  GroundObject(int, int, int, int, int, bool);

  //object can jump and fall and does its stuff on the frame
  virtual void jump(float);
  virtual void fall();

  virtual void on_frame();

};

GroundObject::GroundObject(int x, int y, int h, int w, int ground) : PhysicObject(x, y, w, h){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, float slow, int ground) : PhysicObject(x, y, w, h, slow){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

GroundObject::GroundObject(int x, int y, int h, int w, int ground, bool can_slow) : PhysicObject(x, y, w, h, can_slow){

  this->groundlevel = ground;
  this->gravity = GROUND_OBJECT_STANDARD_GRAVITY;

}

void GroundObject::jump(float jumpinit){

  if(!can_jump)return;

  //checking for negativity

  y_vel = (jumpinit > 0) ? -jumpinit : jumpinit;

  //setting status variables
  is_jumping = true;
  is_falling = true;


}

void GroundObject::fall(){

  //if cannot fall, nothing will be changed
  if (!can_fall)return;


  if (is_falling){

    //if falling

    //if hit the ground
    if ((y+height+y_vel) > groundlevel){

      //if cant bounce: stop, reset status variables and be still
      if(!can_bounce){

        is_falling = false;
        is_jumping = false;
        y_vel = 0;
        y = groundlevel-height;

      }
      else{
        //if can bounce, bounce opposite
        float pos_y_vel = (y_vel < 0) ? -y_vel : y_vel;

        if(pos_y_vel < ground_bounce_stop*gravity){
          //if bouncing critical point was reached: stop bouncing
          y_vel = 0;
          is_falling = false;
          y = groundlevel-height;
          is_jumping = false;

        }
        else{
          //else bounce, but not jumping
          y_vel = -y_vel;
          is_jumping = false;

        }
      }



    }
    else{
      //else: change y_vel
      y_vel += gravity;
    }

    //checking for faster acceleration than planned:

    if (has_max_fall_speed && y_vel > max_fall_speed){

      y_vel = max_fall_speed;

    }


  }





}

void GroundObject::on_frame(){

  //if is in the air: fall
  if ((y+height) < groundlevel){

    is_falling = true;

  }

  //if falling: call defined method
  if (is_falling){

    fall();

  }

  //do x_vel stuff
  PhysicObject::on_frame();


}



#endif
