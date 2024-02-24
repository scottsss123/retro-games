#include <SDL2/SDL.h>
#include <iostream>

#define SDLW 600
#define SDLH 400

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(SDLW, SDLH, 0, &window, &renderer);

    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}