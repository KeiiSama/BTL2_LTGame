#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "main.h"
#include "mainSDL.h"

class Paddle: public SDL_Rect {
private:
    static const int moveSpeed = 20;
    void validatePosition();
public:
    Paddle(int x, int y, int width, int height);
    void moveLeft();
    void moveRight();
};

#endif