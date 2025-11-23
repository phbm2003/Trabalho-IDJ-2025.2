#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"
#include <iostream>
#include <memory>

class Bullet : public Component {
public:
    Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance, std::weak_ptr<GameObject> shooter);
    void Update (float dt) override;
    void Render () override;
    int GetDamage ();
    ~Bullet() {
        std::cout << "Bullet destruída!" << std::endl;
    }
    void extracted(GameObject &associated);
    void NotifyCollision(GameObject &associated) override;
    bool targetsPlayer;

    bool hit = false;
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};
#endif // BULLET_H
