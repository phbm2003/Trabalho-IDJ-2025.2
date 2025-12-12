#ifndef GAME_H
#define GAME_H

#include "State.h"
#include <stack>
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include "StageState.h"

class Game {
public:
    Game(std::string title, int width, int height);
    ~Game();
    void run();
    SDL_Renderer* GetRenderer();

    State& GetCurrentState();
    static Game& GetInstance();

    void Push (State* state);

    float GetDeltaTime ();
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;

    int frameStart;
    float dt;
    void CalculateDeltaTime ();
    std::stack<std::unique_ptr<State>> stateStack;
};

#endif // GAME_H
