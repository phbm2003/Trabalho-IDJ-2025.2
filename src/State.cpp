#include "State.h"
#include <iostream>
#include <ostream>

State::State () {
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State () {
    //std::cout << "789" << std::endl;
    //std::cout << "qtd de gameobjetos" << objectArray.size() << std::endl;
    objectArray.clear();
    //std::cout << "790" << std::endl;

}

std::weak_ptr<GameObject> State::AddObject (GameObject* object) {
    std::shared_ptr<GameObject> pointer(object);
    objectArray.push_back(pointer);
    if (pointer) {
        //std::cout << "criou um objeto válido\n" << go;
    }
    if (started) {
        pointer->Start();
    }
    return pointer;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* object) {
    for(int index = 0; index < objectArray.size(); index++){ // percorre vetor

        if(objectArray[index].get() == object){ // verifica se ponteiro é igual ao parâmetro
            return objectArray[index];
        }
    }

    return std::weak_ptr<GameObject>(); // retorna weak_ptr vazio
}

bool State::PopRequested () {
    return popRequested;
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::StartArray () {
    if (objectArray.size() > 0){
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Start();  // chama Start pra cada GameObject
        }
    }
}

void State::UpdateArray (float dt) {
    for (size_t i = 0; i < objectArray.size(); ++i) {
        if (!objectArray[i]->IsDead()) {
            objectArray[i]->Update(dt);
        }
    }
}

void State::RenderArray () {
    if (objectArray.size() != 0){
        int i = 1;
        for (int index = 0; index <= objectArray.size() -1; index++){
            objectArray[index]->Render();  // chama render pra cada GameObject
            i++;
        }
    }
}
