#include "mainSDL.h"
#include "main.h"
#include "startButton.h"
#include "menu.h"
#include "template.h"
#include "cmath"

using namespace std;

const int FPS = 24;
const int DELAY_TIME = 1000 / FPS;
int frameCount, timerFPS, lastFrame, fps, lastTime = 0;
Uint32 frameStart;

GameState gameState;

// Game State

// Create the window
int WIDTH = 0.9 * GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = 0.9 * GetSystemMetrics(SM_CYSCREEN);
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Renderer *renderer = NULL;

bool isMouseClicked = false;
bool isMouseClicked1 = false;
bool isMouseClicked2 = false;
bool isMouseClicked3 = false;

// Create Start button
TTF_Font *font = NULL;
SDL_Surface *startButtonSurface = NULL;
SDL_Rect startButtonRect;
bool isMouseOverStartButton = false;

// Create menu
SDL_Surface *menuSurface = NULL;
SDL_Rect menuButtonRect;

SDL_Surface *onePersonSurface = NULL;
SDL_Rect onePersonRect;

SDL_Surface *twoPersonSurface = NULL;
SDL_Rect twoPersonRect;

SDL_Surface *exitSurface = NULL;
SDL_Rect exitButtonRect;

TTF_Font *font1 = NULL;
TTF_Font *font2 = NULL;

bool menuHover = false;
bool onePersonHover = false;
bool twoPersonHover = false;
bool exitHover = false;

// Create template
Paddle paddleTop(WIDTH / 2, 100, WIDTH / 5, 10);
HorizontalLine lineTop(95);
Paddle paddleBottom(WIDTH / 2, HEIGHT - 20, WIDTH / 5, 10);
HorizontalLine lineBottom(HEIGHT - 5);
Brick bricks[ROW * COL];
Ball ball;

void delay()
{
    lastFrame = SDL_GetTicks();
    if (lastFrame >= lastTime + 1000)
    {
        lastTime = lastFrame;
        fps = frameCount;
        frameCount = 0;
    }

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60))
    {
        SDL_Delay((1000 / 60) - timerFPS);
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);

    // Vẽ thanh template
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleTop);
    SDL_RenderFillRect(renderer, &paddleBottom);
    SDL_RenderFillRect(renderer, &lineTop);
    SDL_RenderFillRect(renderer, &lineBottom);

    for (int i = 0; i < COL * ROW; i++)
    {
        if (!bricks[i].isBreak)
        {
            SDL_RenderFillRect(renderer, &bricks[i]);
        }
    }
    SDL_RenderFillRect(renderer, &ball);

    // Cập nhật renderer
    SDL_RenderPresent(renderer);
}

void processGameOver()
{
    ball.setVel(0, 0);
    ball.velY = -ball.velY;
}

void update()
{
    if (ball.isStopping())
    {
        ball.x = paddleBottom.x + paddleBottom.w / 2;
        ball.y = paddleBottom.y - 7 - 10;
    }
    else
    {
        if (SDL_HasIntersection(&ball, &paddleBottom))
        {
            double rel = (paddleBottom.x + (paddleBottom.w / 2)) - (ball.x + (ball.size / 2));
            double norm = rel / (paddleBottom.w / 2);
            double bounce = norm * (5 * PI / 12);
            ball.setVel(-ball.speed * sin(bounce), -ball.speed * cos(bounce));
        }
        if (SDL_HasIntersection(&ball, &paddleTop))
        {
            double rel = (paddleTop.x + (paddleTop.w / 2)) - (ball.x + (ball.size / 2));
            double norm = rel / (paddleTop.w / 2);
            double bounce = norm * (5 * PI / 12);
            ball.setVel(ball.speed * sin(bounce), ball.speed * cos(bounce));
        }
        if (SDL_HasIntersection(&ball, &lineBottom) || SDL_HasIntersection(&ball, &lineTop))
            processGameOver();
        ball.move();

        for (int i = 0; i < COL * ROW; i++)
        {
            if (!bricks[i].isBreak)
            {
                if (SDL_HasIntersection(&ball, &bricks[i]))
                {
                    bricks[i].isBreak = true;
                    if (ball.x >= bricks[i].x)
                    {
                        ball.velX = -ball.velX;
                    }
                    if (ball.x <= bricks[i].x)
                    {
                        ball.velX = -ball.velX;
                    }
                    if (ball.y <= bricks[i].y)
                    {
                        ball.velY = -ball.velY;
                    }
                    if (ball.y >= bricks[i].y)
                    {
                        ball.velY = -ball.velY;
                    }
                }
            }
        }
    }
}

