#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>
#include <string>
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(){
    texture = nullptr;
    cameraFollower = false;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    texture = nullptr;
    cameraFollower = false;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) {
        //SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if (texture != nullptr) {
        //SDL_DestroyTexture(texture);
    }
    //texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    texture = Resources::GetImage(file);

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

void Sprite::Render(int x, int y, int w, int h){
    int renderX = x;
    int renderY = y;

    if (!cameraFollower) {
        renderX -= static_cast<int>(Camera::pos.x);
        renderY -= static_cast<int>(Camera::pos.y);
    }

    SDL_Rect renderRect = {renderX, renderY, w, h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &renderRect);
}

int Sprite::GetWidth(){
    return width / frameCountW;
}

int Sprite::GetHeight(){
    return height / frameCountH;
}

bool Sprite::IsOpen(){
    if (texture != nullptr) {
        return true;
    } else {
        return false;
    }
}

// Versão 2.0
void Sprite::SetFrame (int frame){

    int total = frameCountW * frameCountH;  // de frames

    if ((frame >= 0) && (frame < total)){
        int line = frame/frameCountW;   // descobre quantas linhas tem a imagem
        int column = frame%frameCountW;     // descobre quantas colunas tem a imagem
        int x = column * GetWidth();                     // ponto inicial do frame
        int y = line * GetHeight();

        SetClip(x, y, GetWidth(), GetHeight());
    } else {
        std::cout << "Frame fora dos limites" << std::endl;
    }
}
void Sprite::SetFrameCount (int frameCountW, int frameCountH){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetCameraFollower(bool follower) {
    cameraFollower = follower;
}
