#ifndef CHARACTER_H
#define CHARACTER_H
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"
#include <memory>
#include <queue>
#include <string>

class Character : public Component {
public:
    Character (GameObject& associated, std::string sprite);
    ~Character ();
    void Start();
    void Update (float dt);
    void Render ();

    class Command {
    public:
        enum CommandType {MOVE, SHOOT};
        Command (CommandType type, float x, float y);
        CommandType type;
        Vec2 pos;
    };

    void Issue (Command task);
    static Character* player;
private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
};

#endif // CHARACTER_H
