#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie (GameObject& associated) : Component (associated){
    hitpoints = 100;
    SpriteRenderer* zombieS = new SpriteRenderer(associated, "bin/recursos/img/Enemy.png", 3, 2); // novo componente de zombie
    //zombieS->SetFrame(1);
    associated.AddComponent(zombieS);  // // adiciona componente à entidade

    Animator* zombieA = new Animator(associated);
    associated.AddComponent(zombieA);  // // adiciona componente à entidade
    zombieA->AddAnimation("walking", Animation(0, 3, 10));
    zombieA->AddAnimation("dead", Animation(5, 5, 0));
    zombieA->SetAnimation("walking"); // zumbi anda
}
void Zombie::Damage (int damage){
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        SpriteRenderer* zombieS = associated.GetComponent<SpriteRenderer>();

        if (zombieS != nullptr) { // verifica se zombieS já foi adicionado
            associated.GetComponent<Animator>()->SetAnimation("dead"); // chama método setanimation do componente do tipo Animator presente no GameObject passado
        }
    }
}
void Zombie::Update (float dt){
    Damage(1);
}
void Zombie::Render (){}
