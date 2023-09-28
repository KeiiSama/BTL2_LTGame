#include "menu.h"
#include "main.h"
#include "mainSDL.h"

using namespace std;

bool loadMenu() {
    bool success = true;

    font1 = TTF_OpenFont("ERASBD.TTF", 200);
    font2 = TTF_OpenFont("ERASBD.TTF", 100);

    if(!font1 || !font2) {
        cout << "ERROR: Failed to open font" << TTF_GetError() << endl;
        success = false;
    }else {
        SDL_Color textColor = {RED};

        menuSurface = TTF_RenderText_Solid(font1, "Menu", textColor);
        onePersonSurface = TTF_RenderText_Solid(font2, "1 NGUOI CHOI", textColor);
        twoPersonSurface = TTF_RenderText_Solid(font2, "2 NGUOI CHOI", textColor);

        if(!menuSurface || !onePersonSurface || !twoPersonSurface) {
            cout << "ERROR: Failed to render" << TTF_GetError() << endl;
            success = false;
        }           
    }

    //Menu Rect
    menuButtonRect.x = WIDTH / 3;
    menuButtonRect.y = 150;
    menuButtonRect.w = 200;
    menuButtonRect.h = 50;

    //one Person Rect
    onePersonRect.x = WIDTH / 3 - 100;
    onePersonRect.y = menuButtonRect.y + menuButtonRect.h + 200; 
    onePersonRect.w = 200;
    onePersonRect.h = 50;

    //two Person Rect
    twoPersonRect.x = WIDTH / 3 - 100;
    twoPersonRect.y = onePersonRect.y + onePersonRect.h + 100; 
    twoPersonRect.w = 200;
    twoPersonRect.h = 50;

    return success;
}

bool loadMenuScreen() {
    bool success = true;

    //Load splash image
    if( bkground == NULL )
    {
        cout << "Error: SDL_LoadBMP failed" << SDL_GetError() << endl;
        success = false;
    }else
    {
        for (int x = 0; x < WIDTH; x += bkground->w)
        {
            for (int y = 0; y < HEIGHT; y += bkground->h)
            {
                SDL_Rect destRect;
                destRect.w = bkground->w;
                destRect.h = bkground->h;
                destRect.x = x;
                destRect.y = y;

                SDL_BlitSurface(bkground, NULL, screenSurface, &destRect);
            }
        }

        SDL_UpdateWindowSurface(window);
    }

    return success;
}

void menuHoverButton(int x, int y)
{
    if (x >= menuButtonRect.x && x <= (menuButtonRect.x + menuButtonRect.w) &&
        y >= menuButtonRect.y && y <= (menuButtonRect.y + menuButtonRect.h)) {
        menuHover = true; // Mouse is over the button
    } else {
        menuHover = false; // Mouse is not over the button
    }
}

void hoverOneButton(int x, int y)
{
    if (x >= onePersonRect.x && x <= (onePersonRect.x + onePersonRect.w) &&
        y >= onePersonRect.y && y <= (onePersonRect.y + onePersonRect.h)) {
        onePersonHover = true; // Mouse is over the button
    } else {
        onePersonHover = false; // Mouse is not over the button
    }
}

void oneButtonClicked(int x, int y) {
    if (x >= onePersonRect.x && x <= (onePersonRect.x + onePersonRect.w) &&
        y >= onePersonRect.y && y <= (onePersonRect.y + onePersonRect.h)) {
        isMouseClicked1 = true; // Mouse is clicked
    } else {
        isMouseClicked1 = false; // Mouse is not clicked
    }
}

void hoverTwoButton(int x, int y)
{
    if (x >= twoPersonRect.x && x <= (twoPersonRect.x + twoPersonRect.w) &&
        y >= twoPersonRect.y && y <= (twoPersonRect.y + twoPersonRect.h)) {
        twoPersonHover = true; // Mouse is over the button
    } else {
        twoPersonHover = false; // Mouse is not over the button
    }
}

void twoButtonClicked(int x, int y) {
    if (x >= twoPersonRect.x && x <= (twoPersonRect.x + twoPersonRect.w) &&
        y >= twoPersonRect.y && y <= (twoPersonRect.y + twoPersonRect.h)) {
        isMouseClicked2 = true; // Mouse is clicked
    } else {
        isMouseClicked2 = false; // Mouse is not clicked
    }
}

void renderMenuButton() {
    SDL_Color buttonColor;
    if(menuHover) {
        buttonColor = {RED};
    } else {
        buttonColor = {WHITE};
    }

    SDL_Surface* coloredButton1 = TTF_RenderText_Solid(font1, "Menu", buttonColor);
    
    if(coloredButton1) {
        SDL_BlitSurface(coloredButton1, NULL, screenSurface, &menuButtonRect);
        
        SDL_FreeSurface(coloredButton1);
    }

    SDL_UpdateWindowSurface(window);
}

void renderChose1Button() {
    SDL_Color buttonColor;
    if(onePersonHover) {
        buttonColor = {RED};
    }else{
        buttonColor = {WHITE};
    }

    SDL_Surface* coloredButton2 = TTF_RenderText_Solid(font2, "1 NGUOI CHOI", buttonColor);
    
    if(coloredButton2) {
        SDL_BlitSurface(coloredButton2, NULL, screenSurface, &onePersonRect);

        SDL_FreeSurface(coloredButton2);
    }

    SDL_UpdateWindowSurface(window);
}

void renderChose2Button() {
    SDL_Color buttonColor;
    if(twoPersonHover) {
        buttonColor = {RED};
    }else{
        buttonColor = {WHITE};
    }

    SDL_Surface* coloredButton3 = TTF_RenderText_Solid(font2, "2 NGUOI CHOI", buttonColor);
    
    if(coloredButton3) {
        SDL_BlitSurface(coloredButton3, NULL, screenSurface, &twoPersonRect);

        SDL_FreeSurface(coloredButton3);
    }

    SDL_UpdateWindowSurface(window);
}