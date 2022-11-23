#pragma once
#include "Scene.h"
#include "MyMath.h"
#include "ImageData.h"
class TitleScene :
    public Scene {

public:
    struct Data
    {
        ImageData backImage;
        ImageData logoImage;
        ImageData logoYImage;

    };

private:
    bool mIsGameStart = false;
    bool mIsFead = false;

public:
    TitleScene(class Game* game) : Scene(game) {}
    ~TitleScene() {}

    void Create();
    void Init();
    void Update();
    void Draw();
    void NextScene();
};

