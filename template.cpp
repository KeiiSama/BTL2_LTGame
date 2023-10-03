#include "template.h"
#include "mainSDL.h"
using namespace std;

Paddle::Paddle(int x, int y, int width, int height)
{
    rect.x = x;
    rect.y = y;
    image = IMG_Load("bar.png");
    rect.w = image->w;
    rect.h = image->h;
}

void Paddle::disable()
{
    image = IMG_Load("bar_disabled.png");
}

void Paddle::enable()
{
    image = IMG_Load("bar.png");
}

void Paddle::moveLeft()
{
    rect.x -= moveSpeed;
    validatePosition();
}

void Paddle::moveRight()
{
    rect.x += moveSpeed;
    validatePosition();
}

void Paddle::validatePosition()
{
    if (rect.x < 0)
        rect.x = 0;
    if (rect.x + rect.w > WIDTH)
        rect.x = WIDTH - rect.w;
}

Brick::Brick(int x, int y)
{
    rect.x = x;
    rect.y = y;
    image = IMG_Load("brick.jpg");
    rect.h = image->h;
    rect.w = image->w;
}

Ball::Ball(int x, int y)
{
    rect.x = x;
    rect.y = y;
    image = IMG_Load("ball.png");
    rect.w = image->w;
    rect.h = image->h;
    velY = 0;
    velX = 0;
    size = rect.w;
}

void Ball::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = x;
}

void Ball::setVel(int velX, int velY)
{
    this->velX = velX;
    this->velY = velY;
}

void Ball::move()
{
    if (rect.x <= 0 || rect.x + size >= WIDTH)
        velX = -velX;
    rect.x += this->velX;
    rect.y += this->velY;
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