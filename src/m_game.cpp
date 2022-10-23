export module game;

export
{

    import <iostream>;
    import <random>;
    import <memory>;
    import <string>;
    import <utility>;

import controller;
import renderer;
import ball;
import paddle;
import block;
import main;

    class Game
    {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        void Run(Controller &controller,
                 Renderer &renderer,
                 std::size_t target_frame_duration);
        int GetScore() const;
        int GetCount() const;

    private:
        Ball ball;
        Paddle paddle;
        std::vector<std::vector<Block>> blocks;

        int score{0};
        int livesRemaining{2};
        bool gameOver{false};
        int deadBlocks{0};
        int blockCounter{64};
        void MakeBlocks();
        void Update();
        void HandleBlockCorners(Block *block,
                                Ball &ball,
                                int &score,
                                int &deadBlocks);
        bool IsBallDirectionOneOf(Ball &ball,
                                  Ball::Direction a,
                                  Ball::Direction b);
        void SetWindowTitle(Renderer &renderer,
                            Uint32 &frame_start,
                            Uint32 &frame_end,
                            int &frame_count,
                            std::size_t &target_frame_duration,
                            Uint32 &title_timestamp);
        void HandleBallHittingBlock(Block *block);
        void HandleBallHittingBlockHelper();
    };

    Game::Game(std::size_t grid_width, std::size_t grid_height) {}

    void Game::SetWindowTitle(Renderer & renderer, Uint32 & frame_start, Uint32 & frame_end, int &frame_count, std::size_t &target_frame_duration, Uint32 &title_timestamp)
    {
        std::string msg;

        // Gameplay window title
        if (!ball.GetWaitingStatus() && frame_end - title_timestamp >= 500)
        {
            msg = "Score: " + std::to_string(score) + "  |  Lives Remaining: " + std::to_string(livesRemaining) + "  |  FPS: " + std::to_string(frame_count);
        }
        // Beginning of game window title
        else if (ball.GetWaitingStatus() && livesRemaining == 2)
        {
            msg = "Please press the space bar to start a new game";
        }
        // In between rounds window title
        else if (ball.GetWaitingStatus() &&
                 livesRemaining >= 0 &&
                 frame_end - title_timestamp >= 500)
        {
            msg = "Please press the space bar to begin the next round";
        }
        // End of game window title
        else if (gameOver && frame_end - title_timestamp >= 500)
        {
            msg = "Game over! Your final score is: " + std::to_string(score) +
                  "  --  Please press the space bar to begin a new game.";
        }
        else
        {
            return;
        }

        renderer.UpdateWindowTitle(msg);
        frame_count = 0;
        title_timestamp = frame_end;
    }

    void Game::Run(Controller & controller,
                   Renderer & renderer,
                   std::size_t target_frame_duration)
    {
        Uint32 frame_start;
        Uint32 frame_end;
        Uint32 frame_duration;
        bool running = true;
        Uint32 title_timestamp = SDL_GetTicks();
        int frame_count = 0;

        MakeBlocks();

        while (running)
        {
            if (gameOver)
            {
                return;
            }
            else if (deadBlocks == blockCounter)
            {
                ball.SetSpeed(ball.GetSpeed() + 1);
                ball.SetX(((kScreenWidth / 2) - (ball.GetSideLength() / 2)) + ball.GetSpeed());
                ball.SetY(kScreenHeight - kBorderWidth - ball.GetSideLength() - Paddle::GetHeight());
                ball.SetDirection(Ball::Direction::kNE);
                controller.paddleSpeed += 5;
                ball.SetWaitingStatus(true);
                blocks.clear();
                MakeBlocks();
            }

            frame_start = SDL_GetTicks();

            // Input, Update, Render - the main game loop.
            controller.HandleInput(running, paddle, ball);
            Update();
            renderer.Render(ball, paddle, blocks);

            frame_end = SDL_GetTicks();

            frame_count++;
            frame_duration = frame_end - frame_start;

            if (frame_end - title_timestamp >= 1000)
            {
                SetWindowTitle(renderer,
                               frame_start,
                               frame_end,
                               frame_count,
                               target_frame_duration,
                               title_timestamp);
            }

            // If the time for this frame is too small, delay the loop to
            // achieve the correct frame rate.
            if (frame_duration < target_frame_duration)
            {
                SDL_Delay(target_frame_duration - frame_duration);
            }
        }
    }

    void Game::HandleBlockCorners(Block * block,
                                  Ball & ball,
                                  int &score,
                                  int &deadBlocks)
    {
        // Handle bottom left corner
        if (ball.GetDirection() == Ball::Direction::kNE &&
            ball.GetX() + ball.GetSideLength() == block->GetX() &&
            ball.GetY() == block->GetY() + kBlockHeight)
        {
            ball.ChangeVerticalDirection();
        }
        // Handle bottom right corner
        else if (ball.GetDirection() == Ball::Direction::kNW &&
                 ball.GetX() == block->GetX() + kBlockWidth &&
                 ball.GetY() == block->GetY() + kBlockHeight)
        {
            ball.ChangeVerticalDirection();
        }
        // Handle top left corner
        else if (ball.GetDirection() == Ball::Direction::kSE &&
                 ball.GetX() + ball.GetSideLength() == block->GetX() &&
                 ball.GetY() + ball.GetSideLength() == block->GetY())
        {
            ball.ChangeVerticalDirection();
        }
        // Handle top right corner
        else if (ball.GetDirection() == Ball::Direction::kSW &&
                 ball.GetX() + ball.GetSideLength() == block->GetX() + kBlockWidth &&
                 ball.GetY() + ball.GetSideLength() == block->GetY())
        {
            ball.ChangeVerticalDirection();
        }
        else
        {
            return;
        }

        block->SetActiveStatus(false);
        score++;
        deadBlocks += 1;
    };

    // In cases where the ball comes into contact with multiple blocks, this
    // ensures that the block closest to the ball's trajectory is broken first
    void Game::HandleBallHittingBlockHelper()
    {
        if (ball.GetDirection() == Ball::Direction::kNE ||
            ball.GetDirection() == Ball::Direction::kNW)
        {
            for (int i = kRowsPerGame - 1; i >= 0; i--)
            {
                for (int j = 0; j < kBlocksPerRow; j++)
                {
                    // raw ptr so block isn't deleted when ptr goes out of scope
                    Block *block = &blocks[i][j];
                    HandleBallHittingBlock(block);
                }
            }
        }
        else if (ball.GetDirection() == Ball::Direction::kSE ||
                 ball.GetDirection() == Ball::Direction::kSW)
        {
            for (int i = 0; i < kRowsPerGame; i++)
            {
                for (int j = 0; j < kBlocksPerRow; j++)
                {
                    // raw ptr so block isn't deleted when ptr goes out of scope
                    Block *block = &blocks[i][j];
                    HandleBallHittingBlock(block);
                }
            }
        }
    }

    void Game::HandleBallHittingBlock(Block * block)
    {
        // If ball hits corner of block
        HandleBlockCorners(block, ball, score, deadBlocks);

        // If ball hits top (+ gap) or bottom of block
        if (block->IsBlockActive() &&
            (ball.GetY() + ball.GetSideLength() ==
                 block->GetY() - kGridBlockSize ||
             ball.GetY() == block->GetY() + kBlockHeight) &&
            ball.GetX() + ball.GetSideLength() >= block->GetX() &&
            ball.GetX() <= block->GetX() + kBlockWidth + kGridBlockSize)
        {
            ball.ChangeVerticalDirection();
            block->SetActiveStatus(false);
            score++;
            deadBlocks += 1;
        }
        // If ball hits right (+ gap) or left side of block
        else if (block->IsBlockActive() &&
                 (ball.GetX() + ball.GetSideLength() == block->GetX() ||
                  ball.GetX() == block->GetX() + kBlockWidth + kGridBlockSize) &&
                 ball.GetY() + ball.GetSideLength() > block->GetY() - kGridBlockSize &&
                 ball.GetY() < block->GetY() + kBlockHeight)
        {
            ball.ChangeHorizontalDirection();
            block->SetActiveStatus(false);
            score++;
            deadBlocks += 1;
        }
    }

    bool Game::IsBallDirectionOneOf(Ball & ball, Ball::Direction a, Ball::Direction b)
    {
        return ball.GetDirection() == a || ball.GetDirection() == b;
    }

    void Game::Update()
    {
        if (livesRemaining < 0)
            return;
        bool condition;
        std::size_t limitation;

        // move ball along current trajectory
        if (!ball.GetWaitingStatus())
        {
            ball.Update();
        }

        // Check if ball hit left side of screen
        if (IsBallDirectionOneOf(ball,
                                 Ball::Direction::kNW,
                                 Ball::Direction::kSW) &&
            ball.GetX() <= kBorderWidth)
        {
            ball.SetX(kBorderWidth);
            ball.ChangeHorizontalDirection();
        }
        // Check if ball hit right side of screen
        else if (IsBallDirectionOneOf(ball, Ball::Direction::kNE, Ball::Direction::kSE) &&
                 ball.GetX() + ball.GetSideLength() >= kScreenWidth - kBorderWidth)
        {
            ball.SetX(kScreenWidth - kBorderWidth);
            ball.ChangeHorizontalDirection();
        }
        // Check if ball hit top of screen
        else if (IsBallDirectionOneOf(ball,
                                      Ball::Direction::kNW,
                                      Ball::Direction::kNE) &&
                 ball.GetY() <= kBorderWidth)
        {
            ball.SetY(kBorderWidth);
            ball.ChangeVerticalDirection();
        }
        // Check if ball hit bottom of screen
        else if (IsBallDirectionOneOf(ball,
                                      Ball::Direction::kSW,
                                      Ball::Direction::kSE) &&
                 ball.GetY() >= kScreenHeight + 200)
        {
            if (livesRemaining > 0)
            {
                livesRemaining -= 1;
                ball.Reset();
            }
            else
            {
                gameOver = true;
                ball.SetY(kScreenHeight + 1);
            }
        }
        // Check if ball hit paddle
        else if (IsBallDirectionOneOf(ball,
                                      Ball::Direction::kSW,
                                      Ball::Direction::kSE) &&
                 ball.GetY() + ball.GetSideLength() == paddle.GetY() &&
                 ball.GetX() < paddle.GetX() + paddle.GetWidth() &&
                 ball.GetX() + ball.GetSideLength() > paddle.GetX())
        {
            ball.ChangeVerticalDirection();
        }
        // Check if ball hit block
        else
        {
            HandleBallHittingBlockHelper();
        }
    }

    void Game::MakeBlocks()
    {
        deadBlocks = 0;
        blockCounter = 0;
        int y = kBorderWidth * 10; // to give room above blocks
        int x = kBorderWidth;

        for (int i = 0; i < kRowsPerGame; i++)
        {
            std::vector<Block> row;

            for (int j = 0; j < kBlocksPerRow; j++)
            {
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
}