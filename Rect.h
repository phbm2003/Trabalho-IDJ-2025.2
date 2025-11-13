#ifndef RECT_H
#define RECT_H
#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    Rect soma(const Vec2& v) const;
    Rect sub(const Vec2& v) const;
    Vec2 getCentro() const;
    float distCentro(const Rect& outro) const;
    bool contemPonto(const Vec2& ponto) const;
};
#endif // RECT_H
