#include "gamePlaying1.h"

using namespace std;

void render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);

    // Vẽ thanh template
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleTop);
    SDL_RenderFillRect(renderer, &paddleBottom);

    // Cập nhật renderer
    SDL_RenderPresent(renderer);
}