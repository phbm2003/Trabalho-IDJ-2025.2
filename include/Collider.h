#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"
#include "Rect.h"
#include "Vec2.h"

class Collider : public Component {
public:
    Collider (GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    Rect box;
    void Update (float dt);
    void Render ();
    void SetScale (Vec2 scale);
    void SetOffset (Vec2 offset);
private:
    Vec2 scale;
    Vec2 offset;
};

#endif // COLLIDER_H
