#include "WaveSpawner.h"
#include "AIController.h"
#include "Zombie.h"
#include "Camera.h"
#include "Game.h"
#include "Character.h"
#include <cmath>
#include <iostream>
#include <ostream>

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
    Wave wave1(1, 1, 2);
    Wave wave2(2, 4, 2);
    Wave wave3(2, 8, 2);

    waves.push_back(wave1);
    waves.push_back(wave2);
    waves.push_back(wave3);

    currentWave = 0;
    zombieCounter = 0;
    charCounter = 0;

    zombieCooldownTimer.Restart();
    charCooldownTimer.Restart();
}

void WaveSpawner::Update (float dt) {


    zombieCooldownTimer.Update(dt);
    charCooldownTimer.Update(dt);

    Wave& w = waves[currentWave];


    if (zombieCounter < w.zombies) {
        if (zombieCooldownTimer.Get() > waves[currentWave].cooldown) {
            float angle = (rand() % 360) * (M_PI / 180.0f);

            float dist = 1000.0f; // distância suficiente para estar fora da tela

            float cx = Camera::pos.x + 600;
            float cy = Camera::pos.y + 450;

            float x = cos(angle) * dist;
            float y = sin(angle) * dist;

            GameObject* zombiego = new GameObject(); // nova entidade zombie

            Zombie* zombie = new Zombie(*zombiego);  // novo componente de zombie
            zombiego->AddComponent(zombie);          // adiciona componente à entidade

            zombiego->box.x = cx + x;
            zombiego->box.y = cy + y;

            Game::GetInstance().GetState().AddObject(zombiego);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state

            zombieCounter++;
            zombieCooldownTimer.Restart();
        }
    } else if (charCounter < w.characters) {
        if (charCooldownTimer.Get() > waves[currentWave].cooldown) {
            float angle = (rand() % 360) * (M_PI / 180.0f);

            float dist = 1000.0f; // distância suficiente para estar fora da tela

            float cx = Camera::pos.x + 600;
            float cy = Camera::pos.y + 450;

            float x = cos(angle) * dist;
            float y = sin(angle) * dist;

            GameObject* ch = new GameObject(); // nova entidade zombie

            Character* chr = new Character(*ch,  "bin/recursos/img/NPC.png");  // novo componente de character
            AIController* chAI = new AIController(*ch);

            ch->AddComponent(chr);          // adiciona componente à entidade
            ch->AddComponent(chAI);

            ch->box.x = cx + x;
            ch->box.y = cy + y;

            Game::GetInstance().GetState().AddObject(ch);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state

            charCounter++;
            charCooldownTimer.Restart();
        }

    } else {

        if ((Zombie::contador == 0) && (Character::contador == 0)) {
            if (currentWave >= waves.size()) {
                associated.RequestDelete();
                return;
            }

            zombieCounter = 0;
            zombieCooldownTimer.Restart();

            charCounter = 0;
            charCooldownTimer.Restart();

            currentWave++;
        }
    }
}
void WaveSpawner::Render () {}
