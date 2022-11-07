#pragma once
#include "GameObject.h"
class Effect :
    public GameObject {


public:
    Effect(class Game* game) : GameObject(game) {}
    virtual ~Effect() {}

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

