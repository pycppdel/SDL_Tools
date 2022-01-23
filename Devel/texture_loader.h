
/*
*
*
*
* standard texture loader, so you dont have to load a texture twice
*
*/

#ifndef __SDL_TOOLS_DEVEL_TEXTURE_LOADER__
#define __SDL_TOOLS_DEVEL_TEXTURE_LOADER__

std::map<std::string, SDL_Texture*> loaded_textures;

class Texture_Loader{

//class for loading textures and cleaning them up
public:

  SDL_Renderer* intern_renderer=NULL;
  Texture_Loader();
  Texture_Loader(SDL_Renderer*);
  ~Texture_Loader();

  void load_texture(std::string, std::string);
  void unload_texture(std::string);
  SDL_Texture* get(std::string);

};

Texture_Loader::Texture_Loader(){

}

Texture_Loader::Texture_Loader(SDL_Renderer* r){

  intern_renderer = r;

}

Texture_Loader::~Texture_Loader(){

  //unloads and deletes all textures

  std::map<std::string, SDL_Texture*>::iterator it;

  it = loaded_textures.begin();

  while (it != loaded_textures.end()){

    SDL_DestroyTexture((*it).second);
    loaded_textures.erase(it);
    it++;
  }

}

void Texture_Loader::load_texture(std::string name, std::string path){

  //if(intern_renderer==NULL)return;

  SDL_Surface* s = IMG_Load(path.c_str());
  SDL_Texture* lt = SDL_CreateTextureFromSurface(intern_renderer, s);
  SDL_FreeSurface(s);
  loaded_textures[name] = lt;


}

void Texture_Loader::unload_texture(std::string name){

  std::map<std::string, SDL_Texture*>::iterator it;

  it = loaded_textures.begin();

  while (it != loaded_textures.end()){

    if((*it).first == name){

      SDL_DestroyTexture((*it).second);
      loaded_textures.erase(it);
      break;

    }
    it++;
  }


}

SDL_Texture* Texture_Loader::get(std::string name){

  std::map<std::string, SDL_Texture*>::iterator it;

  it = loaded_textures.begin();

  while (it != loaded_textures.end()){

    if((*it).first == name){

      return (*it).second;

    }
    it++;
  }

  return NULL;

}

#endif
