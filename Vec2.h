#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    Vec2 soma(const Vec2& vetor) const; // não altera o próprio objeto e nem a referência
    Vec2 sub(const Vec2& vetor) const;
    Vec2 mult(float escalar) const;
    float mag() const;
    Vec2 normal() const;
    float distancia(const Vec2& vetor) const;
    float fase() const;
    float inclinacao(const Vec2& vetor) const;
    Vec2 rotaciona(float angulo) const;
};
#endif // VEC2_H
