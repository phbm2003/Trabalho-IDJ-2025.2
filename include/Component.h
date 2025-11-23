#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject; // forward declaration

class Component {
public:
    Component (GameObject& associated);
    virtual ~Component ();
    virtual void Update (float dt) = 0; // virtual pura, função que é obrigatoriamente implementada por classes derivadas
    virtual void Render () = 0;
    virtual void Start();

    virtual void NotifyCollision (GameObject& other);
protected:
    GameObject& associated;
};

#endif // COMPONENT_H
