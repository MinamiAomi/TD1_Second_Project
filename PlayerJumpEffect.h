#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Array.h"
#include "Shape.h"
class PlayerJumpEffect :
    public GameObject
{

public:
    struct InitData
    {
        Quad imageQuad;
        int particleNum;
        float exitTime;
        float pariticleSpeed;
    };

private:
    struct Particle
    {
        Vec2 pos;
        Vec2 vel;
    };

    bool mIsAlive = false;
    float mLeftTime = 0.0f;
    Vec2 mEmitterPos;
    DynamicArray<Particle> mParticles;

public:
    PlayerJumpEffect(class Game* game);
    ~PlayerJumpEffect();

    bool getIsAlive() const { return mIsAlive; }

    void Create();
    void Spawn(const Vec2& spawnPos);
    void Update();
    void Draw();
};

