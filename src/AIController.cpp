#include "AIController.h"
#include "Bullet.h"
#include "Character.h"
#include "Game.h"
#include "Gun.h"
#include <cmath>

AIController::AIController(GameObject& associated) : Component(associated){
    this->state = AIState::RESTING;
}
void AIController::Update (float dt){
    if (Character::player == nullptr) {
        return;
    }

    if (associated.GetComponent<Character>()->player == nullptr) {
        return;
    }

    if (associated.GetComponent<Character>()->player->dead) {
        return;
    }

    if (associated.GetComponent<Character>()->player == associated.GetComponent<Character>()) {
        return;
    }

    restTimer.Update(dt);

    if (this->state == AIState::RESTING) {
        if (restTimer.Get() > 1.5f) {
            state = AIState::MOVING;
            destination = {associated.box.x, associated.box.y};
            associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, associated.box.x, associated.box.y));
        }
        return;
    } else if (this->state == AIState::MOVING) {
        Vec2 target = Character::player->GetAssociated().box.getCentro();
        Vec2 origem = associated.box.getCentro();

        Vec2 delta = target.sub(origem);
        float distancia = delta.mag();

        Vec2 direcao = delta.normal();

        float angle2 = direcao.fase();
        float velocidade = 1.0f;

        if (distancia <= 250.0f) {
            associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::SHOOT, target.x, target.y));

            restTimer.Restart();
            state = RESTING;
            return;

        } else {
            associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, direcao.x, direcao.y));
        }

    }
}
void AIController::Render (){}
