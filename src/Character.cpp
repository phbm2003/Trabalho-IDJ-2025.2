#include "Character.h"
#include "Animator.h"
#include "Bullet.h"
#include "Collider.h"
#include "EndState.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include "Zombie.h"
#include "Camera.h"
#include <iostream>
#include "GameData.h"

Character* Character::player = nullptr;
int Character::contador = 0;
bool Character::playerDied = false;

Character::Character (GameObject& associated, std::string sprite) : Component (associated), deathSound (Sound("bin/recursos/audio/Dead.wav")), heatSound (Sound("bin/recursos/audio/Hit1.wav")) {
    cooldownState = 0;

    dead = false;

    speed = {0, 0};

    /* if (sprite.empty()) {
        sprit = "abc";
    } else {
        sprit = sprite;
    }*/
    this->sprit = sprite;

    //hp = 10;

    SpriteRenderer* characterS = new SpriteRenderer(associated, sprite, 3, 4); // novo componente de character

    associated.AddComponent(characterS);  // adiciona componente à entidade

    Animator* characterA = new Animator(associated);
    associated.AddComponent(characterA);  // adiciona componente à entidade

    characterA->AddAnimation("idle", Animation(6, 9, 0.3f)); // animação de parado
    characterA->AddAnimation("walking", Animation(0, 5, 0.1f));
    characterA->AddAnimation("dead", Animation(10, 11, 0.3f));
    characterA->AddAnimation("walkingleft", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL)); // inverte na horizontal para mover à esquerda

    characterA->SetAnimation("idle"); // character fica parado

    if (sprite == "bin/recursos/img/Player.png") {
        player = this;
        hp = 50;
        linearSpeed = 300;
    } else {
        contador++;
        hp = 20;
        linearSpeed = 300;
    }
}

Character::~Character () {
    //std::cout << "795" << std::endl;
    if (this != player) {
        contador--;
    }

    if (player == this) { // compara valor do endereço de player com endereço do objeto atual
        player = nullptr;
    }
    //std::cout << "796" << std::endl;
}

void Character::Start() {
    GameObject* weapongo = new GameObject(); // nova entidade arma

    std::weak_ptr<GameObject> character = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated); // acessa instância do game para acessar o state associado e assim obter o ponteiro shared_ptr associado ao GameObject

    Gun* weapon = new Gun(*weapongo, character);  // novo componente de arma
    weapongo->AddComponent(weapon);          // adiciona componente à entidade

    Game::GetInstance().GetCurrentState().AddObject(weapongo);  // adiciona entidade ao vetor de ponteiros únicos de entidade em state

    this->gun = Game::GetInstance().GetCurrentState().GetObjectPtr(weapongo); // atribui ponteiro GameObj associado a arma ao ponteiro weak_ptr do character

    Collider* characterC = new Collider(associated);
    associated.AddComponent(characterC);  // adiciona componente à entidade
}

void Character::Update (float dt) {
    speed = {0, 0}; // zera speed para que o personagem fique parado caso nenhum comando seja realizado

    cdTimer.Update(dt);

    if (cdTimer.Get() > 0.5) {
        cooldownState = 0;
    }

    if (!dead) {
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
    }
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    // _______________________________________
    // 2) LIMITES DO MAPA
    float minX = 640;
    float maxX = 1920;
    float minY = 512;
    float maxY = 2048;

    if (associated.box.x < minX)
        associated.box.x = minX;

    if (associated.box.x + associated.box.w > maxX)
        associated.box.x = maxX - associated.box.w;

    if (associated.box.y < minY)
        associated.box.y = minY;

    if (associated.box.y + associated.box.h > maxY)
        associated.box.y = maxY - associated.box.h;

    Animator* animator = associated.GetComponent<Animator>();

    // animação de andar caso esteja vivo
    if ((hp > 0) && (speed.x > 0)) {
        animator->SetAnimation("walking");

    } else if ((hp > 0) && (speed.x < 0)) {
        animator->SetAnimation("walkingleft");

    } else if ((hp > 0) && (speed.x == 0) && (speed.y != 0)) {
        animator->SetAnimation("walking");

    } else if ((hp > 0) && (speed.mag() == 0)) { // animação de ficar parado caso velocidade seja 0
        animator->SetAnimation("idle");

    } else if ((hp <= 0)) {

        if (!dead) {
            if (this == Character::player) {

                Character::player = nullptr;
                Camera::Unfollow();
            }

            animator->SetAnimation("dead");
            deathSound.Play(1);
            dead = true;
            //associated.RemoveComponent(associated.GetComponent<Collider>());
        }

        deathTimer.Update(dt);

        if (deathTimer.Get() > 5.0f)  { // tempo após a animação de morte
            associated.RequestDelete();
            if (auto g = gun.lock()) {
                g->RequestDelete();
            }

            //if (sprit == "bin/recursos/img/Player.png") {
            //    Character::playerDied = true;
            //}

            return;
        }
    }
}

void Character::Render () {}
Character::Command::Command (CommandType type, float x, float y) : type(type) , pos(x, y) {}

void Character::Issue (Command task) {
    taskQueue.push(task);  // adiciona tarefa
}
void Character::NotifyCollision(GameObject& associated) { // notificação de colisão
    auto bullet = associated.GetComponent<Bullet>();
    auto zombie = associated.GetComponent<Zombie>();
    auto character = associated.GetComponent<Character>();

    // só leva dano se for zumbi ou bala ou character
    if (!bullet && !zombie && !character) return;

    if (dead || hp <= 0) {
        return;
    }

    if (bullet && !cooldownState && hp > 0) {
        if (bullet->hit) return;
        bullet->hit = true;

        bool isPlayer = (this == player);
        bool hitsPlayer = bullet->targetsPlayer;

        if ((hitsPlayer && isPlayer) || (!hitsPlayer && !isPlayer)) {
            hp = hp - 10;
            heatSound.Play(1);
            cooldownState = 1;
            cdTimer.Restart();
        }

        return;
    }

    if ((zombie || character) && !cooldownState) {
        if (hp > 0) {
            if (zombie) {
                hp = hp - 10; // recebe 10 de dano se contato for com zumbi
                heatSound.Play(1);
                cooldownState = 1;
                cdTimer.Restart();
                return;
            }

            if (character) {
                std::cout << "HP = " << hp << std::endl;
                hp = hp - 10; // recebe 10 de dano se contato for com character
                heatSound.Play(1);
                cooldownState = 1;
                cdTimer.Restart();
                return;
            }
        }
    }
}
