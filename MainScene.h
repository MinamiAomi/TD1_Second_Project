#pragma once
#include "Scene.h"
class MainScene :
    public Scene {

private:


public:
    MainScene(class Game* game) : Scene(game) {}
    ~MainScene() {}

    void Create();
    void Init();
    void Update();
    void Draw();
    void NextScene();
};

