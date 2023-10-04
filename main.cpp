#include "mainSDL.h"
#include "main.h"
#include "startButton.h"
#include "menu.h"
#include "template.h"
#include "cmath"
#include "gameOver.h"

using namespace std;

// Timer
int frameCount, timerFPS, lastFrame, fps, lastTime = 0;

// Game State
GameState gameState;
PaddleSelect player1 = BOTTOM;
PaddleSelect player2 = TOP;

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
SDL_Rect scoreRect = {50, 30, 0, 0};
SDL_Rect levelRect = {WIDTH / 2 - 50, 30, 0, 0};
int life = 3;
int score = 0;
int countScore = 0;
int level = 1;

// Set timer
SDL_Rect timerRect = {WIDTH - 400, 30, 0, 0};
int time = 30;
int currentTime = 0;
int preTime = 0;

// Game Over
SDL_Rect gameOverRect = {WIDTH / 4 - 100, HEIGHT / 3 - 100, 0, 0};

SDL_Rect showScoreRect = {WIDTH / 4, gameOverRect.y + 200, 0, 0};

SDL_Rect button1Rect = {WIDTH / 3, showScoreRect.y + 150, 0, 0};
bool isButton1Hovered = false;
bool isButton1Clicked = false;

SDL_Rect button2Rect = {WIDTH / 3 + 150, button1Rect.y + 100, 0, 0};
bool isButton2Hovered = false;
bool isButton2Clicked = false;
bool isOver = false;

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

void renderPlayingGame()
{
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, GREEN));
    string scoreText = "Score: " + to_string(score);
    SDL_Surface *coloredButton = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 50), scoreText.c_str(), {WHITE});

    string timeText = "Time Left: " + to_string(time) + "s";
    SDL_Surface *coloredButton1 = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 50), timeText.c_str(), {WHITE});

    string levelText = "Level " + to_string(level);
    SDL_Surface *coloredButton2 = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 50), levelText.c_str(), {WHITE});

    // Vẽ thanh template
    if (gameState == PLAYING1)
    {
        if (player1 == TOP)
        {
            paddleTop.enable();
            paddleBottom.disable();
            SDL_BlitSurface(paddleBottom.image, NULL, screenSurface, &paddleBottom.rect);
            SDL_BlitSurface(paddleTop.image, NULL, screenSurface, &paddleTop.rect);
        }
        if (player1 == BOTTOM)
        {
            paddleBottom.enable();
            paddleTop.disable();
            SDL_BlitSurface(paddleBottom.image, NULL, screenSurface, &paddleBottom.rect);
            SDL_BlitSurface(paddleTop.image, NULL, screenSurface, &paddleTop.rect);
        }
    }

    if (gameState == PLAYING2)
    {
        SDL_BlitSurface(paddleBottom.image, NULL, screenSurface, &paddleBottom.rect);
        SDL_BlitSurface(paddleTop.image, NULL, screenSurface, &paddleTop.rect);
    }

    if (life > 0)
    {
        SDL_FillRect(screenSurface, &lineTop, SDL_MapRGB(screenSurface->format, RED));
        SDL_FillRect(screenSurface, &lineBottom, SDL_MapRGB(screenSurface->format, RED));
    }
    else
    {
        SDL_FillRect(screenSurface, &lineTop, SDL_MapRGB(screenSurface->format, WHITE));
        SDL_FillRect(screenSurface, &lineBottom, SDL_MapRGB(screenSurface->format, WHITE));
    }
    for (int i = 0; i < COL * ROW; i++)
    {
        if (!bricks[i].isBreak)
        {
            SDL_BlitSurface(bricks[i].image, NULL, screenSurface, &bricks[i].rect);
        }
    }

    SDL_BlitSurface(ball.image, NULL, screenSurface, &ball.rect);
    SDL_BlitSurface(coloredButton, NULL, screenSurface, &scoreRect);
    SDL_BlitSurface(coloredButton1, NULL, screenSurface, &timerRect);
    SDL_BlitSurface(coloredButton2, NULL, screenSurface, &levelRect);

    SDL_UpdateWindowSurface(window);
}

void processGameOver()
{
    ball.setVel(0, 0);
    ball.velY = -ball.velY;
    isOver = true;
}

bool isBreakingAllBricks()
{
    for (int i = 0; i < COL * ROW; i++)
    {
        if (!bricks[i].isBreak)
            return false;
    }
    return true;
}

