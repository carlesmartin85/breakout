#include "game.h"


Game::Game(std::size_t grid_width, std::size_t grid_height) {}

void Game::Run(Controller &controller,
               Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    std::string msg;
    int frame_count = 0;
    bool running = true;

    MakeBlocks();

    while (running) {
        if (gameOver) {
            return;
        } else if (deadBlocks == blockCounter) {
            ball.speed += 1;
            ball.x = ((kScreenWidth / 2) - (ball.sideLength / 2)) + ball.speed;
            ball.y = kScreenHeight - kBorderWidth - ball.sideLength - Paddle::height;
            ball.direction = Ball::Direction::kNE;
            controller.paddleSpeed += 5;
            ball.waiting = true;
            blocks.clear();
            MakeBlocks();
        }

        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, paddle, ball);

        Update();

        renderer.Render(ball, paddle, blocks);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render 
        // cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // Gameplay window title
        if (!ball.waiting && frame_end - title_timestamp >= 1000) {
            renderer.GameplayWindowTitle(score,
                                        frame_count,
                                        livesRemaining);
            frame_count = 0;
            title_timestamp = frame_end;
        } 
        
        // Beginning of game window title
        if (ball.waiting && livesRemaining == 2) {
            msg = "Please press the space bar to start a new game";
            UpdateHeaderText(msg,
                            renderer,
                            frame_count,
                            title_timestamp,   
                            frame_end);
        } 
        // In between rounds window title
        else if (ball.waiting &&
                 livesRemaining >= 0 &&
                 frame_end - title_timestamp >= 1000) {
            msg = "Please press the space bar to begin the next round";
            UpdateHeaderText(msg,
                            renderer,
                            frame_count,
                            title_timestamp,
                            frame_end);
        } 
        // End of game window title
        else if (gameOver && frame_end - title_timestamp >= 500) {
            msg = "Game over! Your final score is: " + std::to_string(score) +
                  "  --  Please press the space bar to begin a new game.";
            UpdateHeaderText(msg,
                            renderer,
                            frame_count,
                            title_timestamp,
                            frame_end);
        } 

        // If the time for this frame is too small, delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
        }
  }
}

void Game::UpdateHeaderText(std::string msg,
                            Renderer &renderer,
                            int &frame_count,
                            Uint32 &title_timestamp,
                            Uint32 &frame_end) {
    renderer.WaitingWindowTitle(msg);
    frame_count = 0;
    title_timestamp = frame_end;
}

void Game::HandleBlockCorners(Block* block,
                              Ball &ball,
                              int &score,
                              int &deadBlocks) {
    // Handle bottom left corner
    if (ball.direction == Ball::Direction::kNE &&
       ball.x + ball.sideLength == block->x &&
       ball.y == block->y + kBlockHeight) {
        ball.ChangeVerticalDirection();
    }
    // Handle bottom right corner
    else if (ball.direction == Ball::Direction::kNW &&
            ball.x == block->x + kBlockWidth &&
            ball.y == block->y + kBlockHeight) {
        ball.ChangeVerticalDirection();
    }
    // Handle top left corner
    else if (ball.direction == Ball::Direction::kSE &&
            ball.x + ball.sideLength == block->x &&
            ball.y + ball.sideLength == block->y) {
        ball.ChangeVerticalDirection();
    }
    // Handle top right corner
    else if (ball.direction == Ball::Direction::kSW &&
            ball.x + ball.sideLength == block->x + kBlockWidth &&
            ball.y + ball.sideLength == block->y) {
        ball.ChangeVerticalDirection();
    } else {
        return;
    }

    block->alive = false;
    score++;
    deadBlocks += 1;
    return;
};

// ensures that the block closest to the ball's trajectory is broken first
void Game::HandleBallHittingBlockHelper() {
    if (ball.direction == Ball::Direction::kNE ||
        ball.direction == Ball::Direction::kNW) {
        for (int i = kRowsPerGame - 1; i >= 0; i--) {
            for (int j = 0; j < kBlocksPerRow; j++) {
                // raw ptr so block isn't deleted when ptr goes out of scope
                Block* block = &blocks[i][j];
                HandleBallHittingBlock(block);
            }
        }
    } else if (ball.direction == Ball::Direction::kSE ||
               ball.direction == Ball::Direction::kSW) {
        for (int i = 0; i < kRowsPerGame; i++) {
            for (int j = 0; j < kBlocksPerRow; j++) {
                // raw ptr so block isn't deleted when ptr goes out of scope
                Block* block = &blocks[i][j];
                HandleBallHittingBlock(block);

            }
        }
    }
}

