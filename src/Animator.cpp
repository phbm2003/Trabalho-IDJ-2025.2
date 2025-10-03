#include "Animator.h"
#include "SpriteRenderer.h"

Animator::Animator (GameObject& associated) : Component (associated){
    frameStart = 0;
    frameEnd = 0;
    frameTime = 0;
    currentFrame = 0;
    timeElapsed = 0;
}
void Animator::Update (float dt){
    if (frameTime != 0) {
        timeElapsed++;
    }
    if (timeElapsed > frameTime) {
        currentFrame++;
        timeElapsed = timeElapsed - frameTime;
        associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame); // chama método SetFrame do componente SpriteRenderer presente em um GameObject
    }
    if (currentFrame > frameEnd) {
        currentFrame = frameStart;
        associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame);
    }
}
void Animator::Render (){}
void Animator::SetAnimation (std::string name){
    for (auto index = animations.begin(); index != animations.end(); index++) { // percorre mapa
        if (index->first == name) { // pega primeiro elemento do par
            frameStart = (index->second).frameStart; // atribui frameStart do objeto Animation a frameStart de Animator
            frameEnd = (index->second).frameEnd;
            frameTime = (index->second).frameTime;
            currentFrame = frameStart;
            timeElapsed = 0;
            associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame);
            break; // chaves únicas
        }
    }
}
void Animator::AddAnimation (std::string name, Animation anim){
    for (auto index = animations.begin(); index != animations.end(); index++) { // percorre mapa
        if (index->first == name) { // pega primeiro elemento do par
            return;
        }
    }
    animations.insert({name, anim}); // adiciona novo par
}
