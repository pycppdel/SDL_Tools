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

#define NO_TOLERANCE 0

class Object_Engine{

private:

  //container for loaded objects
  std::vector<PhysicObject*> loaded_objects;
  //container for unloaded objects
  std::vector<PhysicObject*> unloaded_objects;

  //pointer to the relevant camera
  Camera* camera_ptr = NULL;

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

  //gives back the list of all loaded objects
  std::vector<PhysicObject*>* get_loaded_objects();
  std::vector<PhysicObject*>* get_unloaded_objects();

  //for drawing and framing loaded objects
  void draw_loaded_objects(SDL_Renderer*);
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

  unloaded_objects.push_back(obj);

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
    loaded_objects.push_back(obj);

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
    unloaded_objects.push_back(obj);

  }

}

void Object_Engine::draw_loaded_objects(SDL_Renderer* rend){

  for (PhysicObject* obj : loaded_objects){

    obj->draw(rend);

  }

}

void Object_Engine::on_frame_loaded_objects(){

  for(PhysicObject* obj : loaded_objects){

    obj->on_frame();

  }

}

void Object_Engine::interact(){

  //lets all the objects interact

  for(PhysicObject* obj : loaded_objects){

    for (PhysicObject* counter : loaded_objects){

      //search for counterparts

      //if there is a ghost object, ignore it
      if (counter->ghost_object) {continue;}

    }

  }
}

void Object_Engine::load_unload(){

  //loads or unloads according to the camera position

}

std::vector<PhysicObject*>* Object_Engine::get_loaded_objects(){

  //gives back loaded objects
  return &loaded_objects;

}

std::vector<PhysicObject*>* Object_Engine::get_unloaded_objects(){

  //gives back the unloaded objects
  return &unloaded_objects;

}

Object_Engine standard_engine(&main_camera);

#endif
