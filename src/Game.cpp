#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include <string>
#include "GAME.h"

Game* Game::instance = nullptr;

Game::~Game(){
    delete state;

    Mix_CloseAudio();

    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::run(){
    state->LoadAssets();
    while (state->QuitRequested() != true) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
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