void overComeLevel()
{
    level++;
    for (int i = 0; i < ROW * COL; i++)
    {
        bricks[i].isBreak = false;
    }
}

void update()
{
    if (ball.isStopping())
    {
        ball.rect.x = paddleBottom.rect.x + paddleBottom.rect.w / 2;
        ball.rect.y = paddleBottom.rect.y - 10 - ball.size;
    }
    else
    {
        if (SDL_HasIntersection(&ball.rect, &paddleBottom.rect))
        {
            double rel = (paddleBottom.rect.x + (paddleBottom.rect.w / 2)) - (ball.rect.x + (ball.size / 2));
            double norm = rel / (paddleBottom.rect.w / 2);
            double bounce = norm * (5 * PI / 12);
            ball.setVel(-ball.speed * sin(bounce), -ball.speed * cos(bounce));
        }
        if (SDL_HasIntersection(&ball.rect, &paddleTop.rect))
        {
            double rel = (paddleTop.rect.x + (paddleTop.rect.w / 2)) - (ball.rect.x + (ball.size / 2));
            double norm = rel / (paddleTop.rect.w / 2);
            double bounce = norm * (5 * PI / 12);
            ball.setVel(-ball.speed * sin(bounce), ball.speed * cos(bounce));
        }
        if (SDL_HasIntersection(&ball.rect, &lineBottom) || SDL_HasIntersection(&ball.rect, &lineTop))
            if (life > 0)
            {
                life--;
                ball.velY = -ball.velY;
            }
            else
            {
                processGameOver();
                return;
            }
        ball.move();

        for (int i = 0; i < COL * ROW; i++)
        {
            if (!bricks[i].isBreak)
            {
                if (SDL_HasIntersection(&ball.rect, &bricks[i].rect))
                {
                    bricks[i].isBreak = true;
                    score++;
                    countScore++;
                    if (countScore == 20)
                    {
                        countScore = 0;
                        life++;
                    }
                    if (ball.rect.x <= bricks[i].rect.x)
                    {
                        // canh trai
                        if (ball.velX == 0)
                            ball.velY = -ball.velY;
                        else
                            ball.velX = -ball.velX;
                    }
                    else
                    {
                        if (ball.rect.y <= bricks[i].rect.y)
                        {
                            // canh tren
                            if (ball.velY == 0)
                                ball.velX = -ball.velX;
                            else
                                ball.velY = -ball.velY;
                        }
                        else
                        {
                            if (bricks[i].rect.x + bricks[i].rect.w - ball.rect.x < 2)
                            {
                                // canh phai
                                if (ball.velX == 0)
                                    ball.velY = -ball.velY;
                                else
                                    ball.velX = -ball.velX;
                            }
                            else
                            {
                                // canh duoi
                                if (ball.velY == 0)
                                    ball.velX = -ball.velX;
                                else
                                    ball.velY = -ball.velY;
                            }
                        }
                    }
                }
            }
        }
    }
}

void initialBrick()
{
    int relX = WIDTH / 2 - (SPACING + bricks[0].rect.w) * COL / 2;
    int relY = (HEIGHT - 80) / 2 - (SPACING + bricks[0].rect.h) * ROW / 2;
    for (int i = 0; i < COL * ROW; i++)
    {
        bricks[i].rect.x = relX + (((i % COL) + 1) * SPACING) + ((i % COL) * bricks[i].rect.w) - (SPACING / 2);
        bricks[i].rect.y = relY + bricks[i].rect.h * 3 + (((i % ROW) + 1) * SPACING) + ((i % ROW) * bricks[i].rect.h) - (SPACING / 2);
    }
}

void processPlaying1(int key)
{
    switch (key)
    {
    case SDLK_DOWN:
    case SDLK_s:
        if (player1 == TOP)
            player1 = BOTTOM;
        break;
    case SDLK_UP:
    case SDLK_w:
        if (player1 == BOTTOM)
            player1 = TOP;
        break;
    case SDLK_SPACE:
        ball.setVel(0, ball.speed / 2);
        break;
    case SDLK_a:
    case SDLK_LEFT:
        if (player1 == TOP)
            paddleTop.moveLeft();
        if (player1 == BOTTOM)
            paddleBottom.moveLeft();
        break;
    case SDLK_d:
    case SDLK_RIGHT:
        if (player1 == TOP)
            paddleTop.moveRight();
        if (player1 == BOTTOM)
            paddleBottom.moveRight();
        break;
    }
}

