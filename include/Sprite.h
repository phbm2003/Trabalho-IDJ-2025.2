#ifndef SPRITE_H
#define SPRITE_H

#include "Vec2.h"
#include <string>
#define SDL_MAIN_HANDLED
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"


class Sprite {
public:
    Sprite ();
    Sprite (std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite ();
    void Open (std::string file);
    void SetClip (int x, int y, int w, int h);
    void Render (int x, int y, int w, int h, float angle = 0);
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();

    //Versão 2.0

    void SetFrame (int frame);
    void SetFrameCount (int frameCountW, int frameCountH);
    void SetCameraFollower(bool follower);

    void SetScale (float scaleX, float scaleY);
    Vec2 GetScale ();
    void SetFlip(SDL_RendererFlip flip);

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

    SDL_RendererFlip flip;
    Vec2 scale;

    int frameCountW;
    int frameCountH;

    bool cameraFollower;
};

#endif // SPRITE_H
