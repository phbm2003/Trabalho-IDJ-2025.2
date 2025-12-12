#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "State.h"
#include "TileSet.h"

class StageState : public State {
public:
    StageState();
    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Resume () override;
    void Pause () override;
    //std::weak_ptr<GameObject> AddObject(GameObject* go);
    //std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    ~StageState ();
private:
    //Music music;
    //bool quitRequested;

    Music backgroundMusic;

    //bool started;
    //std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif // STAGESTATE_H
