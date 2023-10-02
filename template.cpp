#include "template.h"

using namespace std;

Paddle::Paddle(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
}

void Paddle::moveLeft()
{
    this->x -= moveSpeed;
}

void Paddle::moveRight()
{
    this->x += moveSpeed;
}

void Paddle::validatePosition()
{
    if (this->x < 0)
        this->x = 0;
    if (this->x + this->w > WIDTH)
        this->x = WIDTH - this->w;
}