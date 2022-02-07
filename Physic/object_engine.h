/*
*
* Object engine for all objects involved
*
*
*
*/

#ifndef __SDL_TOOLS_OBJECT_ENGINE__
#define __SDL_TOOLS_OBJECT_ENGINE__

#include <vector>

#ifndef __SDL_TOOLS_PHYSIC_OBJECT__
#include "physicobject.h"
#endif

#ifndef __SDL_TOOLS_CAMERA__
#include "../camera.h"
#endif

#ifndef __SDL_TOOLS_PHYSIC_HITBOX__
#include "hitbox.h"
#endif

#define NO_TOLERANCE 0
#define STABILITY_FACTOR 2

#include <iostream>

class PhysicLayerComparator : public Comparator<PhysicObject*, PhysicObject*>{

public:

  PhysicLayerComparator();
  int compare(PhysicObject*, PhysicObject*);

};

PhysicLayerComparator::PhysicLayerComparator(){

}

int PhysicLayerComparator::compare(PhysicObject* a, PhysicObject* b){

  if(a->layer < b->layer)return -1;
  if(a->layer > b->layer)return 1;
  return 0;

}

class Object_Engine{

private:

  //container for loaded objects
  std::vector<PhysicObject*> loaded_objects;
  //container for unloaded objects
  std::vector<PhysicObject*> unloaded_objects;

  //pointer to the relevant camera
  Camera* camera_ptr = NULL;

protected:

  virtual bool check_x_hit(Hitbox&, Hitbox&);
  virtual bool check_y_hit(Hitbox&, Hitbox&);

  virtual void insert_ordered_loaded(PhysicObject*);
  virtual void insert_ordered_unloaded(PhysicObject*);

  PhysicLayerComparator layer_comparator;

public:

  //load tolerance for loading and unloading objects
  int x_load_tolerance = NO_TOLERANCE;
  int y_load_tolerance = NO_TOLERANCE;

  Object_Engine();
  Object_Engine(Camera*);
  //for copying all object of an array
  Object_Engine(PhysicObject**, int);
  Object_Engine(PhysicObject**, int, Camera*);
  //for copying from vector
  Object_Engine(std::vector<PhysicObject*>&);
  Object_Engine(std::vector<PhysicObject*>&, Camera*);
  //destructor
  virtual ~Object_Engine();


  void change_camera(Camera*);

  void register_object(PhysicObject*);
  void unregister_object(PhysicObject*);

  void load_object(PhysicObject*);
  void unload_object(PhysicObject*);

  //makes all the stuff happen
  virtual void interact();
  //loads in via camera and the tolerance, also unloads object that are not in the focus
  virtual void load_unload();
  //resorts the layers
  virtual void resort_layer_wise();

  //gives back the list of all loaded objects
  std::vector<PhysicObject*>* get_loaded_objects();
  std::vector<PhysicObject*>* get_unloaded_objects();

  //for drawing and framing loaded objects
  void draw_loaded_objects(void*);
  void on_frame_loaded_objects();


};

Object_Engine::Object_Engine(){

}

Object_Engine::Object_Engine(Camera* cam){

  camera_ptr = cam;

}

Object_Engine::Object_Engine(PhysicObject** object_container, int size){

  //copying all in unloaded
  for(int i = 0; i < size; i++){

    unloaded_objects.push_back(object_container[i]);

  }

}

Object_Engine::Object_Engine(PhysicObject** object_container, int size, Camera* cam){

  //copying all in unloaded
  for(int i = 0; i < size; i++){

    unloaded_objects.push_back(object_container[i]);

  }

  camera_ptr = cam;

}

Object_Engine::Object_Engine(std::vector<PhysicObject*>& container){

  for(PhysicObject* obj : container){

    unloaded_objects.push_back(obj);

  }

}

Object_Engine::Object_Engine(std::vector<PhysicObject*>& container, Camera* cam){

  for(PhysicObject* obj : container){

    unloaded_objects.push_back(obj);

  }

  camera_ptr = cam;

}


Object_Engine::~Object_Engine(){

}


void Object_Engine::change_camera(Camera* cam){

  camera_ptr = cam;

}

void Object_Engine::register_object(PhysicObject* obj){

  //if the object was registered before, unregister it
  unregister_object(obj);

  insert_ordered_unloaded(obj);

}

