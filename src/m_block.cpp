export module block;

export import main;

#include "SDL.h"

export
{

    constexpr int kBlockHeight = 20;
    constexpr int kBlockWidth = (((kScreenWidth + 1) - (kBorderWidth * (kBlocksPerRow + 1))) / kBlocksPerRow);

    class Block
    {
    public:
        Block(int x, int y) : x(x), y(y) {}

        int GetY();
        void SetY(int newY);
        int GetX();
        void SetX(int newX);
        bool IsBlockActive();
        void SetActiveStatus(bool newStatus);

    private:
        bool active{true};
        int x;
        int y;
    };

    int Block::GetY() { return y; }

    void Block::SetY(int newY) { y = newY; }

    int Block::GetX() { return x; }

    void Block::SetX(int newX) { x = newX; }

    bool Block::IsBlockActive() { return active; }

    void Block::SetActiveStatus(bool newStatus) { active = newStatus; }
}