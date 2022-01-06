/*
*
*
* Camera object
*
*/

#ifndef __SDL_TOOLS_CAMERA__
#define __SDL_TOOLS_CAMERA__

#define STANDARD_CAMERA_X 0
#define STANDARD_CAMERA_Y 0
#define STANDARD_CAMERA_WIDTH 1920
#define STANDARD_CAMERA_HEIGHT 1080

class Camera{

public:

  int x = STANDARD_CAMERA_X;
  int y = STANDARD_CAMERA_Y;
  int w = STANDARD_CAMERA_WIDTH;
  int h = STANDARD_CAMERA_HEIGHT; //x and y position, and how wide and high the camera can look
  bool is_scaled = false;


  Camera();
  Camera(int, int);
  Camera(int, int, int, int);

  virtual ~Camera();

  virtual void set_pos(int, int);
  virtual void set_scale(int, int);
  virtual void can_scale(bool);
};

Camera::Camera(){

}

Camera::Camera(int x, int y){

  this->x = x;
  this->y = y;

}

Camera::Camera(int x, int y, int w, int h){

  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;

}

Camera::~Camera(){

}

void Camera::set_pos(int x, int y){

  this->x = x;
  this->y = y;

}

void Camera::set_scale(int w, int h){

  this->w = w;
  this->h = h;

}

void Camera::can_scale(bool can){

  is_scaled = can;

}

Camera main_camera;



#endif
