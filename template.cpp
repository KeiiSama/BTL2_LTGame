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
    this->w = this->h = this->size;
    this->velY = 0;
    this->velX = 0;
}

void Ball::setPosition(int x, int y)
{
    this->x = x;
    this->x = x;
}

void Ball::setVel(int velX, int velY)
{
    this->velX = velX;
    this->velY = velY;
}

void Ball::move()
{
    if (this->x <= 0 || this->x + this->size >= WIDTH)
        velX = -velX;
    this->x += this->velX;
    this->y += this->velY;
}

bool Ball::isStopping()
{
    if (this->velX == 0 && this->velY == 0)
        return true;
    return false;
}

HorizontalLine::HorizontalLine(int y)
{
    this->y = y;
    this->x = x;
    this->w = WIDTH;
    this->h = 2;
}