#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <string>
#include "SDL.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"
#include "main.h"
#include <memory>

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height,
                const std::size_t grid_width, const std::size_t grid_height);
        ~Renderer();
        void Render(const Ball &ball, const Paddle &paddle, const std::vector<std::vector<Block>> &blocks);
        void GameplayWindowTitle(int score, int fps, int lives);
        void WaitingWindowTitle(std::string msg);
        void RenderBlocks(SDL_Rect &block, const std::vector<std::vector<Block>> &blocks);

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        const std::size_t screen_width;
        const std::size_t screen_height;
        const std::size_t grid_width;
        const std::size_t grid_height;
};

#endif