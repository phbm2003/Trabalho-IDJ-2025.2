#include "Character.h"
#include "Animator.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include <iostream>

Character* Character::player = nullptr;

Character::Character (GameObject& associated, std::string sprite) : Component (associated) {
    speed = {0, 0};
    linearSpeed = 300;
    hp = 100;

    SpriteRenderer* characterS = new SpriteRenderer(associated, sprite, 3, 4); // novo componente de character

    associated.AddComponent(characterS);  // adiciona componente à entidade

    Animator* characterA = new Animator(associated);
    associated.AddComponent(characterA);  // adiciona componente à entidade
    characterA->AddAnimation("idle", Animation(6, 9, 0.3f)); // animação de parado
    characterA->AddAnimation("walking", Animation(0, 5, 0.1f));
    characterA->AddAnimation("dead", Animation(10, 11, 0.1f));
    characterA->AddAnimation("walkingleft", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL)); // inverte na horizontal para mover à esquerda

    characterA->SetAnimation("idle"); // character fica parado

    if (sprite == "bin/recursos/img/Player.png") {
        player = this;
    }
}

Character::~Character () {
    if (player == this) { // compara valor do endereço de player com endereço do objeto atual
        player = nullptr;
    }
}

void Character::Start() {
    GameObject* weapongo = new GameObject(); // nova entidade arma

    std::weak_ptr<GameObject> character = Game::GetInstance().GetState().GetObjectPtr(&associated); // acessa instância do game para acessar o state associado e assim obter o ponteiro shared_ptr associado ao GameObject

    Gun* weapon = new Gun(*weapongo, character);  // novo componente de arma
    weapongo->AddComponent(weapon);          // adiciona componente à entidade

    Game::GetInstance().GetState().AddObject(weapongo);  // adiciona entidade ao vetor de ponteiros únicos de entidade em state

    this->gun = Game::GetInstance().GetState().GetObjectPtr(weapongo); // atribui ponteiro GameObj associado a arma ao ponteiro weak_ptr do character
}

void Character::Update (float dt) {
    speed = {0, 0}; // zera speed para que o personagem fique parado caso nenhum comando seja realizado

    while (taskQueue.size() != 0) {
        Command task = taskQueue.front(); // pega primeiro elemento da queue

        if (task.type == Command::MOVE) {
            Vec2 direction = task.pos;
            direction = direction.normal();
            speed = direction.mult(linearSpeed); // velocidade constante

        } else if (task.type == Command::SHOOT) {
            std::shared_ptr<GameObject> gunPtr = gun.lock();
            if (gunPtr) {
                Gun* gunComponent = gunPtr->GetComponent<Gun>();
                if (gunComponent) {
                    gunComponent->Shoot(task.pos);
                }
            }
        }
        taskQueue.pop(); // remove esse elemento
    }
    associated.box.x += speed.x * dt; // atualizar posições
    associated.box.y += speed.y * dt;

    Animator* animator = associated.GetComponent<Animator>();

    // animação de andar caso esteja vivo
    if ((hp > 0) && (speed.x > 0)) {
        animator->SetAnimation("walking");

    } else if ((hp > 0) && (speed.x < 0)) {
        animator->SetAnimation("walkingleft");

    } else if ((hp > 0) && (speed.x == 0) && (speed.y != 0)) {
        animator->SetAnimation("walking");

    }    else if ((hp > 0) && (speed.mag() == 0)) { // animação de ficar parado caso velocidade seja 0
        animator->SetAnimation("idle");

    } else if (hp <= 0) {
        animator->SetAnimation("dead"); // animação de morte caso vida seja 0

        deathTimer.Update(dt);
        if (deathTimer.Get() > 2.0f)  { // tempo após a animação de morte
            associated.RequestDelete();
            return;
        }
    }
}

void Character::Render () {}
Character::Command::Command (CommandType type, float x, float y) : type(type) , pos(x, y) {}

void Character::Issue (Command task) {
    taskQueue.push(task);  // adiciona tarefa
}
