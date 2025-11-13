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

    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    ~State ();

private:
    Music music;
    bool quitRequested;

    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif // STATE_H
