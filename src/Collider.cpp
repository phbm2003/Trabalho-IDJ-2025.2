#include "Collider.h"
#include "Camera.h"
#include "Game.h"
#include "SDL2/SDL_rect.h"

Collider::Collider (GameObject& associated, Vec2 scale, Vec2 offset) : Component (associated){
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update (float dt){
    box.h = associated.box.h * scale.y;
    box.w = associated.box.w * scale.x;

    Vec2 newCenter;
    newCenter.x = associated.box.getCentro().x + offset.rotaciona(associated.angleDeg).x;
    newCenter.y = associated.box.getCentro().y + offset.rotaciona(associated.angleDeg).y;

    box.x = newCenter.x - box.w/2;
    box.y = newCenter.y - box.h/2;
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center( box.getCentro() );
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y).sub(center)).rotaciona(associated.angleDeg/(180/M_PI)).soma(center).sub(Camera::pos);
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y).sub(center)).rotaciona(associated.angleDeg/(180/M_PI)).soma(center).sub(Camera::pos);
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h).sub(center)).rotaciona(associated.angleDeg/(180/M_PI)).soma(center).sub(Camera::pos);
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h).sub(center)).rotaciona(associated.angleDeg/(180/M_PI)).soma(center).sub(Camera::pos);
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);

#endif // DEBUG
}

void Collider::SetScale (Vec2 scale){
    if (!scale.x || !scale.y){
        return;
    } else {
        this->scale =  scale;
    }
}

void Collider::SetOffset (Vec2 offset){
    this->offset = offset;
}
