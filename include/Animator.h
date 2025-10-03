#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <unordered_map>
#include "Animation.h"
#include "GameObject.h"
#include <string>

class Animator : public Component {
public:
    Animator (GameObject& associated);
    void Update (float dt);
    void Render ();
    void SetAnimation (std::string name);
    void AddAnimation (std::string name, Animation anim);

private:
    std::unordered_map<std::string, Animation>animations;
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;
};
#endif // ANIMATOR_H
