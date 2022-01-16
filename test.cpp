#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <iostream>

#include <cinttypes>

#include "sdltools.h"
#include "Physic/testbox.h"

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
void frame(void*);

SDL_Color black = {0, 0, 0};

Timer framer(60, frame, NULL);


Testbox test(100, 100, 100, 100, 800, black);

int main(int argc, char** argv){
  init();
  test.has_bounds = true;
  test.set_boundaries(0, 800);
  test.can_slide = false;
  test.can_bounce = false;
  test.has_max_speed = true;
  test.max_speed = 10;
  //test.can_wall_bounce = true;
  test.can_slide = true;
  test.add_hitbox(0, 0, 100, 100);
  quit = false;

  while (!quit){
  framer.tick();
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
  test.draw(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  SDL_RenderPresent(renderer);

}

void frame(void* n){

    for(Hitbox& box: test.hitboxes){

      std::cout << box.x << " " << box.y << std::endl;
      std::cout.flush();

    }
    SDL_PollEvent(&e);
    uint8_t* state = const_cast<uint8_t*>(SDL_GetKeyboardState(NULL));

    if (state[SDL_SCANCODE_LEFT]){

      test.move_left(5);

    }
    if (state[SDL_SCANCODE_RIGHT]){

      test.move_right(5);

    }
    if(state[SDL_SCANCODE_SPACE]){

      test.jump(-20);

    }



    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;
		   }
       test.on_frame();
        draw();
    }
