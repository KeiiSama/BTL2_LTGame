#include "mainSDL.h"
#include "main.h"
#include "startButton.h"
#include "menu.h"

using namespace std;

const int FPS = 60;  
const int DELAY_TIME = 1000 / FPS;
Uint32 frameStart;

GameState gameState;

// Create the window
int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bkground = SDL_LoadBMP( "bkground.bmp" );
bool isMouseClicked = false;
bool isMouseClicked1 = false;
bool isMouseClicked2 = false;

// Create Start button
TTF_Font* font = NULL;
SDL_Surface* startButtonSurface = NULL;
SDL_Rect startButtonRect;
bool isMouseOverStartButton = false; 

//Create menu 
SDL_Surface* menuSurface = NULL;
SDL_Rect menuButtonRect;

SDL_Surface* onePersonSurface = NULL;
SDL_Rect onePersonRect;

SDL_Surface* twoPersonSurface = NULL;
SDL_Rect twoPersonRect;

TTF_Font* font1 = NULL;
TTF_Font* font2 = NULL;

bool menuHover = false;
bool onePersonHover = false;
bool twoPersonHover = false;

//Create bars
SDL_Surface* bar1Surface = NULL;
SDL_Surface* bar2Surface = NULL;
SDL_Rect bar1Rect;
SDL_Rect bar2Rect;

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
        }else if(!loadFontStartButton()) {
            cout << "Error: SDL fonts failed" << endl;
        }
        else
        {
            SDL_Event e; 
            bool quit = false; 

            while( !quit )
            { 
                frameStart = SDL_GetTicks();
                while( SDL_PollEvent( &e ) )
                { 
                    if( e.type == SDL_QUIT ) {
                        quit = true; 
                    }
                    else if(gameState == START) {
                        if (e.type == SDL_MOUSEMOTION)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            mouseHoverStartButton(mouseX, mouseY); 
                            renderStartButton();
                        }else if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            startButtonClicked(mouseX, mouseY);
                            if (isMouseClicked) 
                            {    
                                gameState = MENU;
                                if(!loadMenuScreen()){
                                    cout << "ERROR: Couldn't load menu screen" << endl;
                                }else if(!loadMenu()) {
                                    cout << "ERROR: Couldn't load menu" << endl;
                                }
                            }
                        } 
                    }
                    //if (gameState == MENU)  
                    else if(gameState == MENU) {                                              
                        if (e.type == SDL_MOUSEMOTION)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            menuHoverButton(mouseX, mouseY);
                            renderMenuButton(); 
                            
                            hoverOneButton(mouseX, mouseY);
                            renderChose1Button(); 
                            
                            hoverTwoButton(mouseX, mouseY);
                            renderChose2Button();
                        }
                        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            if (onePersonHover) {
                                int mouseX, mouseY;
                                SDL_GetMouseState(&mouseX, &mouseY);
                                oneButtonClicked(mouseX, mouseY);
                                if (isMouseClicked1) 
                                {    
                                    gameState = PLAYING1;
                                }
                            }
                            else if (twoPersonHover) {
                                int mouseX, mouseY;
                                SDL_GetMouseState(&mouseX, &mouseY);
                                twoButtonClicked(mouseX, mouseY);
                                if (isMouseClicked2) 
                                {    
                                    gameState = PLAYING2;
                                }
                            }
                        }
                    }
                }

                Uint32 frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < DELAY_TIME) {
                    SDL_Delay(DELAY_TIME - frameTime);
                }
            }  
        }
    }

    close();
    return 0;
}
