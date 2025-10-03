#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Component.h"
#include "Sound.h"

class Zombie : public Component {
public:
    Zombie (GameObject& associated);
    void Damage (int damage);
    void Update (float dt);
    void Render ();

private:
    int hitpoints;
    Sound deathSound;
};
#endif // ZOMBIE_H
