export module renderer;

export
{

import <vector>;
import <iostream>;
import <string>;
import <memory>;

import ball;
import paddle;
import block;
import main;

#include "SDL.h"

    class Renderer
    {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height,
                 const std::size_t grid_width, const std::size_t grid_height);
        ~Renderer();
        void Render(Ball &ball, Paddle &paddle, const std::vector<std::vector<Block>> &blocks);
        void UpdateWindowTitle(std::string msg);
        void RenderBlocks(SDL_Rect &block, const std::vector<std::vector<Block>> &blocks);

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        const std::size_t screen_width;
        const std::size_t screen_height;
        const std::size_t grid_width;
        const std::size_t grid_height;
    };

    Renderer::Renderer(const std::size_t screen_width,
                       const std::size_t screen_height,
                       const std::size_t grid_width, const std::size_t grid_height)
        : screen_width(screen_width),
          screen_height(screen_height),
          grid_width(grid_width),
          grid_height(grid_height)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL could not initialize.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        }

        // Create Window
        sdl_window = SDL_CreateWindow("BREAKOUT",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      screen_width,
                                      screen_height,
                                      SDL_WINDOW_SHOWN);

        if (nullptr == sdl_window)
        {
            std::cerr << "Window could not be created.\n";
            std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        }

        // Create renderer
        sdl_renderer = SDL_CreateRenderer(sdl_window,
                                          -1,
                                          SDL_RENDERER_ACCELERATED);
        if (nullptr == sdl_renderer)
        {
            std::cerr << "Renderer could not be created.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        }
    }

    Renderer::~Renderer()
    {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

    void Renderer::RenderBlocks(SDL_Rect & block, const std::vector<std::vector<Block>> &blocks)
    {
        for (int i = 0; i < kRowsPerGame; i++)
        {
            switch (i)
            {
            case (0):
            case (1):
                SDL_SetRenderDrawColor(sdl_renderer, 0xEE, 0x20, 0x4D, 0xFF);
                break;
            case (2):
            case (3):
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x75, 0x38, 0xFF);
                break;
            case (4):
            case (5):
                SDL_SetRenderDrawColor(sdl_renderer, 0x1C, 0xAC, 0x78, 0xFF);
                break;
            case (6):
            case (7):
                SDL_SetRenderDrawColor(sdl_renderer, 0xFC, 0xE8, 0x83, 0xFF);
                break;
                // implement additional cases if kRowsPerGame > 8
            }

            for (Block b : blocks[i])
            {
                if (b.IsBlockActive())
                {
                    block.x = b.GetX();
                    block.y = b.GetY();
                    block.w = kBlockWidth;
                    block.h = kBlockHeight;
                    SDL_RenderFillRect(sdl_renderer, &block);
                }
            }
        }
    }

    void Renderer::Render(Ball & ball, Paddle & paddle, const std::vector<std::vector<Block>> &blocks)
    {
        SDL_Rect block;

        // Clear screen
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(sdl_renderer);

        // Render blocks
        RenderBlocks(block, blocks);

        // Render ball
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        block.w = ball.GetSideLength();
        block.h = ball.GetSideLength();
        block.x = ball.GetX();
        block.y = ball.GetY();
        SDL_RenderFillRect(sdl_renderer, &block);

        // Render paddle
        SDL_SetRenderDrawColor(sdl_renderer, 0xBE, 0xBE, 0xBE, 0xFF);
        block.w = paddle.GetWidth();
        block.h = paddle.GetHeight();
        block.x = paddle.GetX();
        block.y = paddle.GetY();
        SDL_RenderFillRect(sdl_renderer, &block);

        SDL_RenderPresent(sdl_renderer);
    }

    void Renderer::UpdateWindowTitle(std::string msg)
    {
        SDL_SetWindowTitle(sdl_window, msg.c_str());
    }
}