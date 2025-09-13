#include "State.h"


State::State() {
    quitRequested = false;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    bg.Open("bin/recursos/img/Background.png");
    music.Open("bin/recursos/audio/BGM.wav");
    music.Play(-1);
}

void State::Update(float dt) {
    if (SDL_QuitRequested() == true) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}



