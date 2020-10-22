#ifndef BLOCK_H
#define BLOCK_H

#include "SDL.h"
#include "main.h"

constexpr int kBlockHeight = 20;
constexpr int kBlockWidth = (((kScreenWidth + 1) - (kBorderWidth * (kBlocksPerRow + 1))) / kBlocksPerRow);


class Block {
    public:
        Block(int x, int y) : x(x), y(y) {}
        bool alive{true};
        int x;
        int y;

    private:
    

};

#endif