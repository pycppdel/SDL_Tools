/*
*
*General purpose frame for loading
*
*/
#ifndef __SDL_TOOLS_DEVEL_GENERAL_PURPOSE_FRAME__
#define __SDL_TOOLS_DEVEL_GENERAL_PURPOSE_FRAME__

#ifndef __ALL_PHYSICS_IMPORT__
#include "../Physic/physic.h"
#endif

#ifndef __SDL_TOOLS_AUTO_ENGINE__
#include "auto_engine.h"
#endif

class General_Frame{

protected:

  std::vector<PhysicObject*> objects;

public:

  General_Frame* next_frame = NULL;

  General_Frame();
  General_Frame(std::vector<PhysicObject*>&);

  virtual ~General_Frame();
  virtual void execute_all()=0;

  //loading operations
  void load_into(Object_Engine*);
  void load_into(Auto_Engine*);

  void unload_from(Object_Engine*);
  void unload_from(Auto_Engine*);

};

General_Frame::General_Frame(){

}

General_Frame::General_Frame(std::vector<PhysicObject*>& objs){

  for (PhysicObject* obj : objs){

    objects.push_back(obj);

  }

}

General_Frame::~General_Frame(){

}

void General_Frame::load_into(Object_Engine* engine){

  for (PhysicObject* obj : objects){

    engine->register_object(obj);

  }

}

void General_Frame::load_into(Auto_Engine* engine){

  for (PhysicObject* obj : objects){

    engine->register_object(obj);

  }

}

void General_Frame::unload_from(Object_Engine* engine){

  for(PhysicObject* obj : objects){

    engine->unregister_object(obj);

  }

}

void General_Frame::unload_from(Auto_Engine* engine){

  for(PhysicObject* obj : objects){

    engine->unregister_object(obj);

  }

}

#endif
