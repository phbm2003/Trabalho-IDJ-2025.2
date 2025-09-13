#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include "State.h"

class Game {
public:
    ~Game();
    void run();
    SDL_Renderer* GetRenderer();

    State& GetState();
    static Game& GetInstance();

private:
    Game(std::string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

#endif // GAME_H
