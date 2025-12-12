#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "StageState.h"
#include "Text.h"

TitleState::TitleState (){
    // imagem de fundo
    GameObject* title = new GameObject();
    SpriteRenderer* titleS = new SpriteRenderer(*title, "bin/recursos/img/Title.png", 1, 1);
    titleS->SetcameraFollower(true);
    title->AddComponent(titleS);
    title->box.x = 0;
    title->box.y = 0;
    AddObject(title);

   // texto
    GameObject* textObj = new GameObject();
    Text* text = new Text(*textObj, "bin/recursos/font/neodgm.ttf", 70,  Text::BLENDED, "Press Space To Start", SDL_Color{255, 255, 255, 255} );
    text->SetCameraFollower(true);
    textObj->AddComponent(text);
    int windowW, windowH;
    SDL_Renderer* rend = Game::GetInstance().GetRenderer();
    SDL_GetRendererOutputSize(rend, &windowW, &windowH);

    textObj->box.x = (windowW - textObj->box.w) / 2;
    textObj->box.y = (windowH - textObj->box.h) / 2 + 250;


    AddObject(textObj);
}

TitleState::~TitleState () {}
void TitleState::LoadAssets () {}
void TitleState::Update (float dt) {
    UpdateArray(dt);

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY)) { // barra de espaço pressionada
        StageState* state = new StageState();
        Game::GetInstance().Push(state);
    }
}
void TitleState::Render () {
    RenderArray();
}
void TitleState::Start () {
    LoadAssets();
    StartArray();
    started = true;
}
void TitleState::Pause () {}
void TitleState::Resume () {}
