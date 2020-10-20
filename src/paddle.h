#ifndef PADDLE_H
#define PADDLE_H

class Paddle {
    public:
        enum class Direction{kLeft, kRight, kStill};
        int getLocation();

        static constexpr std::size_t height{10};
        static constexpr std::size_t width{200};
        static constexpr std::size_t xLocation{10};

        void Update();

        bool PaddleCells();

        Direction direction{Direction::kStill};

        Paddle(int width, int height)
      : _screenWidth(width),
        _screenHeight(height),
        _yLocation(_screenWidth / 2) {}

        std::vector<SDL_Point> paddle;

    private:
        void UpdateLocation();
        std::size_t _screenWidth;
        std::size_t _screenHeight;
        int _yLocation;

};

#endif