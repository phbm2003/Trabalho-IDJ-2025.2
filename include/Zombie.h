#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Component.h"

class Zombie : public Component {
public:
    Zombie (GameObject& associated);
    void Damage (int damage);
    void Update (float dt);
    void Render ();

private:
    int hitpoints;
};
#endif // ZOMBIE_H
