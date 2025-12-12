#include "Zombie.h"
#include "Bullet.h"
#include "Collider.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include <cmath>

int Zombie::contador = 0;

Zombie::Zombie (GameObject& associated) : Component (associated), deathSound("bin/recursos/audio/Dead.wav"), heatSound("bin/recursos/audio/Hit0.wav"){
    contador++;
    dead = false;
    hit = false;
    hitpoints = 10;
    SpriteRenderer* zombieS = new SpriteRenderer(associated, "bin/recursos/img/Enemy.png", 3, 2); // novo componente de zombie
    //zombieS->SetFrame(1);
    associated.AddComponent(zombieS);  // // adiciona componente à entidade

    Animator* zombieA = new Animator(associated);
    associated.AddComponent(zombieA);  // // adiciona componente à entidade

    Collider* zombieC = new Collider(associated);
    associated.AddComponent(zombieC);  // // adiciona componente à entidade

    zombieA->AddAnimation("walking", Animation(0, 3, 0.1f));
    zombieA->AddAnimation("dead", Animation(5, 5, 0.1f));
    zombieA->AddAnimation("hit", Animation(4,4, 0.2f)); // animação de hit
    zombieA->AddAnimation("walkingleft", Animation(0, 3, 0.1f, SDL_FLIP_HORIZONTAL));
    zombieA->AddAnimation("hitleft", Animation(4,4, 0.2f, SDL_FLIP_HORIZONTAL)); // animação de hit

    zombieA->SetAnimation("walking"); // zumbi anda

}
void Zombie::Damage (int damage){
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        SpriteRenderer* zombieS = associated.GetComponent<SpriteRenderer>();

        if (zombieS != nullptr && !dead) { // verifica se zombieS já foi adicionado
            associated.GetComponent<Animator>()->SetAnimation("dead"); // chama método setanimation do componente do tipo Animator presente no GameObject passado
            deathSound.Play(1);
            deathTimer.Restart();
            dead = true;
            associated.RemoveComponent(associated.GetComponent<Collider>());
        }
    }
}
void Zombie::Update (float dt){
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    if (Character::player == nullptr) {
        if (!(hitpoints > 0) && deathTimer.Get() >= 5) {
            if (Camera::GetFocus() == &associated) {
                Camera::Unfollow();
            }
            //Animator* animator = associated.GetComponent<Animator>();
            //SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();

            //if (animator) associated.RemoveComponent(animator); // deleta apenas zumbi
            //if (sprite) associated.RemoveComponent(sprite);

            associated.RequestDelete();
            return;
        } else {
            return;
        }
    }

    Vec2 target = Character::player->GetAssociated().box.getCentro();
    Vec2 origem = associated.box.getCentro();

    Vec2 delta = target.sub(origem);
    Vec2 direcao = delta.normal();

    if (!(hitpoints > 0) && deathTimer.Get() >= 3) {
        if (Camera::GetFocus() == &associated) Camera::Unfollow();
        associated.RequestDelete();
        return;
    }

    if (hitpoints > 0 && hit == true && hitTimer.Get() >= 0.5) {
        if (direcao.x >= 0) {
            associated.GetComponent<Animator>()->SetAnimation("walking");
        } else {
            associated.GetComponent<Animator>()->SetAnimation("walkingleft");
        }
        hit = false;
    }

    if (Character::player && !Character::player->dead && !dead) {
        Vec2 target = Character::player->GetAssociated().box.getCentro();
        Vec2 origem = associated.box.getCentro();

        Vec2 delta = target.sub(origem);
        Vec2 direcao = delta.normal();

        float angle2 = direcao.fase();
        float velocidade = 100.0f;

        associated.box.x = associated.box.x + direcao.x * velocidade * dt;
        associated.box.y = associated.box.y + direcao.y * velocidade * dt;

        if (direcao.x >= 0 && !hit) {
            associated.GetComponent<Animator>()->SetAnimation("walking");
        } else if (!hit) {
            associated.GetComponent<Animator>()->SetAnimation("walkingleft");
        }

    } else {
        //Vec2 target = Character::player->GetAssociated().box.getCentro();
        Vec2 origem = associated.box.getCentro();
        //Vec2 direcao = (target.sub(origem)).normal();

        float angle2 = origem.fase();
        float velocidade = 0.0f;

        associated.box.x = associated.box.x + origem.x * velocidade * dt;
        associated.box.y = associated.box.y + origem.y * velocidade * dt;
    }

    /*
    int mouseWorldX = InputManager::GetInstance().GetMouseX() + static_cast<int>(Camera::pos.x); // posição considerando deslocamento da câmera
    int mouseWorldY = InputManager::GetInstance().GetMouseY() + static_cast<int>(Camera::pos.y);

    if (    InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && // botão esquerdo do mouse pressionado?
            mouseWorldX >= associated.box.x && // posição do mouse dentro da área do zumbi?
            mouseWorldX <= associated.box.x + associated.box.w &&
            mouseWorldY >= associated.box.y &&
            mouseWorldY <= associated.box.y + associated.box.h &&
            !dead) {

        Damage(20);
        heatSound.Play(1);
        if (hitpoints > 0) {
            hit = true;
            hitTimer.Restart();
            associated.GetComponent<Animator>()->SetAnimation("hit"); // zumbi sofre dano
        }
    }*/
}
void Zombie::Render (){}

void Zombie::NotifyCollision(GameObject& associated) {
    if (associated.GetComponent<Bullet>()) {
        if (!dead) {
            Damage(20);
            heatSound.Play(1);
            if (hitpoints > 0) {
                hit = true;
                hitTimer.Restart();
                Vec2 target = Character::player->GetAssociated().box.getCentro();
                Vec2 origem = associated.box.getCentro();

                Vec2 delta = target.sub(origem);
                Vec2 direcao = delta.normal();

                if (direcao.x >= 0) {
                    this->associated.GetComponent<Animator>()->SetAnimation("hit"); // zumbi sofre dano
                } else {
                    this->associated.GetComponent<Animator>()->SetAnimation("hitleft"); // zumbi sofre dano
                }
            }
        }
    }
}
