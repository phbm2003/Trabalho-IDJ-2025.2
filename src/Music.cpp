#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Music.h"

#include <string>
#include <iostream>

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

Music::~Music (){
    Stop ();
    Mix_FreeMusic(music);
}

void Music::Play (int times){
    if (music == nullptr) {
        std::cout << "Nenhuma música encontrada" << std::endl;
    } else if (Mix_PlayMusic(music, times) == -1){
        std::cout << "Erro ao tocar música" << std::endl;
    }
}

void Music::Stop (int  msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open (std::string file){
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cout << "Erro ao carregar a música: " << SDL_GetError()  << std::endl;
    }
}

bool Music::IsOpen (){
    if (music != nullptr) {
        return true;
    } else {
        return false;
    }
}
