#include "Component.h"

Component::Component(GameObject& associated) : associated(associated) {} // initializer lists para atribuir referência ou constantes
// associanted da classe Component sendo atribuído associated passado como parâmetro
Component::~Component (){}

void Component::Start() {

}

void Component::NotifyCollision (GameObject& other){}
