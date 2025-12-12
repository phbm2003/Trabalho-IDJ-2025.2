#include "SDL2/SDL_ttf.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"
#include <cstdlib>
#include <ctime>

Game* Game::instance = nullptr;

Game::~Game(){
    if (storedState != nullptr) {
        delete storedState;
        storedState = nullptr;
    }

    while (!stateStack.empty()) {
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run(){
    if (storedState != nullptr){
        stateStack.push(std::unique_ptr<State>(storedState));
        storedState = nullptr;
        //std::cout << "1" << std::endl;
    } else {
        //std::cout << "2" << std::endl;
        return;
    }

    GetCurrentState().Start();

    while ((GetCurrentState().QuitRequested() != true) && (stateStack.size() != 0)) {
        //std::cout << "7" << std::endl;
        if (GetCurrentState().PopRequested()) {
            //std::cout << "3" << std::endl;
            //std::cout << "Tamanho" << stateStack.size() << std::endl;
            stateStack.pop();
            //std::cout << "4" << std::endl;
            if (!stateStack.empty()) {
                stateStack.top()->Resume();
                //std::cout << "5" << std::endl;
            }
            //std::cout << "6" << std::endl;
            continue;
        }
        //std::cout << "8" << std::endl;
        if (storedState) {
            //std::cout << "5" << std::endl;
            GetCurrentState().Pause();
            stateStack.push(std::unique_ptr<State>(storedState));
            storedState = nullptr;
            GetCurrentState().Start();
        }
        //std::cout << "9" << std::endl;
        CalculateDeltaTime();
        //std::cout << "91" << std::endl;
        InputManager::GetInstance().Update();
        //std::cout << "92" << std::endl;
        GetCurrentState().Update(dt);
        //std::cout << "93" << std::endl;
        SDL_RenderClear(renderer);
        //std::cout << "94" << std::endl;
        GetCurrentState().Render();
        //std::cout << "95" << std::endl;
        SDL_RenderPresent(renderer);
        //std::cout << "96" << std::endl;
        SDL_Delay(16);
        //std::cout << "10" << std::endl;
    }
    //std::cout << "11" << std::endl;
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetCurrentState(){
    return *stateStack.top();
}

Game& Game::GetInstance() {
    if (instance != nullptr) {
        return *instance;
    } else {
        instance = new Game ("Paulo Henrique Borges Martins/ 211068790", 1200, 900);
        return *instance;
    }
}

Game::Game(std::string title, int width, int height){
    if (instance != nullptr) {
        std::cout << "Erro instância já criada" << std::endl;
        exit(1);
    } else {
        instance = this;
    }

    srand(time(NULL));

    frameStart = SDL_GetTicks();
    dt = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "Erro init sdl" << std::endl;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        std::cout << "Erro img init" << std::endl;
    }

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD) == 0) {
        std::cout << "Erro mix init" << std::endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS , 1024) != 0) {
        std::cout << "Erro open audio" << std::endl;
    }

    if (TTF_Init() != 0) {
        std::cout << "Erro ttf init" << std::endl;
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (window == nullptr) {
        std::cout << "Erro create window" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Erro create window" << std::endl;
    }

    storedState = nullptr;

}
float Game::GetDeltaTime (){
    return dt;
}

void Game::CalculateDeltaTime (){
    Uint32 x = SDL_GetTicks();
    dt = (x - frameStart)/1000.0f;
    frameStart = x;
    if (dt > 0.05f) dt = 0.05f;
}

void Game::Push (State* state) {
    storedState = state;
}
