#ifndef BALL_H
#define BALL_H

#include "SDL.h"
#include "main.h"
#include "paddle.h"
#include <vector>

class Ball {
    public:
        Ball() {}

        enum class Direction { kNW, kNE, kSW, kSE };

        void Update();
        void ChangeVerticalDirection();
        void ChangeHorizontalDirection();
        void Reset();

        Direction direction{Direction::kNE};

        int speed{5};
        //const int diameter{10};
        //const int radius{diameter / 2};
        const int sideLength{15};
        bool waiting{true};
        std::size_t x{((kScreenWidth / 2) - (sideLength / 2))};
        std::size_t y{kScreenHeight - kBorderWidth - sideLength - Paddle::height};

   private:
};

#endif