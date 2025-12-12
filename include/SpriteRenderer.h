#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"
#include <iostream>
#include <ostream>
#include <string>

class SpriteRenderer : public Component {
public:

    SpriteRenderer (GameObject& associated);
    SpriteRenderer (GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    void Open (std::string file);
    void SetFrameCount (int frameCountW, int frameCountH);
    void Update (float dt);
    void Render ();
    void SetFrame(int frame, SDL_RendererFlip flip);
    void SetcameraFollower(bool cond);

    void SetScale (float scaleX, float scaleY);

    ~SpriteRenderer() {
        //std::cout << "803" << std::endl;
    }

private:
    Sprite sprite;
};

#endif // SPRITERENDERER_H
