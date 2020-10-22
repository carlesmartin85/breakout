#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ball.h"
#include "paddle.h"

class Controller {
 public:
  void HandleInput(bool &running, Paddle &paddle, Ball &ball) const;
};

#endif