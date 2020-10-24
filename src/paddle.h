#ifndef PADDLE_H
#define PADDLE_H

#include <string>
#include "main.h"

class Paddle {
    public:
        Paddle() {}

        int GetX();
        void SetX(int newX);
        int GetY();
        void SetY(int newY);
        static int GetHeight();
        static int GetWidth();
        
    private:
        static constexpr int height{20};
        static constexpr int width{150};
        int y{kScreenHeight - kBorderWidth - height};
        int x{((kScreenWidth / 2) - (width / 2))};     
};

#endif