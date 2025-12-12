#include "WaveSpawner.h"
#include "AIController.h"
#include "EndState.h"
#include "Zombie.h"
#include "Camera.h"
#include "Game.h"
#include "Character.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include "GameData.h"

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
    Wave wave1(1, 5, 2);
    Wave wave2(2, 10, 2);
    Wave wave3(6, 15, 2);

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

    if (currentWave >= waves.size()) {
        associated.RequestDelete();
        GameData::playerVictory = true;
        Game::GetInstance().GetCurrentState().popRequested = true;
        // Não force a transição aqui. Deixe o StageState fazer isso.
        //Game::GetInstance().GetCurrentState().popRequested = true;
        return;
    }

    // 2. CHECAGEM DE DERROTA (Morte do Player)
    if (Character::player == nullptr || Character::player->dead) {
        // Se o player morreu, marque a derrota e solicite o pop.
        //if (Game::GetInstance().GetCurrentState().popRequested == false) {
            GameData::playerDefeat = true; // <-- MARCA A DERROTA
            Game::GetInstance().GetCurrentState().popRequested = true;
            //Game::GetInstance().GetCurrentState().popRequested = true;
        //}
        return;
    }

    // Se o player morreu, não continua
    //if (Character::playerDied) {
    //    return;
    //}

    zombieCooldownTimer.Update(dt);
    charCooldownTimer.Update(dt);

    Wave& w = waves[currentWave];

    std::cout << "Wave: " << currentWave << " / " << waves.size()
              << " | Zombies Spawned/Total: " << zombieCounter << "/" << w.zombies
              << " | Chars Spawned/Total: " << charCounter << "/" << w.characters
              << " | Zombs Alive: " << Zombie::contador
              << " | Chars Alive: " << Character::contador << std::endl;

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

            Game::GetInstance().GetCurrentState().AddObject(zombiego);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state

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

            Game::GetInstance().GetCurrentState().AddObject(ch);    // adiciona entidade ao vetor de ponteiros únicos de entidade em state

            charCounter++;
            charCooldownTimer.Restart();
        }

    } else {
        std::cout << "--- WAITING FOR ALL ENEMIES TO DIE ---" << std::endl;
        if ((Zombie::contador == 0) && (Character::contador == 0)) {
            std::cout << "--- ADVANCING TO NEXT WAVE ---" << std::endl;
            currentWave++;


            zombieCounter = 0;
            zombieCooldownTimer.Restart();

            charCounter = 0;
            charCooldownTimer.Restart();

            //currentWave++;
        }
    }
}
void WaveSpawner::Render () {}
