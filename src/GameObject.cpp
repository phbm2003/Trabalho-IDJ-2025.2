#include "GameObject.h"

GameObject::GameObject(){
    isDead = false;
}
GameObject::~GameObject(){
    for (int index = components.size() - 1; index >= 0; index--){
        delete components[index].get();   // deleta ponteiro associado, oq automaticamente deleta o objeto unique_ptr
    }
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
    components.emplace_back(std::unique_ptr<Component>(cpt));  // adiciona no fim do vetor objeto que tem ponteiro para objeto do tipo Component
}
void GameObject::RemoveComponent(Component* cpt){
    for (int index = 0; index <= components.size() -1; index++){
        if (components[index].get() == cpt) {  // pega ponteiro do objto unique_ptr e compara com cpt
            components.erase(components.begin() + index); // chama automaticamente método Render do objeto apontado Component
        }
    }
}


