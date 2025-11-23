#include "Bullet.h"
#include "Animator.h"
#include "Character.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include <cmath>
#include <iostream>

Bullet::Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance,  std::weak_ptr<GameObject> shooter) : Component(associated) {
    if (shooter.lock()->GetComponent<Character>()->player == shooter.lock()->GetComponent<Character>()) { // quem atirou foi o player
        targetsPlayer = false;
    } else {
        targetsPlayer = true;
    }

    SpriteRenderer* bulletS = new SpriteRenderer(associated, "bin/recursos/img/Bullet.png");
    associated.AddComponent(bulletS);

    bulletS->SetScale(1.3, 1.3);

    Animator* bulletA = new Animator(associated);
    associated.AddComponent(bulletA);  // adiciona componente à entidade

    Collider* bulletC = new Collider(associated);
    associated.AddComponent(bulletC);  // adiciona componente à entidade

    bulletA->AddAnimation("idle", Animation(0, 0, 0.2f)); // animação de parado

    bulletA->SetAnimation("idle"); // gun anda

    this->damage = damage;

    Vec2 direction = Vec2(std::cos(angle), std::sin(angle));
    this->speed = direction.mult(speed);

    distanceLeft = maxDistance;

    // Define o ângulo para renderizar corretamente
    associated.angleDeg = angle * 180.0f / M_PI;
}

void Bullet::Update(float dt) {

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    distanceLeft -= std::sqrt(speed.x * speed.x + speed.y * speed.y) * dt;

    if (distanceLeft <= 0) {
        //Vec2 speed = {0, 0};
        associated.RequestDelete();
        return;
    }
}

void Bullet::Render (){}
int Bullet::GetDamage (){
    return damage;
}

void Bullet::NotifyCollision(GameObject& associated) {
    auto ch = associated.GetComponent<Character>();
    auto zb = associated.GetComponent<Zombie>();

    // só colide com zumbi ou personagem
    if (!ch && !zb) return;

    if (zb) {
        this->associated.RequestDelete();
        return;
    }

    if (ch) {
        if ((ch->player == ch && targetsPlayer)  ||
            (ch->player != ch && !targetsPlayer)) {

            this->associated.RequestDelete();
        }
    }
}
