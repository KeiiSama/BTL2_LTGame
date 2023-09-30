#include "template.h"

using namespace std;

renderTemplate::renderTemplate(SDL_Surface* templateSurface, int x, int y, int width, int height)
{
    this->templateSurface = SDL_LoadBMP("bar.bmp");
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void renderTemplate::moveLeft() {
    this->x -= moveSpeed;
}

void renderTemplate::moveRight() {
    this->x += moveSpeed;
}

void renderTemplate::renderT() {
    /*templateSurface = SDL_LoadBMP("bar.bmp");
    SDL_Rect templateRect = {this->x, this->y, this->width, this->height};
    renderScore();
    SDL_BlitSurface(bkground, &templateRect, screenSurface, &templateRect);
    SDL_FreeSurface(screenSurface);

    templateRect.x = this->x;
    templateRect.y = this->y;
    templateRect.w = this->width;
    templateRect.h = this->height;

    renderScore();
    SDL_BlitSurface(this->templateSurface, NULL, screenSurface, &templateRect);
    SDL_UpdateWindowSurface(window);*/

    SDL_Surface* snapshot = SDL_ConvertSurface(screenSurface, screenSurface->format, SDL_SWSURFACE);

    // Vẽ template lên hình chụp
    SDL_Rect templateRect = {this->x, this->y, this->width, this->height};
    SDL_BlitSurface(this->templateSurface, NULL, snapshot, &templateRect);

    // Hiện thị hình chụp trên cửa sổ
    SDL_BlitSurface(snapshot, NULL, screenSurface, NULL);
    SDL_FreeSurface(snapshot);

    // Cập nhật màn hình
    SDL_UpdateWindowSurface(window);
}