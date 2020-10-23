#ifndef BALL_H
#define BALL_H

#include <iostream>
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
        int GetSpeed();
        int GetSideLength();
        int GetWaitingStatus();
        int GetX();
        int SetX(int x);
        int GetY();
        int SetY(int y);

        Direction direction{Direction::kNE};

        

    private:
        int speed{5}; // ball speed should be divisable by five on current grid
        const int sideLength{15};
        bool waiting{true};
        int x{((kScreenWidth / 2) - (sideLength / 2))};
        int y{kScreenHeight - kBorderWidth - sideLength - Paddle::height};


};

#endif