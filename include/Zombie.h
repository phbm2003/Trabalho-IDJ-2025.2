#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include <iostream>
#include <ostream>

class Zombie : public Component {
public:
    Zombie (GameObject& associated);
    void Damage (int damage);
    void Update (float dt) override;
    void Render () override;

    void NotifyCollision(GameObject& other) override;
    static int contador;

    ~Zombie() {
        contador--;
        std::cout << "800" << std::endl;
    }

private:
    int hitpoints;
    Sound deathSound;
    Sound heatSound;
    Timer hitTimer;
    bool hit;
    Timer deathTimer;
    bool dead;
};
#endif // ZOMBIE_H
