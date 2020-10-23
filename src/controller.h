#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ball.h"
#include "paddle.h"
#include "SDL.h"
#include "main.h"
#include <iostream>

class Controller {
 public:
  void HandleInput(bool &running, Paddle &paddle, Ball &ball) const;
  int paddleSpeed{20};

};

#endif