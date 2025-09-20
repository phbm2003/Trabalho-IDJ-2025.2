#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"

State::State() {
    quitRequested = false;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    GameObject* bg = new GameObject();
    SpriteRenderer* spriteR = new SpriteRenderer(*bg, "bin/recursos/img/Background.png", 1, 1); // ponteiro para um novo obj SpriteRenderer
    bg->AddComponent(spriteR);  // adiciona ao GameObject ponteiro pra um SpriteRenderer

    bg->box.x = 0;  // incializar bg
    bg->box.y = 0;

    AddObject(bg);  // garante que bg seja atualizado

    music.Open("bin/recursos/audio/BGM.wav");
    music.Play(-1);

    GameObject* zombiego = new GameObject(); // nova entidade zombie

    Zombie* zombie = new Zombie(*zombiego);  // novo componente de zombie
    zombiego->AddComponent(zombie);          // adiciona componente à entidade

    zombiego->box.x = 600; // seta posição do zombie no background
    zombiego->box.y = 450;

    AddObject(zombiego);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state
}

void State::Update(float dt) {
    // Versão 2.0

    if (objectArray.size() != 0){
        for (int index = 0; index <= objectArray.size() - 1; index++){
            objectArray[index]->Update(dt);  // chama update pra cada GameObject
        }
    }

    for (int index = objectArray.size() - 1; index >= 0; index--){  // percorre vetor de trás pra frente já que índice de cada elemento pode mudar
        if (objectArray[index]->IsDead()) { // chama método IsDead de GameObject
            objectArray.erase(objectArray.begin() + index); // apaga objeto marcado a partir do endereço do primeiro elemento somado com index
        }
    }
    // Versão 1.0
    if (SDL_QuitRequested() == true) {
        quitRequested = true;
    }
}

void State::Render() {
    // Versão 2.0

    if (objectArray.size() != 0){
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Render();  // chama render pra cada GameObject
        }
    }
    //bg->Render(); // fundo deve ser desenhado primeiro
}

// Versão 2.0
State::~State () {
    objectArray.clear();
}

void State::AddObject (GameObject* go) {
    objectArray.emplace_back(std::unique_ptr<GameObject>(go));  // adiciona no fim do vetor objeto que tem ponteiro para objeto do tipo Component

}

