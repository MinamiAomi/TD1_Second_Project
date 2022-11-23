#pragma once
#include "Scene.h"
#include "MyMath.h"
#include "ImageData.h"
class OptionScene :
    public Scene
{
public:

    int handle;
public:
    OptionScene(class Game* game) : Scene(game) {}
    ~OptionScene() {}

    void Create();
    void Init();
    void Update();
    void Draw();
    void NextScene();
};

