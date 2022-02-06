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

#define STANDARD_TGROUNDOBJECT_COLOR {0xA9,0xA9,0xA9}

class TextureObject_For_Physic{

protected:

  SDL_Rect standard_rect;
  SDL_Color standard_color = STANDARD_TGROUNDOBJECT_COLOR;

public:

  SDL_Texture* texture = NULL;
  //for drawing purpose
  float angle = .0F;

  TextureObject_For_Physic();

  virtual void update_position()=0;
  virtual void draw(void*)=0;



};

//class for texturalized ground object
class TGroundObject : public GroundObject, public TextureObject_For_Physic{

protected:

  SDL_Rect standard_rect;
  SDL_Color standard_color = STANDARD_TGROUNDOBJECT_COLOR;

public:

  SDL_Texture* texture = NULL;

  //for drawing purpose
  float angle = .0F;

  TGroundObject(int, int, int, int, int);
  TGroundObject(int, int, int, int, int, SDL_Texture*);
  TGroundObject(int, int, int, int, float, int);
  TGroundObject(int, int, int, int, int, bool);

  virtual void draw(void*);
  virtual void update_position();



};

TextureObject_For_Physic::TextureObject_For_Physic(){

}



TGroundObject::TGroundObject(int x, int y, int w, int h, int ground) : GroundObject(x, y, w, h, ground), TextureObject_For_Physic(){


}

TGroundObject::TGroundObject(int x, int y, int w, int h, int ground, SDL_Texture* t) : GroundObject(x, y, w, h, ground), TextureObject_For_Physic(){

  //setting texture
  texture = t;

}

TGroundObject::TGroundObject(int x, int y, int w, int h, float slow, int ground) : GroundObject(x, y, w, h, slow, ground), TextureObject_For_Physic(){


}

TGroundObject::TGroundObject(int x, int y, int w, int h, int ground, bool can_slow) : GroundObject(x, y, w, h, ground, can_slow), TextureObject_For_Physic(){


}

void TGroundObject::draw(void* data){

  update_position();

  //checking for texture
  if (texture != NULL){

    SDL_RenderCopyEx((SDL_Renderer*)data, texture, NULL, &standard_rect, angle, NULL, SDL_FLIP_NONE);

  }
  else{
    SDL_SetRenderDrawColor((SDL_Renderer*)data, standard_color.r, standard_color.g, standard_color.b, 0x0);
    //drawing standard
    SDL_RenderFillRect((SDL_Renderer*)data, &standard_rect);

  }

}

void TGroundObject::update_position(){
  //setting standard_rect
  standard_rect.x = x;
  standard_rect.y = y;
  standard_rect.w = width;
  standard_rect.h = height;

}


//same for static object

#endif
