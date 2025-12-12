#ifndef TEXT_H
#define TEXT_H
#include "GameObject.h"
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Timer.h"
#include <string>

class Text : public Component {
public:
    enum TextStyle {SOLID, SHADED, BLENDED};
    Text (GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text ();
    void Update (float dt) override;
    void Render () override;
    void Start() override;
    void SetText (std::string text);
    void SetColor (SDL_Color color);
    void SetStyle (TextStyle style);
    void SetFontFile (std::string fontFile);
    void SetFontSize (int fontSize);
    bool visible = true;
    std::string GetText() const { return text; }
    void SetCameraFollower(bool follow) { cameraFollower = follow; }
private:
    void RemakeTexture ();
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    Timer blinkTimer;
    bool cameraFollower = false;
};

#endif // TEXT_H
