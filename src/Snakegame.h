#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

#include "Definitions.h"

class Snakegame
{
public:
    Snakegame(SDL_Renderer* renderer);

private:
    void Pixel(int x, int y, int c, SDL_Renderer* renderer);
    void Init(SDL_Renderer* renderer);
    void Clear(SDL_Renderer* renderer);
    void UpdateFood(std::vector<int>& pos);
    int  Update();
    void Draw(SDL_Renderer* renderer);
    void Gameloop(SDL_Renderer* renderer);

    std::vector<std::vector<int>> pArr;
    std::vector<int>    fPos;
    char                dir;
    int                 score;
    
    SDL_Color white = {255,255,255};
    TTF_Font* ArcadeFont;
    std::string  ScoreMsg;
    SDL_Surface* ScoreSurface;
    SDL_Texture* ScoreTexture;
    SDL_Rect ScoreRect;
};

#endif 