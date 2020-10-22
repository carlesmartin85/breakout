#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "main.h"

constexpr std::size_t kPaddleSpeed = 20;

void Controller::HandleInput(bool &running, Paddle &paddle, Ball &ball) const {
  SDL_Event e;
  
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          if (paddle.x - kPaddleSpeed >= kBorderWidth) {
            paddle.x -= kPaddleSpeed;
            break;
          } else {
              paddle.x = kBorderWidth;
              break;
          }

        case SDLK_RIGHT:
          if ((paddle.x + paddle.width - 1 + kPaddleSpeed) <= (kScreenWidth - kBorderWidth)) {
              paddle.x += kPaddleSpeed;
              break;
          } else {
              paddle.x = kScreenWidth - kBorderWidth - paddle.width - 1;
              break;
          }

        case SDLK_SPACE:
            if (ball.waiting) {
                ball.waiting = false;
            }
      }
    }
  }
}