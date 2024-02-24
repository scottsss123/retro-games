#include "Snakegame.h"

#define W 30    // WIDTH
#define H 20    // HEIGHT
#define S 20    // SCALE

Snakegame::Snakegame(SDL_Renderer* renderer)
{
    Init(renderer);
    Gameloop(renderer);
}

void Snakegame::Pixel(int x, int y, int c, SDL_Renderer* renderer)
{
    int rgb[3];
         if (c == 0) { rgb[0] = 0;   rgb[1] = 0;   rgb[2] = 0; } // Background
    else if (c == 1) { rgb[0] = 0;   rgb[1] = 255; rgb[2] = 0; } // Snake
    else if (c == 2) { rgb[0] = 255; rgb[1] = 0;   rgb[2] = 0; } // Food

    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_Rect pixel;
    pixel.w = S;
    pixel.h = S;
    pixel.x = x * S;
    pixel.y = y * S;
    SDL_RenderFillRect(renderer, &pixel);
}

void Snakegame::Init(SDL_Renderer* renderer)
{
    pArr.push_back({1, H/2});
    pArr.push_back({0, H/2});

    fPos.push_back(W/2);
    fPos.push_back(H/2);

    dir = 'r';

    score = 0;

    Clear(renderer);

    TTF_Init();

    ArcadeFont = TTF_OpenFont("fonts/arcade.TTF", 24);
    ScoreRect.x = 5; ScoreRect.y = 0; ScoreRect.h = SDLH/6;
    return;
}

void Snakegame::Clear(SDL_Renderer* renderer)
{ int x, y;
    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            Pixel(x, y, 0, renderer);
        }
    }
}

void Snakegame::UpdateFood(std::vector<int>& pos)
{ int i;
    srand(time(NULL));

    bool valid = false;
    while (!valid)
    {
        pos[0] = rand() % W;
        pos[1] = rand() % H;

        bool collision = false;
        int  pLen = pArr.size();
        for (i = 0; i < pLen; i++)
        {
            if (pos[0] == pArr[i][0] && pos[1] == pArr[i][1])
                collision = true;
        }

        if (!collision)
            valid = true;
    }
}

int Snakegame::Update()
{ int i;
    // Init next position to head
    std::vector<int> nPos;
    nPos.resize(2);
    nPos[0] = pArr[0][0]; nPos[1] = pArr[0][1];

    switch (dir)    // Modify next position based on direction
    {
        case 'r':
            nPos[0]++;
            break;
        case 'l':
            nPos[0]--;
            break;
        case 'u':
            nPos[1]--;
            break;
        case 'd':
            nPos[1]++;
            break;
    }    

    // Loss check
    //      Bounds
    int x = nPos[0], y = nPos[1];
    if (x < 0 || x > W - 1 || y < 0 || y > H -1)
    {
        std::cout << "Out Of Bounds\n";
        return -1;
    }

    //      Self Collision
    int pLen = pArr.size();
    for (i = 0; i < pLen; i++)
    {
        if (x == pArr[i][0] && y == pArr[i][1])
        {
            std::cout << "Self Collision\n";
            return -1;
        }
    }

    // Food
    bool food = false;
    if (x == fPos[0] && y == fPos[1])
    {
        food = true;
        UpdateFood(fPos);
        score++;
    }

    // Add new head
    pArr.insert(pArr.begin(), nPos);

    if (!food)
        pArr.pop_back();

    return 0;
}

void Snakegame::Draw(SDL_Renderer* renderer)
{ int i;
    Clear(renderer);

    // Draw Score
    if (ScoreMsg == "You Lose!")
    {
        ScoreRect.y = (SDLH/2) - (ScoreRect.h / 2);
        ScoreRect.x = (SDLH/2) - (ScoreRect.w / 2);
    } else
    {
        ScoreMsg = "Score:" + std::to_string(score);
    }
    ScoreRect.w = 0.07*SDLW*ScoreMsg.length();
    ScoreSurface = TTF_RenderText_Solid(ArcadeFont, ScoreMsg.c_str(), white);
    ScoreTexture = SDL_CreateTextureFromSurface(renderer, ScoreSurface);
    SDL_RenderCopy(renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_FreeSurface(ScoreSurface);
    SDL_DestroyTexture(ScoreTexture);

    // Draw Snake
    int pLen = pArr.size();
    for (i = 0; i < pLen; i++)
    {
        Pixel(pArr[i][0], pArr[i][1], 1, renderer);
    }

    // Draw Food
    Pixel(fPos[0], fPos[1], 2, renderer);

}

void Snakegame::Gameloop(SDL_Renderer* renderer)
{
    bool running = true;
    bool dirChange = false;
    SDL_Event e;

    while (running)
    {
        dirChange = false;

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_LEFT:
                            if (dir != 'r' && !dirChange)
                            { dir = 'l'; dirChange = true; }
                            break;
                        case SDL_SCANCODE_A:
                            if (dir != 'r' && !dirChange)
                            { dir = 'l'; dirChange = true; }
                            break;
                        
                        case SDL_SCANCODE_RIGHT:
                            if (dir != 'l' && !dirChange)
                            { dir = 'r'; dirChange = true; }
                            break;
                        case SDL_SCANCODE_D:
                            if (dir != 'l' && !dirChange)
                            { dir = 'r'; dirChange = true; }
                            break;

                        case SDL_SCANCODE_UP:
                            if (dir != 'd' && !dirChange)
                            { dir = 'u'; dirChange = true; }
                            break;
                        case SDL_SCANCODE_W:
                            if (dir != 'd' && !dirChange)
                            { dir = 'u'; dirChange = true; }
                            break;

                        case SDL_SCANCODE_DOWN:
                            if (dir != 'u' && !dirChange)
                            { dir = 'd'; dirChange = true; }
                            break;
                        case SDL_SCANCODE_S:
                            if (dir != 'u' && !dirChange)
                            { dir = 'd'; dirChange = true; }
                            break;
                    }
                    break;
            }
        }

        switch (Update())
        {
            case 0:
                break;
            case 1:
                std::cout << "You win!\n";
                break;
            case -1:
                std::cout << "You Lose!\n";
                ScoreMsg = "You Lose!";
                running = false;
                break;
        }
        Draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
    SDL_Delay(3000);
    std::cout << "End of Snake Game\n";
}