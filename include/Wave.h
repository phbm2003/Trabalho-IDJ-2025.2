#ifndef WAVE_H
#define WAVE_H

class Wave {
public:
    Wave(int characters, int zombies, float cooldown);
    int zombies;
    float cooldown;
    int characters;
};

#endif // WAVE_H
