#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"
#include <iostream>

class Bullet : public Component {
public:
    Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance);
    void Update (float dt);
    void Render ();
    int GetDamage ();
    ~Bullet() {
        std::cout << "Bullet destruída!" << std::endl;
    }
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};
#endif // BULLET_H
