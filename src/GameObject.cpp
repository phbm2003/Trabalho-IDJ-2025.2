#include "GameObject.h"
#include <iostream>

GameObject::GameObject(){
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject(){
    for (size_t i = 0; i < GetAllComponents().size(); ++i) {
        RemoveComponent(components[i].get());
    }
}

void GameObject::Update(float dt){
    std::cout << "Quantos componentes tem: " << components.size() << "\n";
    for (int index = 0; index <= components.size() -1; index++){
        std::cout << "Quantos componentes tem: " << index + 1 << "\n" << components[index].get() << "\n";
        components[index]->Update(dt);   // chama automaticamente método Update do objeto apontado Component
    }
    std::cout << "Terminou?";
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
    std::cout << "tamanho COMPO: # " <<  components.size() << "\n" << std::endl;
    for (int index = 0; index <= components.size() -1; index++){
        std::cout << "COMPONENTES: # " << index + 1 << "\n" << components[index].get() << std::endl;
        if (components[index].get() == cpt) {  // pega ponteiro do objto unique_ptr e compara com cpt
            components.erase(components.begin() + index); // chama automaticamente método Render do objeto apontado Component
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
