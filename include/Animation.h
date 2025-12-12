#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL2/SDL_render.h"
#include <iostream>
class Animation {
public:
    //Animation () : frameStart(0), frameEnd(0), frameTime(0.0f) {}
    Animation (int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int frameStart;
    int frameEnd;
    float frameTime;

    SDL_RendererFlip flip;

    ~Animation() {
        //std::cout << "804" << std::endl;
    }
};

#endif // ANIMATION_H
