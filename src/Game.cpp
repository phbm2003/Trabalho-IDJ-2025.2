#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::~Game(){
    delete state;
    state = nullptr;

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run(){
    state->Start();

    while (state->QuitRequested() != true) {
        std::cout << "1\n" << std::endl;
        CalculateDeltaTime();
        std::cout << "2\n" << std::endl;
        InputManager::GetInstance().Update();
        std::cout << "3\n" << std::endl;
        state->Update(dt);
        std::cout << "4\n" << std::endl;
        SDL_RenderClear(renderer);
        std::cout << "5\n" << std::endl;
        state->Render();
        std::cout << "6\n" << std::endl;
        SDL_RenderPresent(renderer);
        std::cout << "7\n" << std::endl;
        SDL_Delay(16);
        std::cout << "8\n" << std::endl;
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

State& Game::GetState(){
    return *state;
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

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (window == nullptr) {
        std::cout << "Erro create window" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Erro create window" << std::endl;
    }

    state = new State();

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
