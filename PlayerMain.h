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
        kStateGround, // 地面にいる
        kStateAir, // 空中にいる

        kStateNum
    };

    struct InitData {
        ImageData image;

        Vec2 position;
        Vec2 size;
        Vec2 mapColliderSize;

        float movementJerk; // 左右移動の躍度（加速度の変化量）
        float jumpForce; // ジャンプの力
        float gravity; // 重力
        float wallKickForce; // 壁キックの力（横）
        float wallFriction; // 壁摩擦

        float airMoveDecay; // 空中時の左右移動の減衰率
        float moveFriction; // 未入力時の減速
        float moveSpeedMax; // スピードの最大

        float dushAttakSpeed; // ダッシュ攻撃の速度
        float dushAttakDistance; // ダッシュ攻撃の距離
        float dushAttakCoolTime; // ダッシュ攻撃のクールタイム
    };

private:
    Vec2 mPosition; // 位置
    Vec2 mVelocity; // 速度
    Vec2 mAcceleration; // 加速度
    Vec2 mSize; // 大きさ

    float mGravityAcc = 0;

    Rect mImageRect; // 画像の矩形
    Rect mMapColliderRect; // マップチップ用の矩形

    int mMoveInput = 0; // 左右移動入力
    bool mJumpInput = false; // ジャンプ入力
    bool mJumpInputRelease = false;
    bool mAttakInput = false; // 攻撃入力
    bool mDushAttakInput = false; // ダッシュ攻撃入力
    Vec2 mDushAttakDirectionInput; // ダッシュ攻撃の向き

    bool mIsDoubleJump = false; // 二段ジャンプ可能
    bool mIsJump = false;
    bool mIsGround = false;
    bool mIsCeiling = false;
    bool mIsLeftonWall = false;
    bool mIsRightonWall = false;
    bool mIsMapCollsion = false;
    bool mIsRightDirection = false;

    bool mIsDushAttak = false;
    Vec2 mDushAttakDirection;
    Vec2 mDushAttakStartPosition;
    float mDushCoolTime = 0.0f;

public:
    Player(class Game* game);
    ~Player();

    void Create();
    void Update();
    void Draw();

    void StateUpdate();
    void Move();

    const Vec2& getPosition() const { return mPosition; }
    void setPosition(const Vec2& pos) { mPosition = pos; }
    const Vec2& getVelocity() const { return mVelocity; }
    void setVelocity(const Vec2& vel) { mVelocity = vel; }
    const Rect& mapColliderRect() const { return mMapColliderRect; }

    const Vec2& getDashAttakDirection() const { return mDushAttakDirectionInput; }
    
    void WallKick(int i); // 方向


    void SetState();

private:
    void Input();
    void ApplyForce();
};


