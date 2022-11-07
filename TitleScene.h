#pragma once
#include "Scene.h"
#include "MyMath.h"
class TitleScene :
    public Scene {

public:
 

private:


public:
    TitleScene(class Game* game) : Scene(game) {}
    ~TitleScene() {}

    void Create();
    void Init();
    void Update();
    void Draw();
    void NextScene();
};

