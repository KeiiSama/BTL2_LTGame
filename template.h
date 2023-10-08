#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "main.h"
#include "mainSDL.h"

class Paddle
{
private:
    static const int moveSpeed = 30;
    void validatePosition();

public:
    Paddle(int x, int y, int width, int height);
    SDL_Surface *image;
    SDL_Rect rect;
    void disable();
    void enable();
    void moveLeft();
    void moveRight();
};

class Brick
{
public:
    Brick(int x = 0, int y = 0);
    SDL_Surface *image;
    SDL_Rect rect;
    bool isBreak = false;
};

class Ball
{
public:
    int speed = 6;
    float velY, velX;
    int size;
    Ball(int x = 100, int y = 100);
    SDL_Surface *image;
    SDL_Rect rect;
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