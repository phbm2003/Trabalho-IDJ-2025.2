#include "PlayerController.h"
#include "Character.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include <iostream>
#include "Camera.h"
#include "Game.h"


PlayerController::PlayerController (GameObject& associated) : Component(associated) {}

void PlayerController::Start() {}

void PlayerController::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    Character* character = associated.GetComponent<Character>();
    if (!character) return;

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        float mouseX = input.GetMouseX() + Camera::pos.x;
        float mouseY = input.GetMouseY() + Camera::pos.y;
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::SHOOT, mouseX, mouseY));
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s')) && (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d'))){
        //associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, -0.5f)); // valores indicam direção
        return; // todos os movimentos se anulam
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.5f, 0.0f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d')) && (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, -0.5f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, -0.5f, -0.0f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d')) && (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, 0.5f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s'))){
        //associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, -0.5f)); // valores indicam direção
        return; // todos os movimentos se anulam
    }

    if ((input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d'))){
        //associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, -0.5f)); // valores indicam direção
        return; // todos os movimentos se anulam
    }

    if ((input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, -0.5f, -0.5f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) && (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, -0.5f, 0.5f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.5f, 0.5f)); // valores indicam direção
        return;
    }

    if ((input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) && (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d'))){
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.5f, -0.5f)); // valores indicam direção
        return;
    }

    if (input.IsKeyDown(SDLK_UP) || input.IsKeyDown('w')) {
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, -0.5f)); // valores indicam direção
    }
    if (input.IsKeyDown(SDLK_DOWN) || input.IsKeyDown('s')) {
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.0f, 0.5f));
    }
    if (input.IsKeyDown(SDLK_LEFT) || input.IsKeyDown('a')) {
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, -0.5f, 0.0f));
    }
    if (input.IsKeyDown(SDLK_RIGHT) || input.IsKeyDown('d')) {
        associated.GetComponent<Character>()->Issue(Character::Command (Character::Command::MOVE, 0.5f, 0.0f));
    }



}
void PlayerController::Render () {}
