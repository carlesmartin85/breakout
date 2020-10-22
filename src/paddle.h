#ifndef PADDLE_H
#define PADDLE_H

#include <string>
#include "main.h"

class Paddle {
    public:
        int getLocation();

        static constexpr std::size_t height{20};
        static constexpr std::size_t width{200};

        Paddle() {}

        int y{kScreenHeight - kBorderWidth - height};
        int x{kScreenWidth / 2};

    private:

        
};

#endif