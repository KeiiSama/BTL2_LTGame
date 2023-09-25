#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //Thêm thư viện SDL_image
#include <windows.h>

using namespace std;

// Create the window
int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bkground = NULL;

// Khởi tạo screen
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

    return success;
}

// Nhập ảnh
bool loadMedia() 
{
    //Loading success flag
    bool success = true;

    //Load splash image
    bkground = SDL_LoadBMP( "bkground.bmp" );
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

// Đóng cửa sổ screen
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
}

// Tạo Menu Game


int main( int argc, char *argv[] )
{
    if(!init())
    {
        cout << "Error: SDL initialization failed" << endl;
    }else
    {
        if(!loadMedia())
        {
            cout << "Error: SDL media failed" << endl;
        }else
        {
            SDL_Event e; 
            bool quit = false; 
            while( quit == false )
            { while( SDL_PollEvent( &e ) )
                { 
                    if( e.type == SDL_QUIT ) 
                        quit = true; 
                } 
            }
        }
    }

    close();
    return 0;
}
