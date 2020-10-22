#include "ball.h"

void Ball::Update() {
  switch (direction) {
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

void Ball::ChangeVerticalDirection() {
  switch (direction) {
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

void Ball::ChangeHorizontalDirection() {
  switch (direction) {
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


void Ball::Reset() {
    x = kScreenWidth / 2;
    y = kScreenHeight - kBorderWidth - sideLength - Paddle::height;
    waiting = true;
    direction = Direction::kNE;
}