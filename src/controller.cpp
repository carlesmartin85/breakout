#include "controller.h"
#include "main.h"

void Controller::HandleInput(bool &running, Paddle &paddle, Ball &ball) const {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {

            case SDLK_LEFT:
            std::cout << "Paddle x is: " << paddle.x << "\n";
                if (paddle.x - paddleSpeed >= (int) kBorderWidth) {
                    paddle.x -= paddleSpeed;
                    break;
                } else {
                    paddle.x = (int) kBorderWidth;
                    break;
                }

            case SDLK_RIGHT:
                if (paddle.x + paddle.width - 1 + paddleSpeed <=
                   (int) kScreenWidth - kBorderWidth) {
                    paddle.x += paddleSpeed;
                    break;
                } else {
                    paddle.x = (int) kScreenWidth -
                               (int) kBorderWidth -
                               paddle.width - 1;
                    break;
                }

            case SDLK_SPACE:
                if (ball.waiting) {
                    ball.waiting = false;
                    break;
                }
            }
        }
    }
}