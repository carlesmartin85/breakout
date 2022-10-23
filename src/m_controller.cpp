export module controller;

import <iostream>;

export import ball;
export import paddle;
export import main;

#include "SDL.h"

export
{

    class Controller
    {
    public:
        void HandleInput(bool &running,
                         Paddle &paddle,
                         Ball &ball) const;
        int paddleSpeed{20};
    };

    void Controller::HandleInput(bool &running,
                                 Paddle &paddle,
                                 Ball &ball) const
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (paddle.GetX() - paddleSpeed >= (int)kBorderWidth)
                    {
                        paddle.SetX(paddle.GetX() - paddleSpeed);
                        break;
                    }
                    else
                    {
                        paddle.SetX((int)kBorderWidth);
                        break;
                    }
                case SDLK_RIGHT:
                    if (paddle.GetX() + paddle.GetWidth() - 1 + paddleSpeed <=
                        (int)kScreenWidth - (int)kBorderWidth)
                    {
                        paddle.SetX(paddle.GetX() + paddleSpeed);
                        break;
                    }
                    else
                    {
                        paddle.SetX((int)kScreenWidth -
                                    (int)kBorderWidth -
                                    paddle.GetWidth() - 1);
                        break;
                    }
                case SDLK_SPACE:
                    if (ball.GetWaitingStatus())
                    {
                        ball.SetWaitingStatus(false);
                        break;
                    }
                }
            }
        }
    }
}