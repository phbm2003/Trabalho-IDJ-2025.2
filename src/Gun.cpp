#include "Gun.h"
#include "Animator.h"
#include "Bullet.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include <cmath>
#include <iostream>
#include "InputManager.h"
#include "Camera.h"


Gun::Gun (GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated){
    this->character = character;
    cooldownState = 0;
    angle = 0;

    SpriteRenderer* gunS = new SpriteRenderer(associated, "bin/recursos/img/Gun.png", 3, 2); // novo componente de gun
    associated.AddComponent(gunS);  // adiciona componente à entidade

    Animator* gunA = new Animator(associated);
    associated.AddComponent(gunA);  // adiciona componente à entidade
    gunA->AddAnimation("idle", Animation(0, 0, 0.2f, SDL_FLIP_NONE)); // animação de parado
    gunA->AddAnimation("reloading", Animation(1, 5, 0.1f, SDL_FLIP_NONE));
    gunA->AddAnimation("idle2", Animation(0, 0, 0.2f, SDL_FLIP_VERTICAL)); // animação de parado
    gunA->AddAnimation("reloading2", Animation(1, 5, 0.1f, SDL_FLIP_VERTICAL));

    gunA->SetAnimation("idle"); // gun anda

    shotSound = Sound("bin/recursos/audio/Range.wav");
    reloadSound = Sound("bin/recursos/audio/PumpAction.mp3");
}

void Gun::Update(float dt) {
    // Verificar se o Character existe
    std::shared_ptr<GameObject> characterPtr = character.lock();

    // Pega o centro do personagem
    Vec2 gunCenter = characterPtr->box.getCentro();

    float angleRad = angle * M_PI / 180.0f;

    // Distância do personagem até a arma (pode ajustar pra mais longe/perto)
    float distancia = 100;

    // Cria um vetor deslocado na direção do ângulo atual
    Vec2 offset = Vec2(distancia, 0).rotaciona(angleRad);

    // Aplica a posição
    associated.box.x = gunCenter.x - associated.box.w / 2 + offset.x;
    associated.box.y = gunCenter.y - associated.box.h / 2 + offset.y;

    // Atualiza rotação visual
    associated.angleDeg = angle;  // SDL usa rotação invertida
    std::cout << "associated.angleDeg: " << associated.angleDeg << "\n" << std::endl;
    cdTimer.Update(dt);

    Animator* animator = associated.GetComponent<Animator>();
    if (!animator) return;

    switch (cooldownState) {
    case 0: // pronta para atirar
        if (angle > 90 || angle < -90) {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle2");
        } else {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle");
        }
        break;

    case 1: // pós-tiro
        if (cdTimer.Get() > 0.2f) { // tempo de espera antes de recarregar
            cooldownState = 2;
            cdTimer.Restart();

            reloadSound.Play();
        }
        if (angle > 90 || angle < -90) {
            //associated.angleDeg += 180;
            animator->SetAnimation("reloading2");

        } else {
            //associated.angleDeg += 180;
            animator->SetAnimation("reloading");
        }
        break;

    case 2: // recarregando
        if (cdTimer.Get() > 0.5f) { // tempo de recarga
            cooldownState = 3;
            cdTimer.Restart();

        }
        if (angle > 90 || angle < -90) {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle2");
        } else {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle");
        }
        break;

    case 3: // recarregada, espera um pouco antes de ficar pronta
        if (cdTimer.Get() > 0.1f) {
            cooldownState = 0;
            cdTimer.Restart();

        }
        if (angle > 90 || angle < -90) {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle2");
        } else {
            //associated.angleDeg += 180;
            animator->SetAnimation("idle");
        }
        break;
    }
}

void Gun::Render (){
}
void Gun::Shoot(Vec2 target) {

    if (cooldownState == 0) {
        Vec2 barrelOffsetLocal = Vec2(90, -5);

        Vec2 origem = associated.box.getCentro();
        Vec2 direcao = target.sub(origem);
        float angle2 = direcao.fase();

        float velocidade = 800.0f;
        int dano = 10;
        float dist = 1000.0f;



        //Vec2 cano = associated.box.getCentro().soma(Vec2(0, 0).rotaciona(angle2));
        //bl->box.x = cano.x;
        //bl->box.y = cano.y;
        //bl->box.h = 36;
        //bl->box.w = 20;


        // Verificar se o Character existe
        std::shared_ptr<GameObject> characterPtr = character.lock();

        // Pega a posição do mouse no mundo
        Vec2 mousePos = Vec2{static_cast<float>(InputManager::GetInstance().GetMouseX()), static_cast<float>(InputManager::GetInstance().GetMouseY())}.soma(Camera::pos);

        // Pega o centro do personagem
        Vec2 gunCenter = characterPtr->box.getCentro();

        // Calcula o vetor diferença e o ângulo
        Vec2 diff = mousePos.sub(gunCenter);
        angle2 = atan2(diff.y, diff.x); // <-- define o ângulo da mira

        // Atualiza a rotação visual
        //associated.angleDeg = angle2 * 180 / M_PI; // SDL gira no sentido horário

        // Posiciona a arma com um deslocamento (ajuste se necessário)
        Vec2 offset = Vec2(30, 0).rotaciona(angle2);

        angle = angle2 * 180 / M_PI;
        GameObject* bl = new GameObject();

        Bullet* bullet = new Bullet(*bl, angle2, velocidade, dano, dist);
        bl->AddComponent(bullet);

        //Posicionar o centro da arma no centro do corpo
        Rect aux;
        aux.x = gunCenter.x  + offset.x;
        aux.y = gunCenter.y  + offset.y;

        Vec2 barrelWorldPos = aux.getCentro().soma(
            barrelOffsetLocal.rotaciona(angle2)
            );

        bl->box.x = barrelWorldPos.x - bl->box.w / 2;
        bl->box.y = barrelWorldPos.y - bl->box.h / 2;
        if ((angle > 90 || angle < -90)){
            //associated.GetComponent<SpriteRenderer>()->SetFrame(0, SDL_FLIP_NONE);
            //associated.angleDeg += 180;
        } else {
            //associated.GetComponent<SpriteRenderer>()->SetFrame(0, SDL_FLIP_NONE);
        }

        bl->angleDeg = angle + 90; // atualiza ângulo da arma e da bala
        //associated.box.x = cano.x;
        //associated.box.y = cano.y;

        //associated.angleDeg = angle;

        Game::GetInstance().GetState().AddObject(bl);

        shotSound.Play();
        cooldownState = 1;
        cdTimer.Restart();
    } else {
        std::cout << "cooldown ativo\n";
    }
}

