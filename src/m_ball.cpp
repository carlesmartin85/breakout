export module ball;

export
{

  import <iostream>;
  import <vector>;

import main;
import paddle;

  class Ball
  {
  public:
    Ball() {}

    enum class Direction
    {
      kNW,
      kNE,
      kSW,
      kSE
    };

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
    void SetDirection(Direction d);

  private:
    int speed{5}; // ball speed should be divisable by five on current grid
    const int sideLength{10};
    bool waiting{true};
    std::size_t x{((kScreenWidth / 2) - (sideLength / 2))};
    std::size_t y{kScreenHeight - kBorderWidth - sideLength - Paddle::GetHeight()};
    Direction direction{Direction::kNE};
  };

  void Ball::Update()
  {
    switch (direction)
    {
    case Direction::kNW:
      x -= speed;
      y -= speed;
      break;

    case Direction::kNE:
      x += speed;
      y -= speed;
      break;

    case Direction::kSW:
      x -= speed;
      y += speed;
      break;

    case Direction::kSE:
      x += speed;
      y += speed;
      break;
    }
  }

  void Ball::ChangeVerticalDirection()
  {
    switch (direction)
    {
    case Direction::kNW:
      direction = Direction::kSW;
      break;

    case Direction::kNE:
      direction = Direction::kSE;
      break;

    case Direction::kSW:
      direction = Direction::kNW;
      break;

    case Direction::kSE:
      direction = Direction::kNE;
      break;
    }
  }

  void Ball::ChangeHorizontalDirection()
  {
    switch (direction)
    {
    case Direction::kNW:
      direction = Direction::kNE;
      break;

    case Direction::kNE:
      direction = Direction::kNW;
      break;

    case Direction::kSW:
      direction = Direction::kSE;
      break;

    case Direction::kSE:
      direction = Direction::kSW;
      break;
    }
  }

  void Ball::Reset()
  {
    x = kScreenWidth / 2;
    y = kScreenHeight - kBorderWidth - sideLength - Paddle::GetHeight();
    waiting = true;
    direction = Direction::kNE;
  }

  int Ball::GetSpeed() { return speed; }

  void Ball::SetSpeed(int s) { speed = s; }

  int Ball::GetSideLength() { return sideLength; }

  bool Ball::GetWaitingStatus() { return waiting; }

  void Ball::SetWaitingStatus(bool b) { waiting = b; }

  int Ball::GetX() { return x; }

  void Ball::SetX(int newX) { x = newX; }

  int Ball::GetY() { return y; }

  void Ball::SetY(int newY) { y = newY; }

  Ball::Direction Ball::GetDirection() { return direction; }

  void Ball::SetDirection(Direction d) { direction = d; }
}