void Game::HandleBallHittingBlock(Block* block) {
    // If ball hits top or bottom of block
    if (block->alive && 
        (ball.y + ball.sideLength == block->y || 
        ball.y == block->y + kBlockHeight) && 
        ball.x + ball.sideLength > block->x && 
        ball.x <= block->x + kBlockWidth) {                    
        ball.ChangeVerticalDirection();
        block->alive = false;
        score++;
        deadBlocks += 1;
        return;
    }
    // If ball hits right or left side of block
    else if (block->alive &&
            (ball.x + ball.sideLength == block->x ||
            ball.x == block->x + kBlockWidth) &&
            ball.y + ball.sideLength > block->y &&
            ball.y < block->y + kBlockHeight) {
        ball.ChangeHorizontalDirection();
        block->alive = false;
        score++;
        deadBlocks += 1;
        return;
    } 
    // If ball hits corner of block
    else {
        HandleBlockCorners(block, ball, score, deadBlocks);
    }
}

bool Game::IsBallDirectionOneOf(Ball &ball, Ball::Direction a, Ball::Direction b) {
        return ball.direction == a || ball.direction == b;
}

void Game::Update() {
    if (livesRemaining < 0) return;
    bool condition;
    std::size_t limitation;

    // move ball along current trajectory
    if (!ball.waiting) {
        ball.Update();
    }

    // Check if ball hit left side of screen
    if (IsBallDirectionOneOf(ball, Ball::Direction::kNW, Ball::Direction::kSW) &&
        ball.x <= kBorderWidth) {
        ball.x = kBorderWidth;
        ball.ChangeHorizontalDirection();
    }
    // Check if ball hit right side of screen
    else if (IsBallDirectionOneOf(ball, Ball::Direction::kNE, Ball::Direction::kSE) &&
        ball.x + ball.sideLength >= kScreenWidth - kBorderWidth) {
        ball.x = kScreenWidth - kBorderWidth;
        ball.ChangeHorizontalDirection();
    }
    // Check if ball hit top of screen
    else if ((ball.direction == Ball::Direction::kNW ||
        ball.direction == Ball::Direction::kNE) &&
        ball.y <= kBorderWidth) {
        ball.y = kBorderWidth;
        ball.ChangeVerticalDirection();
    } 
    // Check if ball hit bottom of screen
    else if ((ball.direction == Ball::Direction::kSW ||
            ball.direction == Ball::Direction::kSE) &&
            ball.y >= kScreenHeight + 200) {
        if (livesRemaining > 0) {
            livesRemaining -= 1;
            ball.Reset();
        } else {
            gameOver = true;
            ball.y = kScreenHeight + 1;
        }
    } 
    // Check if ball hit paddle
    else if ((ball.direction == Ball::Direction::kSW ||
            ball.direction == Ball::Direction::kSE) && 
            ball.y + ball.sideLength == paddle.y &&
            ball.x < paddle.x + paddle.width &&
            ball.x + ball.sideLength > paddle.x) {
        ball.ChangeVerticalDirection();
    }
    // Check if ball hit block
    else {
        HandleBallHittingBlockHelper();
    }
}

void Game::MakeBlocks() {
    deadBlocks = 0;
    blockCounter = 0;
    int y = kBorderWidth * 10; // to give room above blocks
    int x = kBorderWidth;

    for (int i = 0; i < kRowsPerGame; i++) {
        std::vector<Block> row;

        for (int j = 0; j < kBlocksPerRow; j++) {
            Block newBlock(x, y);
            row.emplace_back(newBlock);

            x += kBlockWidth + kBorderWidth;
            blockCounter += 1;
        }
            

        blocks.emplace_back(row);

        y += kBlockHeight + kBorderWidth;

        x = kBorderWidth;
    }
}

int Game::GetScore() const { return score; }
