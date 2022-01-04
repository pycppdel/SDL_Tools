/*
*
* Implemntation of a drawable circle in SDL
*
*
*/

#ifndef __SDL_TOOLS_CIRCLE__
#define __SDL_TOOLS_CIRCLE__

#include <utility>
#include <vector>

#ifndef _SDL_H
#include <SDL.h>
#endif

typedef std::vector<std::pair<int, int> > circle_point_container;

class Circle{

public:

  int x, y, radius;
  int screenwidth, screenheight;
  SDL_Color color;
  circle_point_container points; //order: first -> x, second -> y

  Circle(int, int, int, int, int, SDL_Color&);
  virtual ~Circle();

  void compute_points();
  void clear_points();

  void draw(SDL_Renderer*);




};

Circle::Circle(int x, int y, int r, int sw, int sh, SDL_Color& c){

  this->x = x;
  this->y = y;
  this->radius = r;
  this->color = c;
  this->screenwidth = sw;
  this->screenheight = sh;
  points.clear();

}

Circle::~Circle(){

}

void Circle::clear_points(){

  points.clear();

}

void Circle::draw(SDL_Renderer* rend){

  SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, 0x0);

  for(std::pair<int, int> p : points){

    SDL_RenderDrawPoint(rend, p.first, p.second);

  }

}

void Circle::compute_points(){

  points.clear();

  for(int x_ = -x; x_ < screenwidth-x; x_++){

    for(int y_ = -y; y_ < screenheight-y; y_++){

      int new_x = x_;
      int new_y = y_;

      if (new_x >= -x && new_x <= screenwidth-x && new_y >= -y && new_y <= screenheight-y){

        if (((new_x*new_x)+(new_y*new_y)) <= (radius*radius)){

          std::pair<int, int> p(new_x+x, new_y+y);
          points.push_back(p);

        }

      }

    }

  }


}


#endif
