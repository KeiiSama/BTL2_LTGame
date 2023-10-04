#include "gameOver.h"

using namespace std;

void isButton1Hover(int x, int y)
{
    if (x >= button1Rect.x && x <= (button1Rect.x + button1Rect.w) &&
        y >= button1Rect.y && y <= (button1Rect.y + button1Rect.h))
    {
        isButton1Hovered = true; // Mouse is over the button
    }
    else
    {
        isButton1Hovered = false; // Mouse is not over the button
    }
}

void isButton1Click(int x, int y)
{
    if (x >= button1Rect.x && x <= (button1Rect.x + button1Rect.w) &&
        y >= button1Rect.y && y <= (button1Rect.y + button1Rect.h))
    {
        isButton1Clicked = true; // Mouse is clicked
    }
    else
    {
        isButton1Clicked = false; // Mouse is not clicked
    }
}

void isButton2Hover(int x, int y)
{
    if (x >= button2Rect.x && x <= (button2Rect.x + button2Rect.w) &&
        y >= button2Rect.y && y <= (button2Rect.y + button2Rect.h))
    {
        isButton2Hovered = true; // Mouse is over the button
    }
    else
    {
        isButton2Hovered = false; // Mouse is not over the button
    }
}

void isButton2Click(int x, int y)
{
    if (x >= button2Rect.x && x <= (button2Rect.x + button2Rect.w) &&
        y >= button2Rect.y && y <= (button2Rect.y + button2Rect.h))
    {
        isButton2Clicked = true; // Mouse is clicked
    }
    else
    {
        isButton2Clicked = false; // Mouse is not clicked
    }
}

void renderGameOver()
{
    SDL_Color buttonColor = {GREEN};

    SDL_Surface *coloredButton = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 150), "GAME OVER", buttonColor);

    if (coloredButton)
    {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &gameOverRect);

        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}

void renderShowScore()
{
    SDL_Color buttonColor = {WHITE};

    SDL_Surface *coloredButton = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 100), ("YOUR SCORE: " + to_string(score)).c_str(), buttonColor);

    if (coloredButton)
    {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &showScoreRect);

        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}

void renderButton1()
{
    SDL_Color buttonColor;

    if (isButton1Hovered)
    {
        buttonColor = {RED};
    }
    else
    {
        buttonColor = {WHITE};
    }

    SDL_Surface *coloredButton = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 75), "PLAY AGAIN", buttonColor);

    if (coloredButton)
    {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &button1Rect);

        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}

void renderButton2()
{
    SDL_Color buttonColor;

    if (isButton2Hovered)
    {
        buttonColor = {RED};
    }
    else
    {
        buttonColor = {WHITE};
    }

    SDL_Surface *coloredButton = TTF_RenderText_Solid(TTF_OpenFont("ERASBD.TTF", 75), "EXIT", buttonColor);

    if (coloredButton)
    {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &button2Rect);

        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}
