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
    this->validatePosition();
}

void Paddle::moveRight()
{
    this->x += moveSpeed;
    this->validatePosition();
}

void Paddle::validatePosition()
{
    if (this->x < 0)
        this->x = 0;
    if (this->x + this->w > WIDTH)
        this->x = WIDTH - this->w;
}

Brick::Brick(int x, int y)
{
    this->x = x;
    this->y = y;
    this->w = WIDTH / 30;
    this->h = HEIGHT / 30;
}

Ball::Ball(int x, int y)
{
    this->x = x;
    this->y = y;
    this->radius = 15;
}

HorizontalLine::HorizontalLine(int y)
{
    this->y = y;
    this->x = x;
    this->w = WIDTH;
    this->h = 2;
}