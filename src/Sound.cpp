#include "Sound.h"
#include <iostream>
#include "Resources.h"

Sound::Sound(){
    chunk = nullptr;
}

Sound::Sound(std::string file)  {
    Open(file);
}

Sound::~Sound(){
    if (chunk == nullptr) {
        std::cout << "Nenhuma som encontrado" << std::endl;
    } else if (Mix_HaltChannel(channel) == -1){
        std::cout << "Som não pôde ser parado" << std::endl;
    } else {
        //Mix_FreeChunk(chunk);
    }
}

void Sound::Play (int times){
    if (chunk == nullptr) {
        std::cout << "Nenhuma som encontrado" << std::endl;
    } else {
        channel = Mix_PlayChannel(-1, chunk, times-1);
        if (channel == -1) {
            std::cout << "Som não pôde ser tocado" << std::endl;
        }
    }
}

void Sound::Stop (){
    if (chunk == nullptr) {
        std::cout << "Nenhuma som encontrado" << std::endl;
    } else if (Mix_HaltChannel(channel) == -1){
        std::cout << "Som não pôde ser parado" << std::endl;
    }
}

void Sound::Open (std::string file){
    //chunk = Mix_LoadWAV(file.c_str());
    chunk = Resources::GetSound(file);

    if (chunk == nullptr) {
        std::cout << "Erro ao carregar som: " << chunk << " - " << SDL_GetError() << std::endl;
    }
}
bool Sound::IsOpen (){
    if (chunk != nullptr) {
        return true;
    } else {
        return false;
    }
}
