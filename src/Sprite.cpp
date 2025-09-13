#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>
#include <string>

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(std::string file){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        std::cout << "Não foi possível carregar: " << file << " ERRO: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y){
    SDL_Rect renderRect = {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &renderRect);
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    if (texture != nullptr) {
        return true;
    } else {
        return false;
    }
}

