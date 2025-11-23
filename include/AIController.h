#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "GameObject.h"
#include "Timer.h"

class AIController : public Component {
public:
    AIController(GameObject& associated);
    void Update (float dt);
    void Render ();
private:
    int npcCounter;
    enum AIState { MOVING, RESTING };
    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif // AICONTROLLER_H
