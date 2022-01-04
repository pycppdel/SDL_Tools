/*
*
* File that contains an timer.
* usage: initilaize the timer with an fps integer, then add a function which the timer will carry out.
* in the main event loop call tick(), the timer will now automatically carry out the specified function after the fps
*
*/

#ifndef __TIMER__
#define __TIMER__

#ifndef _SDL_H
#include <SDL.h>
#endif

#define STANDARD_FPS 60

class Timer{

private:

  int fps;
  long int last_tick;
  void (*function)();

public:

  Timer();
  Timer(int);
  Timer(int, void (*f)());
  virtual ~Timer();

  void set_task(void (*task)());
  void change_fps(int);
  void tick();

};

Timer::Timer(){

  fps = STANDARD_FPS;
  last_tick = 0;
  function = NULL;

}

Timer::Timer(int fps){

  this->fps = fps;
  last_tick = 0;
  function = NULL;

}

Timer::Timer(int fps, void (*f)()){

  this->fps = fps;
  this->function = f;
  last_tick = 0;

}

Timer::~Timer(){


}

void Timer::set_task(void (*t)()){

  this->function = t;

}

void Timer::change_fps(int fps){

  this->fps = fps;

}

void Timer::tick(){

  long int now = SDL_GetTicks();

  if ((now-last_tick) > (1000/fps)){

    last_tick = now;
    if (function != NULL){
      function();
    }

  }

}


#endif
