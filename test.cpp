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
SDL_Color white = {0xFF, 0xFF, 0xFF};
SDL_Color blue = {0, 0, 0xFF};
SDL_Color red = {0xFF, 0, 0};

Timer framer(60, frame, NULL);


Testbox test(10, 0, 50, 50, 800, black);

Testbox Block(300, 100, 100, 100, 800, blue);
Testbox Block2(400, 100, 100, 100, 800, red);
Testbox Block3(500, 100, 100, 100, 800, blue);
Testbox Block4(600, 100, 100, 100, 800, blue);
Testbox Block5(700, 100, 100, 100, 800, blue);
Testbox faller(0, 0, 10, 10, 800, blue);

Testbox boxes[1000];
int b_counter = 0;

Texture_Loader loader(renderer);

void add_block(int x, int y, int w, int h){

  Testbox* box = new Testbox(x, y, w, h, 800, blue);


    box->add_hitbox(0, 0, w, h);
    box->can_fall = false;

  boxes[b_counter++] = (*box);
  auto_engine.register_object((PhysicObject*)box);


}

class TestFrame : public Frame{

public:

  TestFrame(){

  }
  TestFrame(SDL_Event* e, SDL_Renderer* r, SDL_Color& c) : Frame(e, r, c){

    main_camera.w = 800;
    main_camera.h = 800;

    faller.add_hitbox(0, 0, 10, 10);
    faller.left_moveable = true;
    faller.right_moveable = true;
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
    test.add_hitbox(0, 0, 50, 50);

    Block.can_fall = false;
    Block.add_hitbox(0, 0, 100, 100);
    Block2.can_fall = false;
    Block2.add_hitbox(0, 0, 100, 100);
    Block4.add_hitbox(0, 0, 100, 100);
    Block4.can_fall = false;
    Block3.add_hitbox(0, 0, 100, 100);
    Block3.can_fall = false;
    quit = false;

    auto_engine.set_color(white);
    auto_engine.set_renderer(renderer);

    auto_engine.register_object((PhysicObject*)&test);

    add_block(100, 700, 100, 100);
    add_block(200, 700, 100, 100);
    add_block(300, 700, 100, 100);
    add_block(400, 700, 100, 100);
    add_block(500, 700, 100, 100);
    add_block(800, 500, 300, 100);
    add_block(1000, 400, 200, 100);
    add_block(1200, 200, 100, 100);

    int last_x = 1200;
    int last_y = 200;
    for(int i = 0; i < 100; i++){

      last_x = last_x + rand()%500+200;
      last_y = last_y - 100 - rand()%100;
      int length = rand()%10+5;
      add_block(last_x, last_y, length, 5);

    }


  }

  void execute_all(){

    main_camera.x = test.x-400;
    main_camera.y = test.y-400;

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

  }

};

TestFrame fram;

int main(int argc, char** argv){
  init();


  srand(time(NULL));

  TestFrame t(&e, renderer, white);
  fram = t;

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
  auto_engine.execute_all();
  SDL_RenderPresent(renderer);

}

void frame(void* n){

    SDL_PollEvent(&e);



    fram.execute_all();


    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;
		   }
       if (!test.is_jumping){

         jump_count = 0;

       }
        draw();
    }
