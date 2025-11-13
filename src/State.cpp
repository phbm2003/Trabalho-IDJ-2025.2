#include "State.h"
#include "Character.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Rect.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include <algorithm>
#include <iostream>

State::State() {
    quitRequested = false;
    started = false;
    // carregar background primeiro

    GameObject* bg = new GameObject();

    SpriteRenderer* spriteR = new SpriteRenderer(*bg, "bin/recursos/img/Background.png", 1, 1);
    spriteR->SetcameraFollower(true);

    bg->AddComponent(spriteR);
    bg->box.x = 0;
    bg->box.y = 0;

    AddObject(bg); // se ainda quiser passar ponteiro cru

    // carregar mapa por cima

    GameObject* tm = new GameObject();

    TileSet* TileSetR = new TileSet(64, 64, "bin/recursos/img/Tileset.png"); // ponteiro para um novo obj TileMap
    TileMap* TileMapR = new TileMap(*tm, "bin/recursos/map/map.txt", TileSetR); // ponteiro para um novo obj TileMap

    tm->AddComponent(TileMapR);  // adiciona ao GameObject ponteiro pra um TileMap
    tm->box.x = 0;  // incializar tm
    tm->box.y = 0;

    AddObject(tm); // garante que tm seja atualizado*/

    // instanciar Character

    GameObject* ch = new GameObject();

    Character* chR = new Character(*ch, "bin/recursos/img/Player.png");

    PlayerController* plR = new PlayerController(*ch);

    ch->AddComponent(chR);
    ch->AddComponent(plR); // adiciona controladora ao objeto

    ch->box.x = 1280;  // dentro da tela
    ch->box.y = 1280;

    AddObject(ch);

    Camera::Follow(ch);
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

    for (size_t i = 0; i < objectArray.size(); ++i) {
        if (!objectArray[i]->IsDead()) {
            objectArray[i]->Update(dt);
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
        int i = 1;
        for (int index = 0; index <= objectArray.size() -1; index++){
            std::cout << "Objeto que vai renderizar #" << index << " em " << objectArray[index].get() << std::endl;
            objectArray[index]->Render();  // chama render pra cada GameObject
            i++;
        }
    }
    std::cout << "Tamanho RENDER DEPOIS: " << objectArray.size() << std::endl;
}

State::~State () {
    objectArray.clear();
}

void State::Start() {
    LoadAssets();

    if (objectArray.size() > 0){
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Start();  // chama Start pra cada GameObject
        }
    }

    started = true;

}
std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> pointer(go);
    objectArray.push_back(pointer);
    if (pointer) {
        std::cout << "criou um objeto válido\n" << go;
    }
    if (started) {
        pointer->Start();
    }
    std::cout << "tá adicionando?\n";
    return pointer;
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for(int index = 0; index < objectArray.size(); index++){ // percorre vetor

        if(objectArray[index].get() == go){ // verifica se ponteiro é igual ao parâmetro
            return objectArray[index];
        }
    }

    return std::weak_ptr<GameObject>(); // retorna weak_ptr vazio
}
