#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "main.h"
#include "paddle.h"

class Ball {
    public:
        Ball() {}
        
        enum class Direction { kNW, kNE, kSW, kSE };
        
        void Update();
        void ChangeVerticalDirection();
        void ChangeHorizontalDirection();
        void Reset();
        int GetSpeed();
        void SetSpeed(int s);
        int GetSideLength();
        bool GetWaitingStatus();
        void SetWaitingStatus(bool b);
        int GetX();
        void SetX(int x);
        int GetY();
        void SetY(int y);
        Direction GetDirection();
        void SetDirection( Direction d);

    private:
        int speed{5}; // ball speed should be divisable by five on current grid
        const int sideLength{10};
        bool waiting{true};
        std::size_t x{((kScreenWidth / 2) - (sideLength / 2))};
        std::size_t y{kScreenHeight - kBorderWidth - sideLength - Paddle::GetHeight()};
        Direction direction{Direction::kNE};
};

#endif