void initialBrick()
{
    ball.x = WIDTH / 2 - (ball.size / 2);
    ball.y = paddleBottom.y - (paddleBottom.h * 4);
    int relX = WIDTH / 2 - (SPACING + bricks[0].w) * COL / 2;
    int relY = (HEIGHT - 80) / 2 - (SPACING + bricks[0].h) * ROW / 2;
    for (int i = 0; i < COL * ROW; i++)
    {
        bricks[i].x = relX + (((i % COL) + 1) * SPACING) + ((i % COL) * bricks[i].w) - (SPACING / 2);
        bricks[i].y = relY + bricks[i].h * 3 + (((i % ROW) + 1) * SPACING) + ((i % ROW) * bricks[i].h) - (SPACING / 2);
    }
}

int main(int argc, char *argv[])
{
    if (!init())
    {
        cout << "Error: SDL initialization failed" << endl;
    }
    else
    {
        if (!loadMedia())
        {
            cout << "Error: SDL media failed" << endl;
        }
        else if (!loadFontStartButton())
        {
            cout << "Error: SDL fonts failed" << endl;
        }
        else
        {
            SDL_Event e;
            bool quit = false;

            while (!quit)
            {
                frameStart = SDL_GetTicks();

                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (gameState == START)
                    {
                        if (e.type == SDL_MOUSEMOTION)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            mouseHoverStartButton(mouseX, mouseY);
                            renderStartButton();
                        }
                        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            startButtonClicked(mouseX, mouseY);
                            if (isMouseClicked)
                            {
                                gameState = MENU;
                                SDL_FillRect(screenSurface, NULL, 0);
                                if (!loadMenu())
                                {
                                    cout << "ERROR: Couldn't load menu" << endl;
                                }
                            }
                        }
                    }
                    // if (gameState == MENU)
                    else if (gameState == MENU)
                    {
                        if (e.type == SDL_MOUSEMOTION)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            // menuHoverButton(mouseX, mouseY);
                            renderMenuButton();

                            hoverOneButton(mouseX, mouseY);
                            renderChose1Button();

                            hoverTwoButton(mouseX, mouseY);
                            renderChose2Button();

                            exitHoverButton(mouseX, mouseY);
                            renderExitButton();
                        }
                        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            if (onePersonHover)
                            {
                                int mouseX, mouseY;
                                SDL_GetMouseState(&mouseX, &mouseY);
                                oneButtonClicked(mouseX, mouseY);
                                if (isMouseClicked1)
                                {
                                    gameState = PLAYING1;
                                }
                            }
                            else if (twoPersonHover)
                            {
                                int mouseX, mouseY;
                                SDL_GetMouseState(&mouseX, &mouseY);
                                twoButtonClicked(mouseX, mouseY);
                                if (isMouseClicked2)
                                {
                                    gameState = PLAYING2;
                                }
                            }
                            else if (exitHover)
                            {
                                int mouseX, mouseY;
                                SDL_GetMouseState(&mouseX, &mouseY);
                                exitButtonClicked(mouseX, mouseY);
                                if (isMouseClicked3)
                                {
                                    gameState = EXIT;
                                }
                            }
                        }
                    }
                    else if (gameState == PLAYING1)
                    {
                        SDL_Event e;
                        bool quit = false;
                        initialBrick();

                        while (!quit)
                        {
                            while (SDL_PollEvent(&e))
                            {
                                if (e.type == SDL_QUIT)
                                {
                                    quit = true;
                                }
                                else if (e.type == SDL_KEYDOWN)
                                {
                                    switch (e.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        ball.setVel(0, ball.speed / 2);
                                        break;
                                    case SDLK_a:
                                    case SDLK_LEFT:
                                        paddleTop.moveLeft();
                                        paddleBottom.moveLeft();
                                        break;
                                    case SDLK_d:
                                    case SDLK_RIGHT:
                                        paddleTop.moveRight();
                                        paddleBottom.moveRight();
                                        break;
                                    }
                                }
                            }
                            delay();
                            update();
                            render();
                        }
                    }
                    // if (gameState == PLAYING2)
                    else if (gameState == PLAYING2)
                    {
                    }
                    // if (gameState == EXIT)
                    else if (gameState == EXIT)
                    {
                        quit = true;
                    }
                }

                Uint32 frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < DELAY_TIME)
                {
                    SDL_Delay(DELAY_TIME - frameTime);
                }
            }
        }
    }

    close();
    return 0;
}
