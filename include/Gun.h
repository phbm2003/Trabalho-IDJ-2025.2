#ifndef GUN_H
#define GUN_H

#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"
#include <memory>

class Gun : public Component {
public:
    Gun (GameObject& associated, std::weak_ptr<GameObject> character);
    void Update (float dt);
    void Render ();
    void Shoot (Vec2 target);

    void SetAngle(float angle) {
        this->angle = angle;
    }

    float& GetAngle() {
        return angle;
    }
    std::weak_ptr<GameObject> character;
    Sound shotSound;
private:

    Sound reloadSound;
    int cooldownState;
    Timer cdTimer;

    float angle;
};

#endif // GUN_H
