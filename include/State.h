#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"


class State {
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    // Versão 2.0
    ~State ();
    void AddObject (GameObject* go);
private:
    Music music;
    bool quitRequested;

    // Versão 2.0
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H
