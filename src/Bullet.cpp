#include "Bullet.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include <cmath>
#include <iostream>

Bullet::Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance) : Component(associated) {
    SpriteRenderer* bulletS = new SpriteRenderer(associated, "bin/recursos/img/Bullet.png");
    associated.AddComponent(bulletS);

    bulletS->SetScale(1.3, 1.3);

    Animator* bulletA = new Animator(associated);
    associated.AddComponent(bulletA);  // adiciona componente à entidade
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
    std::cout << "Bullet Update start\n";

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    distanceLeft -= std::sqrt(speed.x * speed.x + speed.y * speed.y) * dt;
    std::cout << "distanceLeft=" << distanceLeft << "\n";

    if (distanceLeft <= 0) {
        //Vec2 speed = {0, 0};
        std::cout << "Bullet delete request\n";
        associated.RequestDelete();
        std::cout << "Concluído?\n";
        return;
    }

    std::cout << "Bullet Update end\n";
}

void Bullet::Render (){}
int Bullet::GetDamage (){
    return damage;
}

