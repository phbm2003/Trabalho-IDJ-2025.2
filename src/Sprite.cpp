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
    flip = SDL_FLIP_NONE;
    scale = {1, 1};
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    scale = {1, 1};
    texture = nullptr;
    cameraFollower = false;
    flip = SDL_FLIP_NONE;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite(){
    //std::cout << "801" << std::endl;
    if (texture != nullptr) {
        //SDL_DestroyTexture(texture);
    }
    //std::cout << "802" << std::endl;
}

void Sprite::Open(std::string file){
    //if (texture != nullptr) {
        //SDL_DestroyTexture(texture);
    //}
    //texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    std::cout << "Tentando carregar imagem: " << file << std::endl;
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

void Sprite::Render(int x, int y, int w, int h, float angle){
    int renderX = x;
    int renderY = y;

    if (!cameraFollower) {
        renderX -= static_cast<int>(Camera::pos.x);
        renderY -= static_cast<int>(Camera::pos.y);
    }

    SDL_Rect renderRect = {renderX, renderY, static_cast<int>(w * scale.x), static_cast<int>(h * scale.y)};

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &renderRect, angle, nullptr, flip);
}

int Sprite::GetWidth() {
    std::cout << "width: " << width << std::endl;
    std::cout << "frameCountW: " << frameCountW << std::endl;
    std::cout << "scale.x: " << scale.x << std::endl;
    return static_cast<int>((width / frameCountW) * scale.x);
}

int Sprite::GetHeight() {
    std::cout << "height: " << height << std::endl;
    std::cout << "frameCountH: " << frameCountH << std::endl;
    std::cout << "scale.y: " << scale.y << std::endl;
    return static_cast<int>((height / frameCountH) * scale.y);
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
    //std::cout << "Total: " << total << "\n" << std::endl;
    //std::cout << "Total: " << frame << "\n" << std::endl;

    if ((frame >= 0) && (frame < total)){
        int line = frame/frameCountW;   // descobre quantas linhas tem a imagem
        int column = frame%frameCountW;     // descobre quantas colunas tem a imagem
        int frameWidth = width / frameCountW;
        int frameHeight = height / frameCountH;

        int x = column * frameWidth;
        int y = line * frameHeight;

        SetClip(x, y, frameWidth, frameHeight);
    } else {
        std::cout << "Frame fora dos limites" << std::endl;
    }
}
void Sprite::SetFrameCount (int frameCountW, int frameCountH){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;

    //SetClip(0, 0, width / frameCountW, height / frameCountH);
}

void Sprite::SetCameraFollower(bool follower) {
    cameraFollower = follower;
}
void Sprite::SetScale (float scaleX, float scaleY) {
    if (scaleX){
        scale.x = scaleX;
    } else {
        scale.x =  scale.x;
    }

    if (scaleY) {
        scale.y = scaleY;
    } else {
        scale.y = scale.y;
    }
}
Vec2 Sprite::GetScale () {
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    this->flip = flip;
}
