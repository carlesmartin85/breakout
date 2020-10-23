#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <random>
#include <memory>
#include <string>
#include <utility>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"
#include "main.h"

class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        void Run(Controller &controller,
                Renderer &renderer,
                std::size_t target_frame_duration);
        int GetScore() const;
        int GetCount() const;

        void UpdateHeaderText(std::string msg,
                            Renderer &renderer,
                            int &frame_count,
                            Uint32 &title_timestamp,
                            Uint32 &frame_end);
        Ball ball;
        Paddle paddle;
        std::vector<std::vector<Block>> blocks;

    private:
        int score{0};
        int livesRemaining{2};
        bool replay{false};
        bool gameOver{false};
        int deadBlocks{0};
        int blockCounter{64};

        void MakeBlocks();
        void Update();
        void HandleBlockCorners(Block* block,
                                Ball &ball,
                                int &score,
                                int &deadBlocks);
        bool IsBallDirectionOneOf(Ball &ball,
                                  Ball::Direction a,
                                  Ball::Direction b);
        void HandleBallHittingBlock(Block* block);
        void HandleBallHittingBlockHelper();
};

#endif