#include "Rect.h"
#include <cmath>

Rect::Rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::soma(const Vec2& v) const {
    return Rect(x + v.x, y + v.y, w, h);
}

Rect Rect::sub(const Vec2& v) const {
    return Rect(x - v.x, y - v.y, w, h);
}

Vec2 Rect::getCentro() const {
    return Vec2(x + w / 2, y + h / 2);
}

float Rect::distCentro(const Rect& outro) const {
    Vec2 centroA = getCentro();
    Vec2 centroB = outro.getCentro();
    return centroA.distancia(centroB);
}

bool Rect::contemPonto(const Vec2& ponto) const {
    return (ponto.x >= x && ponto.x <= x + w &&
            ponto.y >= y && ponto.y <= y + h);
}
