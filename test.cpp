#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstddef>
#include <iostream>
#include <ctime>


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

int jump_count = 0;

SDL_Color black = {0, 0, 0};
SDL_Color blue = {0, 0, 0xFF};

Timer framer(60, frame, NULL);


Testbox test(10, 0, 10, 10, 800, black);

Testbox Block(300, 100, 100, 100, 800, blue);
Testbox Block2(700, 350, 100, 200, 800, blue);
Testbox Block3(200, 200, 30, 50, 800, blue);
Testbox Block4(100, 500, 300, 100, 800, blue);
Testbox Block5(400, 500, 200, 200, 800, blue);

Testbox boxes[1000];
int b_counter = 0;

void add_block(int x, int y, int w, int h){

  Testbox* box = new Testbox(x, y, w, h, 800, blue);

    box->add_hitbox(0, 0, w, h);
    box->can_fall = false;

  boxes[b_counter++] = (*box);
  standard_engine.register_object((PhysicObject*)box);
  standard_engine.load_object((PhysicObject*)box);


}

int main(int argc, char** argv){
  init();

  srand(time(NULL));


  main_camera.x = 0;
  main_camera.y = 0;
  main_camera.w = 800;
  main_camera.h = 800;
  test.has_bounds = false;
  test.can_slide = true;
  test.can_bounce = false;
  test.can_wall_bounce = false;
  test.slow_down = .0F;
  test.has_max_speed = true;
  test.max_speed = 40;
  //test.can_wall_bounce = true;
  test.can_slide = false;
  test.gravity = .2F;
  //test.add_hitbox(0, 0, 100, 100);
  test.add_hitbox(0, 0, 10, 10);
  test.y = -1000;

  Block.can_fall = false;
  Block.add_hitbox(0, 0, 100, 100);
  Block2.can_fall = false;
  Block2.add_hitbox(0, 0, 200, 200);
  Block4.add_hitbox(0, 0, 300, 100);
  Block4.can_fall = false;
  Block3.add_hitbox(0, 0, 30, 50);
  Block3.can_fall = false;
  quit = false;

  standard_engine.register_object((PhysicObject*)&test);
  standard_engine.register_object((PhysicObject*)&Block);
  standard_engine.register_object((PhysicObject*)&Block2);
  standard_engine.register_object((PhysicObject*)&Block4);
  standard_engine.register_object((PhysicObject*)&Block3);

  standard_engine.load_object((PhysicObject*)&test);
  standard_engine.load_object((PhysicObject*)&Block);
  standard_engine.load_object((PhysicObject*)&Block2);
  standard_engine.load_object((PhysicObject*)&Block4);
  standard_engine.load_object((PhysicObject*)&Block3);

  for(int i = 0; i < 1000; i++){

    add_block(rand()%800, -(rand()%100000), rand()%100+50, rand()%100+20);

  }


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

for(int z = 0; z < b_counter; z++){

  delete &boxes[z];

}
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void draw(){

  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);

  standard_engine.draw_loaded_objects(static_cast<void*>(renderer));

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
  SDL_RenderPresent(renderer);

}

void frame(void* n){

    SDL_PollEvent(&e);
    uint8_t* state = const_cast<uint8_t*>(SDL_GetKeyboardState(NULL));

    if (state[SDL_SCANCODE_LEFT]){

      test.move_left(10);

    }
    if (state[SDL_SCANCODE_RIGHT]){

      test.move_right(10);

    }
    if(state[SDL_SCANCODE_SPACE] && jump_count < 2){

      test.jump(15);
      jump_count++;

    }

    if (state[SDL_SCANCODE_A]){




    }


    standard_engine.interact();
    standard_engine.load_unload();

    main_camera.x = test.x-400;
    main_camera.y = test.y-400;



    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;
		   }
       standard_engine.on_frame_loaded_objects();
       if (!test.is_jumping){

         jump_count = 0;

       }
        draw();
    }
