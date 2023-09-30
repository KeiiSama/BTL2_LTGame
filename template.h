#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "main.h"
#include "mainSDL.h"
#include "score.h"

class renderTemplate {
private:
    SDL_Surface* templateSurface;
    int x, y, width, height;
    static const int moveSpeed = 20;
public:
    renderTemplate(SDL_Surface* templateSurface, int x, int y, int width, int height);
    void moveLeft();
    void moveRight();
    void renderT();
};

#endif