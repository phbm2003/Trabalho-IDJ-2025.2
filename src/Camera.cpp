#include "Camera.h"
#include "InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
}

void Camera::Update (float dt) {
    if (focus != nullptr) {
        // Centraliza o foco na tela (sem Center())
        float screenWidth = 1200;   // ou SDL_GetWindowSize()
        float screenHeight = 900;

        float centerX = focus->box.x + focus->box.w / 2.0f;
        float centerY = focus->box.y + focus->box.h / 2.0f;

        pos.x = centerX - screenWidth / 2.0f;
        pos.y = centerY - screenHeight / 2.0f;
    } else {
        // Movimento manual com teclado
        speed = Vec2(0, 0);
        auto& input = InputManager::GetInstance();

        if (input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) {
            speed.y = -300;
        }
        if (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s')) {
            speed.y = 300;
        }
        if (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) {
            speed.x = -300;
        }
        if (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d')) {
            speed.x = 300;
        }

        pos = pos.soma(speed.mult(dt));

    }
}

GameObject* Camera::GetFocus() {
    return focus;
}
