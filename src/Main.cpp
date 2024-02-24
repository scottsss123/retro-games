#include <SDL2/SDL.h>
#include <iostream>

#include "Snakegame.h"
#include "Definitions.h"

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(SDLW, SDLH, 0, &window, &renderer);

    Snakegame snakegame(renderer);
    
    std::cout << "End of retro-games\n";
    return 0;
}