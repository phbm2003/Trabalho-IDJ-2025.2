#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <ostream>
#include "Resources.h"

Text::Text (GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component (associated){
    this->texture = nullptr;
    this->color = color;
    this->text = text;
    this->style = style;
    this->fontSize = fontSize;
    this->fontFile = fontFile;
    visible = true;
    RemakeTexture();
}

Text::~Text () {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Text::Start() {
    // Agora que o State foi iniciado (Game/renderer/TTF já existem),
    // podemos criar a textura com segurança.
    RemakeTexture();
}

void Text::Update (float dt) {
    blinkTimer.Update(dt);
    if (blinkTimer.Get() > 0.2f) {
        visible = !visible;
        blinkTimer.Restart();
    }
}

void Text::Render () {
    if (!visible) {
        return;
    }

    if (texture == nullptr) {
        RemakeTexture();
        if (texture == nullptr) return; // não dá pra renderizar
    }

    SDL_Rect clip;

    SDL_QueryTexture(texture, nullptr, nullptr, &clip.w, &clip.h);
    clip.x = 0;
    clip.y = 0;

    SDL_Rect dst;

    if (cameraFollower) {
        dst.x = associated.box.x;
        dst.y = associated.box.y;
    } else {
        dst.x = associated.box.x - Camera::pos.x;
        dst.y = associated.box.y - Camera::pos.y;
    }

    dst.w = clip.w;
    dst.h = clip.h;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clip, &dst, 0, nullptr, SDL_FLIP_NONE);
}

void Text::SetText (std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor (SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle (TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile (std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize (int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture () {
    // 1. Se já existir textura, destrua
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // 2. Obtenha a fonte
    font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr) {
        std::cout << "Erro: fonte não carregada: " << fontFile << std::endl;
        return;
    }

    // 3. Criar surface de acordo com o estilo
    SDL_Surface* surface = nullptr;

    switch (style) {
    case Text::SOLID:
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
        break;

    case Text::SHADED: {
        SDL_Color bg = {0, 0, 0, 255}; // fundo preto
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg);
        break;
    }

    case Text::BLENDED:
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
        break;
    }

    if (!surface) {
        std::cout << "Erro ao criar surface do texto: " << SDL_GetError() << std::endl;
        return;
    }

    // 4. Converter surface → texture
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

    if (!texture) {
        std::cout << "Erro ao criar textura do texto: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // 5. Ajustar tamanho do box ao tamanho do texto
    associated.box.w = surface->w;
    associated.box.h = surface->h;

    // 6. Surface não é mais necessária
    SDL_FreeSurface(surface);
}