void processPlaying2(int key)
{
    switch (key)
    {
    case SDLK_SPACE:
        ball.setVel(0, ball.speed / 2);
        break;
    case SDLK_a:
        paddleTop.moveLeft();
        break;
    case SDLK_LEFT:
        paddleBottom.moveLeft();
        break;
    case SDLK_d:
        paddleTop.moveRight();
        break;
    case SDLK_RIGHT:
        paddleBottom.moveRight();
        break;
    }
}

/*void renderGameOverScreen() {
    SDL_FillRect(screenSurface, NULL, 0);

    SDL_Surface* coloredButton1 = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 100), "GAME OVER", {WHITE});
    SDL_Surface* coloredButton2 = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 75),
                                                            ("YOUR SCORE: " + to_string(score)).c_str(), {WHITE});

    SDL_BlitSurface(coloredButton1, NULL, screenSurface, &gameOverRect);
    SDL_BlitSurface(coloredButton2, NULL, screenSurface, &showScoreRect);

    SDL_UpdateWindowSurface(window);
}*/

void resetGame()
{
    isOver = false;
    time = 30;
    score = 0;
    level = 1;
    life = 3;
    countScore = 0;
    for (int i = 0; i < COL * ROW; i++)
    {
        bricks[i].isBreak = false;
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
            bool timerStarted = false;

            while (!quit)
            {
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
                    else if (gameState == PLAYING1 || gameState == PLAYING2)
                    {
                        SDL_Event e;
                        bool quit = false;
                        resetGame();
                        initialBrick();

                        while (!quit)
                        {
                            if (isOver)
                            {
                                gameState = GAMEOVER;
                                quit = true;
                                break;
                            }
                            while (SDL_PollEvent(&e))
                            {
                                if (e.type == SDL_QUIT)
                                {
                                    quit = true;
                                }
                                else if (e.type == SDL_KEYDOWN)
                                {
                                    if (gameState == PLAYING1)
                                        processPlaying1(e.key.keysym.sym);
                                    else
                                        processPlaying2(e.key.keysym.sym);

                                    if (e.key.keysym.sym == SDLK_SPACE && time == 30 && !timerStarted)
                                    {
                                        currentTime = SDL_GetTicks();
                                        preTime = currentTime;
                                        timerStarted = true; // Đã bắt đầu tính thời gian
                                    }
                                }
                            }
                            if (timerStarted)
                            {
                                currentTime = SDL_GetTicks();
                                int elapsedTime = currentTime - preTime;

                                if (time > 0 && elapsedTime >= 1000)
                                {
                                    time--;
                                    preTime = currentTime;
                                }
                            }

                            if (time == 0 && !isBreakingAllBricks())
                            {
                                isOver = true;
                            }
                            else if (isBreakingAllBricks())
                            {
                                overComeLevel();
                            }
                            delay();
                            update();
                            renderPlayingGame();
                        }
                    }
                    else if (gameState == GAMEOVER)
                    {
                        // renderGameOverScreen();
                        SDL_FillRect(screenSurface, NULL, 0);

                        SDL_Event e;
                        bool quit = false;

                        while (!quit)
                        {
                            while (SDL_PollEvent(&e))
                            {
                                if (e.type == SDL_QUIT)
                                {
                                    quit = true;
                                }
                                else if (e.type == SDL_MOUSEMOTION)
                                {
                                    int mouseX, mouseY;
                                    SDL_GetMouseState(&mouseX, &mouseY);

                                    renderGameOver();
                                    renderShowScore();

                                    isButton1Hover(mouseX, mouseY);
                                    renderButton1();

                                    isButton2Hover(mouseX, mouseY);
                                    renderButton2();
                                }
                                else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                                {
                                    int mouseX, mouseY;
                                    SDL_GetMouseState(&mouseX, &mouseY);
                                    if (isButton1Hovered)
                                    {
                                        isButton1Click(mouseX, mouseY);
                                        if (isButton1Clicked)
                                        {
                                            SDL_FillRect(screenSurface, NULL, 0);
                                            gameState = MENU;
                                            quit = true;
                                        }
                                    }
                                    else if (isButton2Hovered)
                                    {
                                        isButton2Click(mouseX, mouseY);
                                        if (isButton2Clicked)
                                        {
                                            gameState = EXIT;
                                            quit = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (gameState == EXIT)
                    {
                        quit = true;
                    }
                }
                delay();
            }
        }
    }

    close();
    return 0;
}
