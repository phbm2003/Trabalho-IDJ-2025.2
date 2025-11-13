#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie (GameObject& associated) : Component (associated), deathSound("bin/recursos/audio/Dead.wav"), heatSound("bin/recursos/audio/Hit0.wav"){
    dead = false;
    hit = false;
    hitpoints = 100;
    SpriteRenderer* zombieS = new SpriteRenderer(associated, "bin/recursos/img/Enemy.png", 3, 2); // novo componente de zombie
    //zombieS->SetFrame(1);
    associated.AddComponent(zombieS);  // // adiciona componente à entidade

    Animator* zombieA = new Animator(associated);
    associated.AddComponent(zombieA);  // // adiciona componente à entidade
    zombieA->AddAnimation("walking", Animation(0, 3, 0.1f));
    zombieA->AddAnimation("dead", Animation(5, 5, 0.5f));
    zombieA->AddAnimation("hit", Animation(4,4, 0.2f)); // animação de hit

    zombieA->SetAnimation("walking"); // zumbi anda

}
void Zombie::Damage (int damage){
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        SpriteRenderer* zombieS = associated.GetComponent<SpriteRenderer>();

        if (zombieS != nullptr) { // verifica se zombieS já foi adicionado
            associated.GetComponent<Animator>()->SetAnimation("dead"); // chama método setanimation do componente do tipo Animator presente no GameObject passado
            deathSound.Play(1);
            deathTimer.Restart();
            dead = true;
        }
    }
}
void Zombie::Update (float dt){
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    if (hitpoints > 0 && hit == true && hitTimer.Get() >= 0.5) {
        associated.GetComponent<Animator>()->SetAnimation("walking");
        hit = false;
    }

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
    }

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
    }
}
void Zombie::Render (){}
