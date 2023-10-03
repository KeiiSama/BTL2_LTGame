#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //Thêm thư viện SDL_image
#include <windows.h>
#include <SDL2/SDL_ttf.h>
#include "template.h"

#define RED 255, 0, 0
#define BLUE 0, 0, 255
#define GREEN 0, 255, 0
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define COL 13 // odd
#define ROW 8  // even
#define PI 3.14159265358979323846
#define SPACING 16

enum GameState
{
    START,
    MENU,
    PLAYING1,
    PLAYING2,
    GAMEOVER,
    EXIT,
};

enum PaddleSelect
{
    TOP,
    BOTTOM,
};

extern GameState gameState;

extern int WIDTH /* = GetSystemMetrics(SM_CXSCREEN)*/;
extern int HEIGHT /*= GetSystemMetrics(SM_CYSCREEN)*/;
extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern SDL_Renderer *renderer;

extern TTF_Font *font;

// create start button
extern SDL_Surface *startButtonSurface;
extern SDL_Rect startButtonRect;
extern bool isMouseClicked;
extern bool isMouseOverStartButton;

// create menu
extern bool isMouseClicked1;
extern bool isMouseClicked2;
extern bool isMouseClicked3;

extern SDL_Surface *menuSurface;
extern SDL_Rect menuButtonRect;

extern SDL_Surface *onePersonSurface;
extern SDL_Rect onePersonRect;

extern SDL_Surface *twoPersonSurface;
extern SDL_Rect twoPersonRect;

extern SDL_Surface *exitSurface;
extern SDL_Rect exitButtonRect;

extern TTF_Font *font1;
extern TTF_Font *font2;

extern bool menuHover;
extern bool onePersonHover;
extern bool twoPersonHover;
extern bool exitHover;

extern int score;

// Game Over
extern SDL_Rect gameOverRect;

extern SDL_Rect showScoreRect;

extern SDL_Rect button1Rect;
extern bool isButton1Hovered;
extern bool isButton1Clicked;

extern SDL_Rect button2Rect;
extern bool isButton2Hovered;
extern bool isButton2Clicked;

#endif