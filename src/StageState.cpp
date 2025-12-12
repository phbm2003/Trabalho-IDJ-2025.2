#include "StageState.h"
#include "Character.h"
#include "Collider.h"
#include "EndState.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "WaveSpawner.h"
#include "Zombie.h"
#include "Rect.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"
#include <algorithm>
#include <iostream>
#include "Game.h"
#include "GameData.h"

StageState::StageState() {
    //quitRequested = false;
    //started = false;
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

    GameObject* ws = new GameObject();

    WaveSpawner* wsR = new WaveSpawner(*ws);

    ws->AddComponent(wsR);

    AddObject(ws);
}

/*bool StageState::QuitRequested() {
    return quitRequested;
}*/

void StageState::LoadAssets() {
    backgroundMusic.Open("bin/recursos/audio/BGM.wav");
    backgroundMusic.Play(-1);
}

void StageState::Update(float dt) {
    // Versão 2.0
    Camera::Update(dt);
    //std::cout << "x1" << std::endl;
    // Atualiza todos os objetos

    for (size_t i = 0; i < objectArray.size(); ++i) {
        if (!objectArray[i]->IsDead()) {
            objectArray[i]->Update(dt);
        }
    }

    //std::cout << "x2" << std::endl;
    // Verifica colisão
    std::vector<int> v;

    for (size_t i = 0; i < objectArray.size(); ++i) {
        if (objectArray[i]->GetComponent<Collider>()) {
            v.push_back(i);
        }
    }
    //std::cout << "x3" << std::endl;
    if (v.size() >= 2){
        //std::cout << "x31" << std::endl;
        for (size_t i = 0; i < v.size(); ++i) {
            //std::cout << "x32" << std::endl;
            for (size_t j = i + 1; j < v.size(); ++j) {
                //std::cout << "x33" << std::endl;
                auto colA = objectArray[v[i]]->GetComponent<Collider>();
                auto colB = objectArray[v[j]]->GetComponent<Collider>();
                if (!colA || !colB) {
                    //std::cout << "Collider faltando" << std::endl;
                    continue;
                }
                if (Collision::IsColliding(objectArray[v[i]]->GetComponent<Collider>()->box, objectArray[v[j]]->GetComponent<Collider>()->box, objectArray[v[i]]->angleDeg, objectArray[v[j]]->angleDeg)){
                    //std::cout << "x34" << std::endl;
                    objectArray[v[i]]->NotifyCollision(*objectArray[v[j]]);
                    //std::cout << "x35" << std::endl;
                    objectArray[v[j]]->NotifyCollision(*objectArray[v[i]]);
                    //std::cout << "x36" << std::endl;
                }
            }
        }
    }
    // std::cout << "x4" << std::endl;
    // Remove objetos mortos (de trás pra frente)
    for (int i = objectArray.size() - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead()) {
            // Se o foco da câmera for esse objeto, desfoca
            if (Camera::GetFocus() == objectArray[i].get()) {
                Camera::Unfollow();
            }

            auto character = objectArray[i]->GetComponent<Character>();
            if (character && character == Character::player) {
                Character::player = nullptr;
            }
            objectArray.erase(objectArray.begin() + i);
        }
    }

    // Lógica de PAUSA/SAÍDA (ESC)
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        popRequested = true;
    }

    // Lógica de SAÍDA FORÇADA (QUIT)
    if (InputManager::GetInstance().QuitRequested()) {
        quitRequested = true;
    }

    if (popRequested) {
        // Se foi o fim do jogo, empurra o EndState
        if (GameData::playerVictory || GameData::playerDefeat) {
            Game::GetInstance().Push(new EndState());
        }
        // Se popRequested for true, o Game::Run irá deletar este StageState.
        // QUALQUER COISA EXECUTADA DEPOIS PODE CAUSAR O CRASH.
        return; // <--- ADICIONE ESTE RETURN. Isso garante que nada mais chame este StageState.
    }
}

void StageState::Render() {
    if (objectArray.size() != 0){
        int i = 1;
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Render();  // chama render pra cada GameObject
            i++;
        }
    }
}

StageState::~StageState() {

    //objectArray.clear();
}

void StageState::Start() {
    LoadAssets();

    if (objectArray.size() > 0){
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Start();  // chama Start pra cada GameObject
        }
    }

    started = true;

}

void StageState::Pause(){}
void StageState::Resume() {}

/*std::weak_ptr<GameObject> StageState::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> pointer(go);
    objectArray.push_back(pointer);
    if (pointer) {
        //std::cout << "criou um objeto válido\n" << go;
    }
    if (started) {
        pointer->Start();
    }
    return pointer;
}*/

/*std::weak_ptr<GameObject> StageState::GetObjectPtr(GameObject* go) {
    for(int index = 0; index < objectArray.size(); index++){ // percorre vetor

        if(objectArray[index].get() == go){ // verifica se ponteiro é igual ao parâmetro
            return objectArray[index];
        }
    }

    return std::weak_ptr<GameObject>(); // retorna weak_ptr vazio
}*/
