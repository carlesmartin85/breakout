#include <iostream>
#include <memory>
#include "game.h"
#include "SDL.h"
#include "main.h"


Game::Game(std::size_t grid_width, std::size_t grid_height) {}

void Game::Run(const Controller &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  std::string msg;
  int frame_count = 0;
  bool running = true;

  MakeBlocks();

  while (running) {

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, paddle, ball);

    Update();

    renderer.Render(ball, paddle, blocks);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.

    if (!ball.waiting && frame_end - title_timestamp >= 1000) {
        renderer.GameplayWindowTitle(score, frame_count, livesRemaining);
        frame_count = 0;
        title_timestamp = frame_end;
    } if (ball.waiting && livesRemaining == 2) {
        msg = "Please press the space bar to start a new game";
        UpdateHeaderText(msg, renderer, frame_count, title_timestamp, frame_end);
    } else if (ball.waiting && livesRemaining >= 0 && frame_end - title_timestamp >= 1000) {
        msg = "Please press the space bar to begin the next round";
        UpdateHeaderText(msg, renderer, frame_count, title_timestamp, frame_end);
    } else if (gameOver && frame_end - title_timestamp >= 500) {
        msg = "Game over! Your final score is: " + std::to_string(score) + "  --  Please press the space bar to begin a new game.";
        UpdateHeaderText(msg, renderer, frame_count, title_timestamp, frame_end);
    } 

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::UpdateHeaderText(std::string msg, Renderer &renderer, int &frame_count, Uint32 &title_timestamp, Uint32 &frame_end) {
    renderer.WaitingWindowTitle(msg);
    frame_count = 0;
    title_timestamp = frame_end;
}

void Game::Update() {
    if (livesRemaining < 0) return;

    // move ball along current trajectory
    if (!ball.waiting) {
        ball.Update();
    }

    // Check if ball hit left side of screen
    if ((ball.direction == Ball::Direction::kNW || ball.direction == Ball::Direction::kSW) && ball.x - ball.speed <= kBorderWidth) {
        ball.x = kBorderWidth;
        ball.ChangeHorizontalDirection();
    } 
    // Check if ball hit right side of screen
    else if ((ball.direction == Ball::Direction::kNE || ball.direction == Ball::Direction::kSE) && ball.x + ball.sideLength + ball.speed >= kScreenWidth - kBorderWidth) {
        ball.x = kScreenWidth - kBorderWidth;
        ball.ChangeHorizontalDirection();
    } 
    // Check if ball hit top of screen
    else if ((ball.direction == Ball::Direction::kNW || ball.direction == Ball::Direction::kNE) && ball.y - ball.speed <= kBorderWidth) {
        ball.y = kBorderWidth;
        ball.ChangeVerticalDirection();
    } 
    // Check if ball hit bottom of screen
    else if ((ball.direction == Ball::Direction::kSW || ball.direction == Ball::Direction::kSE) && ball.y >= kScreenHeight + 200) {
        if (livesRemaining > 0) {
            livesRemaining -= 1;
            ball.Reset();
        } else {
            gameOver = true;
            ball.y = kScreenHeight + 1;
        }
    } 
    // Check if ball hit paddle
    else if ((ball.direction == Ball::Direction::kSW || ball.direction == Ball::Direction::kSE) && (ball.y + ball.sideLength >= paddle.y) && (ball.x >= paddle.x - ball.sideLength) && (ball.x < paddle.x + paddle.width + ball.sideLength)) {
        ball.y = paddle.y - ball.sideLength - 2;
        ball.ChangeVerticalDirection();
    }
    // Check if ball hit block
    else {
        for (int i = 0; i < kRowsPerGame; i ++) {
            for (int j = 0; j < kBlocksPerRow; j++) {
                Block block = blocks[i][j];
                // If ball hits top or bottom of block
                if (block.alive && (ball.y >= block.y - kBorderWidth) && (ball.y < block.y + kBlockHeight) && (ball.x >= block.x) && (ball.x < block.x + kBlockWidth + kBorderWidth)) {
                    ball.y = block.y + kBlockHeight;
                    ball.ChangeVerticalDirection();
                    block.alive = false;
                    blocks[i][j] = block;
                    score++;
                }
            }
        }
    }
}


void Game::MakeBlocks() {
    int y = kBorderWidth * 10; // to give room above blocks
    int x = kBorderWidth;

    for (int i = 0; i < kRowsPerGame; i++) {
        std::vector<Block> row;

        for (int j = 0; j < kBlocksPerRow; j++) {
            std::cout << "x is: " << x << "\n";
            std::cout << "y is: " << y << "\n";

            Block newBlock(x, y);
            row.emplace_back(newBlock);

            x += kBlockWidth + kBorderWidth;

            if (j == (kBlocksPerRow - 1)) { break; }
        }

        blocks.emplace_back(row);

        y += kBlockHeight + kBorderWidth;

        x = kBorderWidth;
        if (i == (kBlocksPerRow - 1)) { break; }

        std::cout << "i = " << i << "\n";

    }
}

int Game::GetScore() const { return score; }
int Game::GetCount() const { return brickCount; }