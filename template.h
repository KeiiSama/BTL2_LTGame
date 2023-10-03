#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "main.h"
#include "mainSDL.h"

class Paddle : public SDL_Rect
{
private:
    static const int moveSpeed = 30;
    void validatePosition();

public:
    Paddle(int x, int y, int width, int height);
    void moveLeft();
    void moveRight();
};

class Brick : public SDL_Rect
{
public:
    Brick(int x = 0, int y = 0);
    bool isBreak = false;
};

class Ball : public SDL_Rect
{
public:
    static const int size = 15;
    static const int speed = 8;
    float velY, velX;
    Ball(int x = 100, int y = 100);
    void move();
    void setPosition(int x, int y);
    void setVel(int velX, int velY);
    bool isStopping();
};

class HorizontalLine : public SDL_Rect
{
public:
    HorizontalLine(int y = 0);
    bool isBounce = false;
};

#endif