#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Rect.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include <iostream>
#include "Camera.h"

State::State() {
    quitRequested = false;

    // carregar background primeiro

    GameObject* bg = new GameObject();
    SpriteRenderer* spriteR = new SpriteRenderer(*bg, "bin/recursos/img/Background.png", 1, 1);
    spriteR->SetcameraFollower(true);
    bg->AddComponent(spriteR);
    bg->box.x = 0;
    bg->box.y = 0;
    AddObject(bg);

    // carregar mapa por cima

    GameObject* tm = new GameObject();

    TileSet* TileSetR = new TileSet(64, 64, "bin/recursos/img/Tileset.png"); // ponteiro para um novo obj TileMap
    TileMap* TileMapR = new TileMap(*tm, "bin/recursos/map/map.txt", TileSetR); // ponteiro para um novo obj TileMap
    tm->AddComponent(TileMapR);  // adiciona ao GameObject ponteiro pra um TileMap

    tm->box.x = 0;  // incializar tm
    tm->box.y = 0;

    AddObject(tm);  // garante que tm seja atualizado*/

}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    music.Open("bin/recursos/audio/BGM.wav");
    music.Play(-1);
}

void State::Update(float dt) {
    // Versão 2.0

    Camera::Update(dt);

    // Atualiza todos os objetos
    for (auto& obj : objectArray) {
        if (!obj->IsDead()) {
            obj->Update(dt);
        }
    }

    // Remove objetos mortos (de trás pra frente)
    for (int i = objectArray.size() - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead()) {
            // Se o foco da câmera for esse objeto, desfoca
            if (Camera::GetFocus() == objectArray[i].get()) {
                Camera::Unfollow();
            }
            objectArray.erase(objectArray.begin() + i);
        }
    }

    // Versão 1.0
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY)) { // barra de espaço pressionada
        GameObject* zombiego = new GameObject(); // nova entidade zombie

        Zombie* zombie = new Zombie(*zombiego);  // novo componente de zombie
        zombiego->AddComponent(zombie);          // adiciona componente à entidade

        zombiego->box.x = InputManager::GetInstance().GetMouseX() + static_cast<int>(Camera::pos.x);
        zombiego->box.y = InputManager::GetInstance().GetMouseY() + static_cast<int>(Camera::pos.y); // compensa deslocamento da câmera

        AddObject(zombiego);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state
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

