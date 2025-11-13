#include "Vec2.h"
#include <cmath>

    Vec2::Vec2() {  // seta 0 pro vetor
        x = 0;
        y = 0;
    }

    Vec2::Vec2(float x, float y) {  // seta valores pro vetor
        this->x = x;
        this->y = y;
    }

    Vec2 Vec2::soma(const Vec2& vetor) const {  // soma vetores sem alterar estado do objeto
        return Vec2(this->x + vetor.x, this->y + vetor.y);  // cria novo objeto Vec2 e seta valores

    }
    Vec2 Vec2::sub(const Vec2& vetor) const {
        return Vec2(this->x - vetor.x, this->y - vetor.y);
    }
    Vec2 Vec2::mult(float escalar) const {
        return Vec2(this->x * escalar, this->y * escalar);
    }
    float Vec2::mag() const {
        return std::sqrt(x*x + y*y);
    }
    Vec2 Vec2::normal() const {
        return Vec2(this->x / mag(), this->y / mag());
    }
    float Vec2::distancia(const Vec2& vetor) const {
        return sub(vetor).mag();   // subtrai, retorna novo vetor e pega mag dele
    }
    float Vec2::fase() const {
        return atan2(y, x);        // não dá erro em divisão por zero, mostra quadrante certo
    }
    float Vec2::inclinacao(const Vec2& vetor) const {
        return vetor.sub(*this).fase();   // gera vetor que vai objeto atual até o ponto vetor
    }
    Vec2 Vec2::rotaciona(float angulo) const {
        return Vec2(x * cos(angulo) - y * sin(angulo), x * sin(angulo) + y * cos(angulo));
    }
