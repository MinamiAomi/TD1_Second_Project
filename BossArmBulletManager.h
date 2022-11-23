#pragma once
#include "GameObject.h"
#include "BossArmBullet.h"
#include <vector>
class BossArmBulletManager :
    public GameObject
{
private:

    bool mIsFire = false;
    float mCoolTime = 0.0f;

    std::vector<BossArmBullet> mBullets;

public:
    BossArmBulletManager(class Game* game);
    ~BossArmBulletManager();


    void Create();
    void Init();
    void Update(const Vec2& pos);
    void Draw();

    void SetFire(bool i) { mIsFire = i; }
    bool IsFire() const { return mIsFire; }
    std::vector<Rect> BulletRect() const;
    std::vector<BossArmBullet> Bullets() const;
};

