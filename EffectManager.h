#pragma once
#include "GameObject.h"


class EffectManager :
    public GameObject {

public:
    enum EffectType {
        kNormalEffect,

        kEffectTypeNum
    };

private:
    class Effect* mEffects[kEffectTypeNum];
    class NormalEffect* mNormalEffectPtr;

public:
    class Effect* getEffect(EffectType type) { return mEffects[type]; }
    class NormalEffect* getNormalEffect() { return mNormalEffectPtr; }


public:
    EffectManager(class Game* game);
    ~EffectManager();

    void Create();
    void Update();
};