void Object_Engine::unregister_object(PhysicObject* obj){

  //searches for the object, then unloads it
  std::vector<PhysicObject*>::iterator it;

  //searching in unloaded objects
  it = unloaded_objects.begin();

  while (it != unloaded_objects.end() && (*it) != obj){

    it++;

  }

  if (it != unloaded_objects.end()){

    //found, now removing
    unloaded_objects.erase(it);
    return;

  }

  //else, search in loaded objects
  it = loaded_objects.begin();

  while (it != loaded_objects.end() && (*it) != obj){

    it++;

  }

  if (it != loaded_objects.end()){

    //found, removing
    loaded_objects.erase(it);
    return;
  }

}

void Object_Engine::load_object(PhysicObject* obj){

  //can only load an object if its registered
  //searches for the object, then unloads it
  std::vector<PhysicObject*>::iterator it;

  //searching in unloaded objects
  it = unloaded_objects.begin();

  while (it != unloaded_objects.end() && (*it) != obj){

    it++;

  }

  if(it != unloaded_objects.end()){

    //insert into loaded
    unloaded_objects.erase(it);

    insert_ordered_loaded(obj);

  }

}

void Object_Engine::unload_object(PhysicObject* obj){

  //can only load an object if its registered
  //searches for the object, then unloads it
  std::vector<PhysicObject*>::iterator it;

  //searching in unloaded objects
  it = loaded_objects.begin();

  while (it != loaded_objects.end() && (*it) != obj){

    it++;

  }

  if(it != loaded_objects.end()){

    //insert into loaded
    loaded_objects.erase(it);

    insert_ordered_unloaded(obj);

  }

}

void Object_Engine::draw_loaded_objects(void* rend){

  for (PhysicObject* obj : loaded_objects){

    obj->draw(rend);

  }

}

void Object_Engine::on_frame_loaded_objects(){

  for(PhysicObject* obj : loaded_objects){

    obj->on_frame();

  }
  for(PhysicObject* obj : unloaded_objects){

    obj->on_frame();

  }

}

