#include "GameObject.h"
#include <iostream>

GameObject::GameObject(){
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){
    for (int index = 0; index <= components.size() -1; index++){
        components[index]->Update(dt);   // chama automaticamente método Update do objeto apontado Component
    }
}

void GameObject::Render(){
    for (int index = 0; index <= components.size() -1; index++){
        components[index]->Render();   // chama automaticamente método Render do objeto apontado Component
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    std::shared_ptr<Component> pointer(cpt);
    components.push_back(pointer); // adiciona no fim do vetor objeto que tem ponteiro para objeto do tipo Component

    if (started) {
        pointer->Start();
    }

}

void GameObject::RemoveComponent(Component* cpt){
    for (int index = 0; index <= components.size() -1; index++){
        if (components[index].get() == cpt) {  // pega ponteiro do objto unique_ptr e compara com cpt
            components.erase(components.begin() + index); // chama automaticamente método Render do objeto apontado Component
            return;
        }
    }
}

void GameObject::Start(){
    if (components.size() > 0){
        for (int index = 0; index <= components.size() -1; index++){
            components[index]->Start();  // chama Start pra cada component
        }
    }

    started = true;

}

void GameObject::NotifyCollision(GameObject& other) {
    for (int index = 0; index <= components.size() -1; index++){
        components[index]->NotifyCollision(other);   // chama automaticamente método Update do objeto apontado Component
    }
}
