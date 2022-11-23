#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Array.h"
#include "Shape.h"

class PlayerDushAttackEffect :
    public GameObject
{


public:
    struct InitData
    {
        Quad imageQuad;
        int particleNum;
    };

private:
    struct Particle
    {
        bool mIsAlive = false;
        Vec2 pos;
    };

    Vec2 prePos;
    float mLeftTime = 0.0f;
    DynamicArray<Particle> mParticles;


public:
    PlayerDushAttackEffect(class Game* game);
    ~PlayerDushAttackEffect();

    void Create();
    void Spawn(const Vec2& spawnPos);
    void Update();
    void Draw();

};

