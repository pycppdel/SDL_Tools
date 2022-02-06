/*
*
*
* Object with a texture. If there's no texture the standard color will be loaded
*
*
*
*/

#ifndef __SDL_TOOLS_TEXTURE_OBJECT__
#define __SDL_TOOLS_TEXTURE_OBJECT__

#ifndef __ALL_PHYSICS_IMPORT__
#include "../Physic/physic.h"
#endif

#define STANDARD_TGROUNDOBJECT_COLOR {0xDC,0xDC,0xDC}

//class for texturalized ground object
class TGroundObject : public GroundObject{

protected:

  SDL_Rect standard_rect;

public:

  SDL_Texture* texture = NULL;

  TGroundObject(int, int, int, int, int);
  TGroundObject(int, int, int, int, int, SDL_Texture*);
  TGroundObject(int, int, int, int, float, int);
  TGroundObject(int, int, int, int, int, bool);

  virtual void draw(void*);



};

TGroundObject::TGroundObject(int x, int y, int w, int h, int ground) : GroundObject(x, y, w, h, ground){


}

TGroundObject::TGroundObject(int x, int y, int w, int h, int ground, SDL_Texture* t) : GroundObject(x, y, w, h, ground){

  //setting texture
  texture = t;

}

TGroundObject::TGroundObject(int x, int y, int w, int h, float slow, int ground) : GroundObject(x, y, w, h, slow, ground){


}

TGroundObject::TGroundObject(int x, int y, int w, int h, int ground, bool can_slow) : GroundObject(x, y, w, h, ground, can_slow){


}

void TGroundObject::draw(void* rend){

}

#endif
