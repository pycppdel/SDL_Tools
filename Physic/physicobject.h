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

#define STANDARD_SLOWDOWN 3.0F
#define STANDARD_BOUNDARY_RIGHT 1920

class PhysicObject{

public:

  enum Direction{

    LEFT,
    RIGHT,
    UNDECIDED

  };

  int x, y;
  float x_vel, y_vel; //velocity
  int size;
  int width, height;
  float slow_down;
  bool sliding;
  bool can_slide;

  int boundary_left, boundary_right;
  bool has_bounds;

  Direction direction;

  std::vector<Hitbox> hitboxes;

  PhysicObject();
  PhysicObject(int, int, int, int, int);
  PhysicObject(int, int, int, int, float, int);
  PhysicObject(int, int, int, int, int, bool);

  virtual ~PhysicObject();

  bool hits(PhysicObject&);
  void add_hitbox(int, int, int, int);

  virtual void move_left(int);
  virtual void move_right(int);
  virtual void draw(SDL_Renderer*)=0;
  virtual void on_frame();
  virtual void set_boundaries(int, int);

};

PhysicObject::PhysicObject(int x, int y, int w, int h, int size){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->size = size;

  slow_down = STANDARD_SLOWDOWN;
  sliding = false;
  can_slide = true;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;


}

PhysicObject::PhysicObject(int x, int y, int w, int h, float slow, int size){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->slow_down = slow;
  this->size = size;

  slow_down = slow;
  sliding = false;
  can_slide = true;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;

}

PhysicObject::PhysicObject(int x, int y, int w, int h, int size, bool can_slide){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->size = size;

  slow_down = STANDARD_SLOWDOWN;
  sliding = false;
  this->can_slide = can_slide;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;

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

  if(x > boundary_left){
    x_vel -= speed;
    direction = LEFT;
  }

}

void PhysicObject::move_right(int speed){

  if(x+size < boundary_right){
    x_vel += speed;
    direction = RIGHT;
  }

}

void PhysicObject::on_frame(){

  x += static_cast<int>(x_vel);
  y += static_cast<int>(y_vel);

  if (!can_slide){

    x_vel = 0;

  }

  else{

      if (x+x_vel < boundary_left || x+x_vel+size > boundary_right){

        x_vel = -x_vel;
        switch(direction){

          case LEFT:

                direction = RIGHT;
                break;
          case RIGHT:
                direction = LEFT;
                break;
        }

      }

    switch(direction){

      case LEFT:

            x_vel += slow_down;
            if(x_vel >= 0){

              x_vel = 0;
              direction = UNDECIDED;


            }
            break;

      case RIGHT:
            x_vel -= slow_down;
            if(x_vel <= 0){
              x_vel = 0;
              direction = UNDECIDED;
            }
            break;
    }


  }

}

void PhysicObject::set_boundaries(int bn, int bf){

  boundary_left = bn;
  boundary_right = bf;

}


#endif
