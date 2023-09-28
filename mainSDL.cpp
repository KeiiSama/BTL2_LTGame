#include "mainSDL.h"

using namespace std;

bool init() 
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "Error: SDL_Init failed" << SDL_GetError() << endl;
        success = false;
    }else 
    {
        window = SDL_CreateWindow("BTL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

        if(window == NULL)
        {
            cout << "Error: SDL_CreateWindow failed" << SDL_GetError() << endl;
            success = false;
        }else
        {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    if(TTF_Init() == -1) {
        cout << "Error: TTF_Init() failed" << SDL_GetError() << endl;
        success = false;
    }

    return success;
}

bool loadMedia() 
{
    //Loading success flag
    bool success = true;

    //Load splash image
    //bkground = SDL_LoadBMP( "bkground.bmp" );
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

void close()
{
    //Deallocate surface
    SDL_FreeSurface( bkground );
    bkground = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();

    if(font) {
        TTF_CloseFont(font);
    }

    if(startButtonSurface) {
        SDL_FreeSurface( startButtonSurface );
    }
}
