#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"
#include <vector>
#include "PlayerJumpEffect.h"
#include "Animation.h"

class Player :
    public GameObject
{

public:

    enum State {
        kStateGround, // 地面にいる
        kStateAir, // 空中にいる

        kStateNum
    };

    enum Anime {
        kRun,
        
        kAnimeNum,
        
        kWait,
        kJump,
        kFall,
        kDush,
    };

    struct InitData {
        ImageData waitImage;
        Quad waitImageQuad;

        ImageData runImage;
        Quad runImageQuad;
        int runFrameNum;
        float runAnimeTime;

        ImageData dushImage;
        Quad dushImageQuad;

        ImageData jumpImage;
        Quad jumpImageQuad;

        ImageData fallImage;
        Quad fallImageQuad;


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

        int jumpEffectNum;

        float hitRectWidth; // ダメージを受ける矩形の幅
        float hitRectHeight; // ダメージを受ける矩形の高さ

        float invincibleTime; // 無敵時間

        float knockBackCoolTime; // ノックバックの初速度
        float knockBackFirstSpeed; // ノックバックの初速度
        Vec2 knockBackDirection; // ノックバックの向き
        float startHitPoint; // 初期hp

        ImageData slashImage;
        Quad slashImageQuad;
        float slashAnimeTime; // 攻撃のアニメーションの切り替わる時間
        int slashAnimeNum; // 攻撃のアニメーションの枚数
        Rect slashCollider;
        unsigned int slashColor;
        float slashCoolTime;
        float slashAttackPower;
    };

private:
    float mHitPoint = 0;

    Vec2 mPosition; // 位置
    Vec2 mVelocity; // 速度
    Vec2 mAcceleration; // 加速度
    Vec2 mSize; // 大きさ

    float mGravityAcc = 0;

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

    Vec2 mSlashPos;
    Vec2 mSlashLeft;
    bool mIsSlash = false;
    Animation mSlashAnime;
    bool mSlashDirection = true;
    float mSlashCoolTime = 0.0f;

    std::vector<PlayerJumpEffect> mJumpEffect;

    float mKnockBackCoolTime = 0.0f;
    Lerp<Vec2> mKnockBackVel;
    bool mIsInvincible = false;
    float mInvincibleTime = 0.0f;
    Rect mHitRect;

    Animation mRunAnimation;
    Anime mCurrentAnime;

    unsigned int mInvincibleEffect;
    float mInvincibleEffectCycleTime;

public:
    Player(class Game* game);
    ~Player();

    void Create();
    void Init();
    void Update();
    void Draw();
    void Collision();
    void Animation();

    void StateUpdate();
    void Move();

    const Vec2& getPosition() const { return mPosition; }
    void setPosition(const Vec2& pos) { mPosition = pos; }
    const Vec2& getVelocity() const { return mVelocity; }
    void setVelocity(const Vec2& vel) { mVelocity = vel; }
    const Rect& mapColliderRect() const { return mMapColliderRect; }
    bool IsInvincible() const { return mIsInvincible; }
    const Rect& HitRect() const { return mHitRect.Translation(mPosition); }
    
    const Vec2& getDashAttakDirection() const { return mDushAttakDirectionInput; }
    
    void WallKick(int i); // 方向
    void SetState();

    bool IsSlash() const { return mIsSlash; }
    Rect getSlashRect() const;

    bool isDeath() const { return mHitPoint <= 0.0f; }
    float getHitPoint() const { return mHitPoint; }

private:
    void NormalState();
    void DushAttakState();

    void Input();
};


