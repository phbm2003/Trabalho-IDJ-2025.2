#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Rect.h"
#include "TileMap.h"
#include "TileSet.h"

State::State() {
    quitRequested = false;

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
    /*GameObject* bg = new GameObject();
    SpriteRenderer* spriteR = new SpriteRenderer(*bg, "bin/recursos/img/Background.png", 1, 1); // ponteiro para um novo obj SpriteRenderer
    bg->AddComponent(spriteR);  // adiciona ao GameObject ponteiro pra um SpriteRenderer

    bg->box.x = 0;  // incializar bg
    bg->box.y = 0;

    AddObject(bg);  // garante que bg seja atualizado*/

    music.Open("bin/recursos/audio/BGM.wav");
    music.Play(-1);

    GameObject* zombiego = new GameObject(); // nova entidade zombie

    Zombie* zombie = new Zombie(*zombiego);  // novo componente de zombie
    zombiego->AddComponent(zombie);          // adiciona componente à entidade

    zombiego->box.x = 600; // seta posição do zombie no background
    zombiego->box.y = 450;

    AddObject(zombiego);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state

    // mais zumbis

    GameObject* zombiego2 = new GameObject(); // nova entidade zombie

    Zombie* zombie2 = new Zombie(*zombiego2);  // novo componente de zombie
    zombiego2->AddComponent(zombie2);          // adiciona componente à entidade

    zombiego2->box.x = 600; // seta posição do zombie no background
    zombiego2->box.y = 750;

    AddObject(zombiego2);


    GameObject* zombiego3 = new GameObject(); // nova entidade zombie

    Zombie* zombie3 = new Zombie(*zombiego3);  // novo componente de zombie
    zombiego3->AddComponent(zombie3);          // adiciona componente à entidade

    zombiego3->box.x = 700; // seta posição do zombie no background
    zombiego3->box.y = 300;

    AddObject(zombiego3);


    GameObject* zombiego4 = new GameObject(); // nova entidade zombie

    Zombie* zombie4 = new Zombie(*zombiego4);  // novo componente de zombie
    zombiego4->AddComponent(zombie4);          // adiciona componente à entidade

    zombiego4->box.x = 850; // seta posição do zombie no background
    zombiego4->box.y = 400;

    AddObject(zombiego4);


    GameObject* zombiego5 = new GameObject(); // nova entidade zombie

    Zombie* zombie5 = new Zombie(*zombiego5);  // novo componente de zombie
    zombiego5->AddComponent(zombie5);          // adiciona componente à entidade

    zombiego5->box.x = 350; // seta posição do zombie no background
    zombiego5->box.y = 450;

    AddObject(zombiego5);
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

