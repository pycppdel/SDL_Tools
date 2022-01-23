/*
*
*standard file for Projects
* using SDL_Tools
*
*/

//including all necessary SDL_Applications
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//getting the standard definitions and tools
#include <cstddef>
#include "sdltools.h"


//linux dependencies
#ifdef __linux__
#include <png.h>
#include <zlib.h>
#endif

//getting libraries from windows
#ifdef _WIN32
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#undef main
#endif


//standard variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;

//game-loop condition
bool quit;

//used functions to init, end and draw the frame
void init();
void end();
void draw();
void frame(void*);

//timer for controlled management
Timer timer(60, frame, NULL);


int main(int argc, char** argv){

  //initializing
  init();

  quit = false;

  //gameloop
  while (!quit){
    timer.tick();
  }

  //deinitializing
  end();

  exit(0);
}

void init(){
  //init everything
  SDL_Init( SDL_INIT_EVERYTHING );
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  //creating window
  window = SDL_CreateWindow("", 100, 100, 800, 800, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void end(){
//  SDL_JoystickClose(stick);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void draw(){

  //drawing and setting
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  //Paste your draw operation here
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  SDL_RenderPresent(renderer);

}
void frame(void* data){


  //on frame will be executed every fps/s frame

    SDL_PollEvent(&e);


    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;

		   }
       draw();
    }
