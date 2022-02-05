/*
*
* Static object. can not be moved or move itself
*
*/

#ifndef __SDL_TOOLS_STATIC_OBJECT__
#define __SDL_TOOLS_STATIC_OBJECT__

#ifndef __SDL_TOOLS_PHYSIC_GROUNDOBJECT__
#include "groundobject.h"
#endif

class StaticObject : public GroundObject{

public:

  StaticObject(int, int, int, int); //standard constructor

  void jump();
  void on_frame();
  void fall();


};

StaticObject::StaticObject(int x, int y, int w, int h) : GroundObject(x, y, w, h, 0){

  gravity = 0;
  can_fall = false;
  can_wall_bounce = false;
  can_jump = false;
  has_bounds = false;
  can_go_right = false;
  can_go_left = false;
  can_bounce = false;
  left_moveable = false;
  right_moveable = false;

}

void StaticObject::jump(){

}

void StaticObject::on_frame(){

  if(left_moveable){
    left_moveable = false;
  }
  if(right_moveable){
    right_moveable = false;
  }
  if(can_fall){
    can_fall = false;
  }
  if(can_go_left){
    can_go_left = false;
  }
  if(can_go_right){
    can_go_right = false;
  }

}

void StaticObject::fall(){
  
}

#endif
