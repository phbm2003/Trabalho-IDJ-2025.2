#include "InputManager.h"

void InputManager::Update (){
    SDL_Event evento;

    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseX = x;
    mouseY = y;

    quitRequested = false;

    ++updateCounter;

    while (SDL_PollEvent(&evento)) {
        if ((evento.type == SDL_KEYDOWN) && !evento.key.repeat) {
                int chave = evento.key.keysym.sym;
                keyState[chave] = true;
                keyUpdate[chave] = updateCounter;

        } else if (evento.type == SDL_KEYUP) {
            int chave = evento.key.keysym.sym;
            keyState[chave] = false;
            keyUpdate[chave] = updateCounter;

        } else if (evento.type == SDL_MOUSEBUTTONDOWN) {
            int botao = evento.button.button;
            mouseState[botao] = true;
            mouseUpdate[botao] = updateCounter;

        } else if (evento.type == SDL_MOUSEBUTTONUP) {
            int botao = evento.button.button;
            mouseState[botao] = false;
            mouseUpdate[botao] = updateCounter;

        } else if (evento.type == SDL_QUIT) {
            quitRequested = true;
        }
    }

}

bool InputManager::KeyPress (int key){
    if ((keyState[key] == true) && keyUpdate[key] == updateCounter) {
        return true;
    } else {
        return false;
    }
}

bool InputManager::KeyRelease (int key){
    if ((keyState[key] == false) && keyUpdate[key] == updateCounter) {
        return true;
    } else {
        return false;
    }
}
bool InputManager::IsKeyDown (int key){
    if (keyState[key] == true) {
        return true;
    } else {
        return false;
    }
}

bool InputManager::MousePress (int button){
    if ((mouseState[button] == true) && (mouseUpdate[button] == updateCounter)) {
        return true;
    } else {
        return false;
    }
}

bool InputManager::MouseRelease (int button){
    if ((mouseState[button] == false) && (mouseUpdate[button] == updateCounter)) {
        return true;
    } else {
        return false;
    }
}

bool InputManager::IsMouseDown (int button){
    if (mouseState[button] == true) {
        return true;
    } else {
        return false;
    }
}

int InputManager::GetMouseX (){
    return mouseX;
}

int InputManager::GetMouseY (){
    return mouseY;
}

bool InputManager::QuitRequested (){
    return quitRequested;
}

InputManager& InputManager::GetInstance (){
    static InputManager instance;
    return instance;
}

InputManager::InputManager (){
    // inicializa variáveis
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager (){}
