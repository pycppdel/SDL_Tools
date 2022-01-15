#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <iostream>

#include "sdltools.h"

#ifdef __linux__
#include <png.h>
#include <zlib.h>
#endif

#ifdef _WIN32
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#undef main
#endif

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;

bool quit;

void init();
void end();
void draw();
void frame();

void print(void* d){
  std::cout << (char*)d << std::endl;
}

Timer timer(1, print, (void*)"Hallo");

int main(int argc, char** argv){
  init();

  quit = false;

  while (!quit){
  frame();
  }

  end();


  exit(0);
}

void init(){
  SDL_Init( SDL_INIT_VIDEO );
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  window = SDL_CreateWindow("T", 100, 100, 800, 800, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void end(){
//  SDL_JoystickClose(stick);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void draw(){

  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  SDL_RenderPresent(renderer);

}

void frame(){
    timer.tick();
    SDL_PollEvent(&e);


    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;

		   }
draw();
    }
