#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H
#include "GameObject.h"
#include "Timer.h"
#include "Wave.h"

class WaveSpawner : public Component {
public:
    WaveSpawner(GameObject& associated);
    void Update (float dt);
    void Render ();
    int zombieCounter;
    std::vector<Wave> waves;
    Timer zombieCooldownTimer;
    int currentWave;

    bool finished = false;

    int charCounter;
    Timer charCooldownTimer;
};

#endif // WAVESPAWNER_H
