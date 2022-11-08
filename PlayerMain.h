#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"

class Player :
    public GameObject
{

public:

    enum State {
        kStateWait, // 待機
        kStateRun, // 走る
        kStateJump, // ジャンプ
        kStateDoubleJump, // 二段ジャンプ
        kStateFall, // 落下
        kStateAlongWall, // 壁ずり
        kStateDushAttak, // ダッシュ攻撃

        kStateNum
    };

    struct InitData {
        ImageData image;

        Vec2 position;
        Vec2 size;
        Vec2 mapColliderSize;
    };

private:
    Vec2 mPosition;
    Vec2 mVelocity;
    Vec2 mAcceleration;
    Vec2 mSize;

    Rect mImageRect;
    Rect mMapColliderRect;

    State mCurrentState;
    class PlayerStateBase* mStates[kStateNum];

    int mMoveInput;
    bool mJumpInput;
    bool mDushAttakInput;

public:
    Player(class Game* game);
    ~Player();

    void Create();
    void Update();
    void Draw();

    const Vec2& getPosition() const { return mPosition; }
    void setPosition(const Vec2& pos) { mPosition = pos; }

    const Vec2& getVelocity() const { return mVelocity; }
    void setVelocity(const Vec2& vel) { mVelocity = vel; }

    const Vec2& getAcceleration() const { return mAcceleration; }
    void setAcceleration(const Vec2& acc) { mAcceleration = acc; }

    const Rect& mapColliderRect() const { return mMapColliderRect; }


private:
    void Input();
    void ApplyForce();
};


