#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Rect.h"
#include <vector>
#include <memory>  // biblioteca com unique_ptr

class GameObject {
public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    std::vector<std::shared_ptr<Component>>& GetAllComponents() {
        return components;
    }
    template<typename T>
    T* GetComponent(){
        long unsigned int index;
        for(index=0;index<components.size();index++){
            T* component = dynamic_cast<T*>(components[index].get());   // pega o objeto (unique_ptr) e pega seu único ponteiro armazenado (Component*)
                                                                        // dynamic tenta converter ponteiro base Component* para um tipo derivado específico
            if(component != nullptr){
                return component;
            }
        }
        return nullptr;
    }
    Rect box;

    void Start();
    bool started;

    double angleDeg;
private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};

#endif // GAMEOBJECT_H
