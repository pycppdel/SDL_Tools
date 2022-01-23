/*
*
*General purpose frame for loading
*
*/
#ifndef __SDL_TOOLS_DEVEL_GENERAL_PURPOSE_FRAME__
#define __SDL_TOOLS_DEVEL_GENERAL_PURPOSE_FRAME__

class General_Frame{

protected:

  std::vector<PhysicObject*> objects;

public:

  General_Frame* next_frame = NULL;

  General_Frame();
  General_Frame(std::vector<PhysicObject*>&);

  virtual ~General_Frame();
  virtual void execute_all()=0;

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

#endif
