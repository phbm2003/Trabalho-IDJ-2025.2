#include "Wave.h"

Wave::Wave(int characters, int zombies, float cooldown){
    this->zombies = zombies;
    this->cooldown = cooldown;
    this->characters = characters;
}
