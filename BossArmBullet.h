#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"
class BossArmBullet :
    public GameObject
{
private:
   
    bool mIsAlive = false;
    Vec2 mPosition;
    Vec2 mVelocity;
    float mAngle;

public:
    BossArmBullet(class Game* game);
    ~BossArmBullet();

    bool IsAlive() const { return mIsAlive; }

    void Create(const Vec2& pos, const Vec2& target);
    void Init();
    void Update();
    void Draw();

    Rect GetRect() const ;
    const Vec2& GetVel() const { return mVelocity; }
};

