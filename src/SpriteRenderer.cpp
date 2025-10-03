#include "SpriteRenderer.h"
#include <iostream>
SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer (GameObject& associated, std::string file, int frameCountW, int frameCountH): Component(associated), sprite(file) {
    sprite.SetFrameCount(frameCountW, frameCountH);  // seta valores do frame
    associated.box.h = sprite.GetHeight();      // altura do frame
    associated.box.w = sprite.GetWidth();       // largura do frame
    sprite.SetFrame(0);                         // primeiro frame é o 0
    std::cout << "SpriteRenderer carregado com sucesso!\n";

}

void SpriteRenderer::Open (std::string file){
    sprite.Open (file);
    associated.box.h = sprite.GetHeight();      // altura do frame
    associated.box.w = sprite.GetWidth();       // largura do frame
}

void SpriteRenderer::SetFrameCount (int frameCountW, int frameCountH){
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update (float dt){}
void SpriteRenderer::Render (){
    sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void SpriteRenderer::SetFrame(int frame){
    sprite.SetFrame(frame);
}
