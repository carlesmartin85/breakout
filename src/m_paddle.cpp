export module paddle;

import <string>;

export import main;

export
{

    class Paddle
    {
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

    int Paddle::GetX() { return x; }

    void Paddle::SetX(int newX) { x = newX; }

    int Paddle::GetY() { return y; }

    void Paddle::SetY(int newY) { y = newY; }

    int Paddle::GetHeight() { return height; }

    int Paddle::GetWidth() { return width; }
}