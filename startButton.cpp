#include "startButton.h"
#include "main.h"
#include "mainSDL.h"

using namespace std;

// Create font
bool loadFontStartButton() {
    bool success = true;

    font = TTF_OpenFont("ERASBD.TTF", 100);
    if(!font) {
        cout << "ERROR: Failed to open font" << TTF_GetError() << endl;
        success = false;
    }else
    {
        SDL_Color textColor = {RED};

        startButtonSurface = TTF_RenderText_Solid(font, "Start", textColor);
        if(!startButtonSurface) {
            cout << "ERROR: Failed to render" << TTF_GetError() << endl;
            success = false;
        }           
    }

    startButtonRect.x = 200;
    startButtonRect.y = 400;
    startButtonRect.w = 50;
    startButtonRect.h = 0;

    return success;
}

//Handle mouse click event
void startButtonClicked(int x, int y) {
    if (x >= startButtonRect.x && x <= (startButtonRect.x + startButtonRect.w) &&
        y >= startButtonRect.y && y <= (startButtonRect.y + startButtonRect.h)) {
        isMouseClicked = true; // Mouse is clicked
    } else {
        isMouseClicked = false; // Mouse is not clicked
    }
}

// Handle mouse hover event
void mouseHoverStartButton(int x, int y)
{
    if (x >= startButtonRect.x && x <= (startButtonRect.x + startButtonRect.w) &&
        y >= startButtonRect.y && y <= (startButtonRect.y + startButtonRect.h)) {
        isMouseOverStartButton = true; // Mouse is over the button
    } else {
        isMouseOverStartButton = false; // Mouse is not over the button
    }
}

// Render the "Start" button with the appropriate color
void renderStartButton() {
    SDL_Color buttonColor;
    if(isMouseOverStartButton) {
        buttonColor = {RED};
    }else{
        buttonColor = {WHITE};
    }

    SDL_Surface* coloredButton = TTF_RenderText_Solid(font, "Start", buttonColor);
    if(coloredButton) {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &startButtonRect);
        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}
