#include "gamePlaying1.h"

using namespace std;

void renderT() {
    templateRect.x = 250;
    templateRect.y = 900;
    templateRect.w = 200;
    templateRect.h = 20;


    // Đặt màu vẽ cho renderer thành màu trắng (255, 255, 255, 255)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Vẽ thanh template 
    SDL_RenderFillRect(renderer, &templateRect);

    // Cập nhật renderer
    SDL_RenderPresent(renderer);
}