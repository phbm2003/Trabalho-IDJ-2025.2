#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage (std::string file){
    for (auto index = imageTable.begin(); index != imageTable.end(); index++) { // percorre mapa
        if (index->first == file) { // pega primeiro elemento do par
            return index->second;
        }
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (!texture) {
        std::cout << "Erro ao carregar imagem: " << file << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }

    imageTable.insert({file, texture}); // adiciona novo par
    return texture;
}

void Resources::ClearImages (){
    for (auto index = imageTable.begin(); index != imageTable.end();) { // percorre mapa
        SDL_DestroyTexture(index->second); // destrói a textura assim como era em sprite
        index = imageTable.erase(index);   // apaga string e ponteiro da tupla, retorno aponto pra próxima tupla
    }
}

Mix_Music* Resources::GetMusic (std::string file){
    for (auto index = musicTable.begin(); index != musicTable.end(); index++) { // percorre mapa
        if (index->first == file) { // pega primeiro elemento do par
            return index->second;
        }
    }
    Mix_Music* music =  Mix_LoadMUS(file.c_str());

    if (!music) {
        std::cout << "Erro ao carregar música: " << file << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }

    musicTable.insert({file, music}); // adiciona novo par
    return music;
}

void Resources::ClearMusics (){
    for (auto index = musicTable.begin(); index != musicTable.end();) { // percorre mapa
        Mix_FreeMusic(index->second); // destrói a música assim como era em Music
        index = musicTable.erase(index);   // apaga string e ponteiro da tupla, retorno aponto pra próxima tupla
    }
}

Mix_Chunk* Resources::GetSound (std::string file){
    for (auto index = soundTable.begin(); index != soundTable.end(); index++) { // percorre mapa
        if (index->first == file) { // pega primeiro elemento do par
            return index->second;
        }
    }
    Mix_Chunk* chunk =  Mix_LoadWAV(file.c_str());

    if (!chunk) {
        std::cout << "Erro ao carregar som: " << file << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }

    soundTable.insert({file, chunk}); // adiciona novo par
    return chunk;
}

void Resources::ClearSounds (){
    for (auto index = soundTable.begin(); index != soundTable.end();) { // percorre mapa
        Mix_FreeChunk(index->second); // destrói o som assim como era em Sound
        index = soundTable.erase(index);   // apaga string e ponteiro da tupla, retorno aponto pra próxima tupla
    }
}