void Object_Engine::interact(){

  //lets all the objects interact

  for(PhysicObject* obj : loaded_objects){

    //variables for saving the last position point
    int coming_from_left_hit_x = 0;
    bool got_coming_from_left = false; //if hit previously

    //variables for coming from right
    int coming_from_right_hit_x = 0;
    bool got_coming_from_right = false;

    //variables for lowest box
    int coming_from_above_y = 0;
    bool got_coming_from_above = false;

    //variables for lowest box
    int coming_from_below_y = 0;
    bool got_coming_from_below = false;

    bool standing = false;

    for (PhysicObject* counter : loaded_objects){


      //if there is a ghost object, ignore it
      if (counter->ghost_object || counter==obj) {continue;}
      //search for counterparts
      //to check a left hit: find the smallest element that is on the right side of the object

      //comparing the hitboxes
      for (Hitbox& obj_h : obj->hitboxes){

        for(Hitbox& counter_h : counter->hitboxes){

          //iterating through all hitboxes

          //checking if jumps against hitbox from below
          if(

            (!got_coming_from_above || (counter_h.y+counter_h.height >= coming_from_above_y))
            //checking if before was below, but now is above
            &&
            (obj_h.y) >= (counter_h.y+counter_h.height)
            &&
            (obj_h.y+obj->y_vel) <= (counter_h.y+counter_h.height)
            &&
            //inside object
            (
            ((obj_h.x >= counter_h.x && obj_h.x <= counter_h.x+counter_h.width)
            ||
            (obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width))
            ||

            (counter_h.width < obj_h.width &&
              (counter_h.x >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
              ||
              (counter_h.x < obj_h.x && counter_h.x+counter_h.width >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
          )
            ||

            (obj_h.width < counter_h.width &&
              (obj_h.x >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
            ||
            (obj_h.x < counter_h.x && obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
          )
          )

          ){

            coming_from_above_y = counter_h.y+counter_h.height;
            got_coming_from_above = true;
            //set y vel opposite
            obj->y = (counter_h.y+counter_h.height);
            if(obj->can_bounce){
              obj->y_vel = -(obj->y_vel*obj->y_vel_above_hit_inverter);
            }
            else{
              obj->y_vel = 0;
            }

          }
          //checking for hit from above

          //checking for above hit

          if(
            (!got_coming_from_below || (counter_h.y <= coming_from_below_y))
            &&
            (
            (obj_h.y+obj_h.height <= counter_h.y && obj_h.y+obj_h.height+obj->y_vel > counter_h.y)
            )
            &&
            (((obj_h.x >= counter_h.x && obj_h.x <= counter_h.x+counter_h.width)
            ||
            (obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width))
            ||
            (counter_h.width < obj_h.width && (
              (counter_h.x >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
              ||
              (counter_h.x < obj_h.x && counter_h.x+counter_h.width >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
          ))
            ||

            (obj_h.width < counter_h.width &&(
              (obj_h.x >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
            ||
            (obj_h.x < counter_h.x && obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
          ))
          )

          ){



            obj->is_standing_on_something = true;
            obj->y_vel = 0;
            obj->is_jumping = false;
            obj->y = (counter_h.y-obj_h.height);
            got_coming_from_below = true;
            coming_from_below_y = counter_h.y;

          }

          if(
            (!got_coming_from_below || (counter_h.y <= coming_from_below_y))
            &&
            ((obj_h.y+obj_h.height == counter_h.y ))
            &&
            (((obj_h.x >= counter_h.x && obj_h.x <= counter_h.x+counter_h.width)
            ||
            (obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width))
            ||
            (counter_h.width < obj_h.width &&(
              (counter_h.x >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
              ||
              (counter_h.x < obj_h.x && counter_h.x+counter_h.width >= obj_h.x && counter_h.x+counter_h.width <= obj_h.x+obj_h.width)
          ))
            ||

            (obj_h.width < counter_h.width &&(
              (obj_h.x >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
            ||
            (obj_h.x < counter_h.x && obj_h.x+obj_h.width >= counter_h.x && obj_h.x+obj_h.width <= counter_h.x+counter_h.width)
          ))
          )

          ){

            if(!obj->is_jumping){

              obj->y_vel = 0;
              obj->y = (counter_h.y-obj_h.height);
              obj->is_standing_on_something = true;

            }
            got_coming_from_below = true;
            coming_from_below_y = counter_h.y;

          }






          //checking for a right hit

          if(


            // hits right if: hitbox is greater, of counter part is the rightest, and y value corresponds
            (!got_coming_from_right || (counter_h.x+counter_h.width >= coming_from_right_hit_x))
            &&
            //if first bigger, but after moving smaller
            (obj_h.x) >= (counter_h.x+counter_h.width)
            &&
            //smaller:
            (obj_h.x + obj->x_vel) < (counter_h.x+counter_h.width)
            &&
            //and inside the object
            (((obj_h.y > counter_h.y && obj_h.y < counter_h.y+counter_h.height)
            ||
            (obj_h.y+obj_h.height > counter_h.y && obj_h.y+obj_h.height < counter_h.y+counter_h.height)
            )
            ||
            (counter_h.height < obj_h.height &&(
              (counter_h.y > obj_h.y && counter_h.y+counter_h.height < obj_h.y+obj_h.height)
              ||
              (counter_h.y < obj_h.y && counter_h.y+counter_h.height > obj_h.y && counter_h.y+counter_h.height < obj_h.y+obj_h.height)
            )
            )
            ||
            (obj_h.height < counter_h.height && ((obj_h.y > counter_h.y && obj_h.y+obj_h.height < counter_h.y +counter_h.height)
            ||
            (obj_h.y < counter_h.y && obj_h.y+obj_h.height > counter_h.y && obj_h.y+obj_h.height < counter_h.y+counter_h.height)
          )
          )
          )
          )
          {

            got_coming_from_right = true;
            coming_from_right_hit_x = counter_h.x+counter_h.width;
            if (counter->left_moveable){
              //counter->x = obj_h.x-counter_h.width;
              counter->x_vel = obj->x_vel+STABILITY_FACTOR;
            }

            if (!obj->can_wall_bounce){

              //stop the object
              obj->x_vel = 0;
              obj->x = counter_h.x+counter_h.width;

            }
            else{

              obj->x_vel = -obj->x_vel;

            }



          }




          //checking for a hit while walking right
          if (

            //if is first smaller, but after adding the x_velocity it hits the object, and the object is smallest, and y value corresponds: left hit

            //checking if smallest
            (!got_coming_from_left || (counter_h.x <= coming_from_left_hit_x))
            &&
            //if first smaller, but after moving bigger
            (obj_h.x + obj_h.width) <= (counter_h.x)
            &&
            //after bigger
            (obj_h.x +  obj_h.width + obj->x_vel) > (counter_h.x)
            &&
            //and inside the object
            (((obj_h.y > counter_h.y && obj_h.y < counter_h.y+counter_h.height)
            ||
            (obj_h.y+obj_h.height > counter_h.y && obj_h.y+obj_h.height < counter_h.y+counter_h.height)
            )
            ||
            (counter_h.height < obj_h.height &&(
              (counter_h.y > obj_h.y && counter_h.y+counter_h.height <= obj_h.y+obj_h.height)
              ||
              (counter_h.y < obj_h.y && counter_h.y+counter_h.height >= obj_h.y && counter_h.y+counter_h.height <= obj_h.y+obj_h.height)
            )
            )
            ||
            (obj_h.height < counter_h.height && ((obj_h.y > counter_h.y && obj_h.y+obj_h.height < counter_h.y +counter_h.height)
            ||
            (obj_h.y < counter_h.y && obj_h.y+obj_h.height > counter_h.y && obj_h.y+obj_h.height < counter_h.y+counter_h.height)
          )
          )
          )


          )
          {

            //then: left hitting

            got_coming_from_left = true;
            coming_from_left_hit_x = counter_h.x;
            if (counter->right_moveable){
              //counter->x = obj_h.x+obj_h.width;
              counter->x_vel = obj->x_vel-STABILITY_FACTOR;
            }

            //now, is left hitting:
            //if cant wall bounce: stop
            if (!obj->can_wall_bounce){

              //stop the object
              obj->x_vel = 0;
              obj->x = counter_h.x-obj->width;

              //if didnt crash



            }
            else{

              obj->x_vel = -obj->x_vel;

            }


          }


        }

      }


    }

    if (!got_coming_from_below){

      obj->is_standing_on_something = false;

    }


  }

}

void Object_Engine::load_unload(){

  //loads or unloads according to the camera position

  //if the object isnt inside the camera view, it needs to be unloaded
  for(int i = 0; i < loaded_objects.size(); i++){

    PhysicObject* obj = loaded_objects[i];

    if (

      obj->x+obj->width <= camera_ptr->x-x_load_tolerance
      ||
      obj->x >= camera_ptr->x+camera_ptr->w+x_load_tolerance
      ||
      obj->y+obj->height <= camera_ptr->y-y_load_tolerance
      ||
      obj->y >= camera_ptr->y+camera_ptr->h+y_load_tolerance

    ){

      unload_object(obj);

    }

  }


  for(int i = 0; i < unloaded_objects.size(); i++){

    PhysicObject* obj = unloaded_objects[i];

    if (

      !(obj->x+obj->width <= camera_ptr->x-x_load_tolerance
      ||
      obj->x >= camera_ptr->x+camera_ptr->w+x_load_tolerance
      ||
      obj->y+obj->height <= camera_ptr->y-y_load_tolerance
      ||
      obj->y >= camera_ptr->y+camera_ptr->h+y_load_tolerance
    )

    ){

      load_object(obj);


    }

  }

}

std::vector<PhysicObject*>* Object_Engine::get_loaded_objects(){

  //gives back loaded objects
  return &loaded_objects;

}

std::vector<PhysicObject*>* Object_Engine::get_unloaded_objects(){

  //gives back the unloaded objects
  return &unloaded_objects;

}

void Object_Engine::insert_ordered_loaded(PhysicObject* obj){

  std::vector<PhysicObject*>::iterator ite = loaded_objects.begin();

  //could be slow
  while (ite != loaded_objects.end()){

    ite++;
    try{
      int layer = (*ite)->layer;

      if(obj->layer <= layer){
        break;
      }

    }
    catch(...){

    }

  }

  loaded_objects.insert(ite, obj);

}

void Object_Engine::insert_ordered_unloaded(PhysicObject* obj){

  std::vector<PhysicObject*>::iterator it = unloaded_objects.begin();

  //could be slow
  while (it != unloaded_objects.end()){

    it++;
    try{
      int layer = (*it)->layer;

      if(obj->layer <= layer){
        break;
      }

    }
    catch(...){

    }

  }

  unloaded_objects.insert(it, obj);

}

bool Object_Engine::check_x_hit(Hitbox& obj_h, Hitbox& counter_h){

  return false;

}

bool Object_Engine::check_y_hit(Hitbox& obj_h, Hitbox& counter_h){

  return ((obj_h.y >= counter_h.y && obj_h.y <= counter_h.y+counter_h.height)
  ||
  (obj_h.y+obj_h.height >= counter_h.y && obj_h.y+obj_h.height <= counter_h.y+counter_h.height));
}

void Object_Engine::resort_layer_wise(){

  insertion_sort(&loaded_objects, (Comparator<PhysicObject*, PhysicObject*>*)&layer_comparator);
  insertion_sort(&unloaded_objects, (Comparator<PhysicObject*, PhysicObject*>*)&layer_comparator);

}

Object_Engine standard_engine(&main_camera);

#endif
