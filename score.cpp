#include "score.h"
#include "main.h"
#include "mainSDL.h"

using namespace std;

bool loadScreen()  {
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
    
    scoreRect.x = 10;
    scoreRect.y = 10;
    scoreRect.w = 60;
    scoreRect.h = 30;

    return success;
}

void renderScore() {
    SDL_Color scoreColor = {BLACK};
    fontScore = TTF_OpenFont("ERASBD.TTF", 50);

    SDL_Surface* coloredButton = TTF_RenderText_Solid(fontScore, "Score: ", scoreColor);
    
    if(coloredButton) {
        SDL_BlitSurface(coloredButton, NULL, screenSurface, &scoreRect);
        
        SDL_FreeSurface(coloredButton);
    }

    SDL_UpdateWindowSurface(window);
}