#include "block.h"

int Block::GetY() { return y; }

void Block::SetY(int newY) {y = newY; }

int Block::GetX() { return x; }

void Block::SetX(int newX) { x = newX; }

bool Block::IsBlockActive() { return active; }

void Block::SetActiveStatus(bool newStatus) { active = newStatus; }