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
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                cout << "Error: SDL renderer creation failed" << SDL_GetError() << endl;
                success = false;
            }
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
    bool success = true;
    
    screenSurface = SDL_GetWindowSurface(window);
    if( screenSurface == NULL )
    {
        cout << "Error: SDL_LoadBMP failed" << SDL_GetError() << endl;
        success = false;
    }else
    {
        SDL_FillRect(screenSurface, NULL, 0);

        SDL_UpdateWindowSurface(window);
    }

    return success;
}

void close()
{
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
