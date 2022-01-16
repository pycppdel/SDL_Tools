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
#include "hitbox.h"
#endif

#include <vector>

//standard definitions for the slowdown and the standard boundary
#define STANDARD_SLOWDOWN 3.0F
#define STANDARD_BOUNDARY_RIGHT 1920
#define STANDARD_MAX_SPEED 100.0F

class PhysicObject{

private:


  //for updating hitboxes
  virtual void update_hitboxes();

public:

  enum Direction{

    LEFT,
    RIGHT,
    UNDECIDED

  };
  //coordinates
  int x, y;
  int width, height;

  float x_vel, y_vel; //velocity

  //friction
  float slow_down;

  //for sliding
  bool sliding;
  bool can_slide;

  //for wall bouncing
  bool can_wall_bounce;

  //falling variables
  bool is_falling = false;
  bool can_fall = true;

  //standing variable
  bool is_standing_on_something = false;

  //boundaries
  int boundary_left, boundary_right;
  bool has_bounds;

  //ghost object means that other objects can pass through it without interacting
  bool ghost_object = false;

  //general direction
  Direction direction;

  //defines the maximum of speed the object can reach, or if it has a max speed
  bool has_max_speed = false;
  float max_speed = STANDARD_MAX_SPEED;

  //all hitboxes from the object
  std::vector<Hitbox> hitboxes;

  PhysicObject();
  PhysicObject(int, int, int, int);
  PhysicObject(int, int, int, int, float);
  PhysicObject(int, int, int, int, bool);

  virtual ~PhysicObject();

  bool hits(PhysicObject&);
  void add_hitbox(int, int, int, int);

  virtual void move_left(int);
  virtual void move_right(int);
  virtual void draw(SDL_Renderer*)=0;
  virtual void on_frame();
  virtual void set_boundaries(int, int);


};

PhysicObject::PhysicObject(int x, int y, int w, int h){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;

  slow_down = STANDARD_SLOWDOWN;
  sliding = false;
  can_slide = true;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;
  can_wall_bounce = false;


}

PhysicObject::PhysicObject(int x, int y, int w, int h, float slow){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->slow_down = slow;

  slow_down = slow;
  sliding = false;
  can_slide = true;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;
  can_wall_bounce = false;

}

PhysicObject::PhysicObject(int x, int y, int w, int h, bool can_slide){

  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;

  slow_down = STANDARD_SLOWDOWN;
  sliding = false;
  this->can_slide = can_slide;
  direction = UNDECIDED;
  boundary_left = 0;
  boundary_right = STANDARD_BOUNDARY_RIGHT;
  has_bounds = true;
  can_wall_bounce = false;

}

PhysicObject::~PhysicObject(){

  //deletes all added and generated hitboxes


  for(Hitbox& h : hitboxes){

    h.~Hitbox();
    //consider deleting

  }

  hitboxes.clear();


}

bool PhysicObject::hits(PhysicObject& other){

  //goes in a loop inside all hitboxes and checks if they hit

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

  //adds a hitbox, that will be removed by the destructor
  //hitbox will be offset from the x and y coordinate of the object
  Hitbox* neu = new Hitbox(x_, y_, w, h);
  neu->x += x;
  neu->y -= y;

  hitboxes.push_back(*neu);


}

void PhysicObject::move_left(int speed){

  //moves left

  //if boundaries:
  if(has_bounds){

    //if doesnt hit boundarie
    if(x > boundary_left){
      //go left
      x_vel -= speed;
      direction = LEFT;

    }

  }
  else{
    //no bound: go anyways
    x_vel -= speed;
    direction = LEFT;
  }

}

void PhysicObject::update_hitboxes(){

  //updates hitboxes according to the last x and y they have been
  for (Hitbox& box : hitboxes){


    box.x = box.x_save+x;
    box.y = y-box.y_save;



  }



}

void PhysicObject::move_right(int speed){

  //moves right

  //if has bounds
  if(has_bounds){

    //if hits the boundarie right
    if(x+width < boundary_right){

      //move right
      x_vel += speed;
      direction = RIGHT;

    }

  }

  else{

    //also move right
    x_vel += speed;
    direction = RIGHT;

  }

}

void PhysicObject::on_frame(){


  //does everything that should be done on the frame

  //change velocities, depending on max_speed
  if (has_max_speed){

    //max speed was broken: fixing by adjusting
    if(x_vel > 0 && x_vel > max_speed){
      x_vel = max_speed;
    }
    else if(x_vel < 0 && x_vel < -max_speed){

      x_vel = -max_speed;

    }

  }

  x += static_cast<int>(x_vel);
  y += static_cast<int>(y_vel);

  //if cant slide, set the x_velocity to zero
  if (!can_slide){

    x_vel = 0;

  }

  else{

    //let it slide

      //if boundaries available:
      if(has_bounds){

        //check if anything hits them
        if (x+x_vel < boundary_left || x+x_vel+width > boundary_right){

          if (can_wall_bounce){

            //if can bounce, bounce

            x_vel = -x_vel;

            //if it was hitting, invert the velocity and switch the direction

            switch(direction){

              case LEFT:

                    direction = RIGHT;
                    break;
              case RIGHT:
                    direction = LEFT;
                    break;
            }

          }

          else{

            x_vel = 0;

          }

        }
      }

    //do standard stuff

    switch(direction){


      case LEFT:

            //slow down, and check if you stopped
            //if stopped, set x_vel to zero

            x_vel += slow_down;
            if(x_vel >= 0){

              x_vel = 0;
              direction = UNDECIDED;


            }
            break;

      case RIGHT:

      //slow down, and check if you stopped
      //if stopped, set x_vel to zero

            x_vel -= slow_down;
            if(x_vel <= 0){
              x_vel = 0;
              direction = UNDECIDED;
            }
            break;
    }


  }

  if (x_vel == 0){

    direction = UNDECIDED;


  }
  else if(x_vel < 0){

    direction = LEFT;

  }
  else if(x_vel > 0){

    direction = RIGHT;

  }

  //updating the hitboxes
  update_hitboxes();

}

void PhysicObject::set_boundaries(int bn, int bf){

  //sets the boundaries

  has_bounds = true;
  boundary_left = bn;
  boundary_right = bf;

}


#endif
