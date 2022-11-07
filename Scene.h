#pragma once
#include "GameObject.h"
class Scene :
    public GameObject {

private:


public:
    Scene(class Game* game) : GameObject(game) {}
    virtual ~Scene() {}

    void Proc() {
        this->Update();
        this->Draw();
        this->NextScene();
    }

    virtual void Create() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void NextScene() = 0;
};

