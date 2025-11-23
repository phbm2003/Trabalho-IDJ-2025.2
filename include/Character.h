#ifndef CHARACTER_H
#define CHARACTER_H
#include "Component.h"
#include "Sound.h"
#include "Timer.h"
#include "Vec2.h"
#include <memory>
#include <queue>
#include <string>

class Character : public Component {
public:
    Character (GameObject& associated, std::string sprite);
    ~Character ();

    void Start() override;
    void Update (float dt) override;
    void Render () override;
    GameObject& GetAssociated() const { return associated; }
    class Command {
    public:
        enum CommandType {MOVE, SHOOT};
        Command (CommandType type, float x, float y);
        CommandType type;
        Vec2 pos;
    };

    void Issue (Command task);
    static Character* player;

    void NotifyCollision(GameObject& associated) override;
    Sound deathSound;
    Sound heatSound;
    bool dead = false;

    std::weak_ptr<GameObject> GetGun() {
        return gun;
    }

    static int contador;
private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;

    int cooldownState;
    Timer cdTimer;

};

#endif // CHARACTER_H
