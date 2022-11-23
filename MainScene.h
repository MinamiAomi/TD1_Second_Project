#pragma once
#include "Scene.h"
#include "Lerp.h"
#include "ImageData.h"
class MainScene :
    public Scene {

public:
    struct Data
    {
        int clearHandle;
        int playerHpBarHandle;
    };

private:
    bool playerDeth;
    bool gameClear;
    Lerp<float> lerp;
    float switchTime;

public:
    MainScene(class Game* game) : Scene(game) {}
    ~MainScene() {}

    void Create();
    void Init();
    void Update();
    void Draw();
    void NextScene();
};

