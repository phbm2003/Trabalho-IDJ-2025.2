#include "Component.h"
#include <iostream>

Component::Component(GameObject& associated) : associated(associated) {} // initializer lists para atribuir referência ou constantes
// associanted da classe Component sendo atribuído associated passado como parâmetro
Component::~Component (){
    //std::cout << "[Component Destroyed] " << typeid(*this).name() << std::endl;
}

void Component::Start() {

}

void Component::NotifyCollision (GameObject& other){}
