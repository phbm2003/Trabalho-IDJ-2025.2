#include "EndState.h"
#include "SpriteRenderer.h"
#include "Text.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameData.h"
#include "TitleState.h"

EndState::EndState() {
    Camera::Unfollow();

    GameObject* bg = new GameObject();

    if (GameData::playerVictory == true) {
        SpriteRenderer* s = new SpriteRenderer(*bg, "bin/recursos/img/Win.png", 1, 1);
        s->SetcameraFollower(true);
        bg->AddComponent(s);

        backgroundMusic.Open("bin/recursos/audio/endStateWin.ogg");
    } else if (GameData::playerVictory == false) {
        SpriteRenderer* s = new SpriteRenderer(*bg, "bin/recursos/img/Lose.png", 1, 1);
        s->SetcameraFollower(true);
        bg->AddComponent(s);

        backgroundMusic.Open("bin/recursos/audio/endStateLose.ogg");
    }

    AddObject(bg);

    GameObject* t = new GameObject();
    SDL_Color white = {255,255,255,255};
    Text* text = new Text(*t, "bin/recursos/font/neodgm.ttf", 50, Text::BLENDED, "Press SPACE to restart, Or Press ESC to quit", white);
    text->SetCameraFollower(true);
    t->AddComponent(text);
    int windowW, windowH;
    SDL_Renderer* rend = Game::GetInstance().GetRenderer();
    SDL_GetRendererOutputSize(rend, &windowW, &windowH);

    t->box.x = (windowW - t->box.w) / 2;
    t->box.y = (windowH - t->box.h) / 2 + 250;  // ajuste opcional para ficar mais em baixo

    AddObject(t);
}

EndState::~EndState() {}

void EndState::LoadAssets() {
    backgroundMusic.Play(-1);
}

void EndState::Update(float dt) {
    UpdateArray(dt);

    auto& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested())
        quitRequested = true;

    if (input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    LoadAssets();
    StartArray();
    started = true;
}

void EndState::Pause() {}
void EndState::Resume() {}
