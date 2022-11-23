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
        kStateGround, // �n�ʂɂ���
        kStateAir, // �󒆂ɂ���

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

        float movementJerk; // ���E�ړ��̖��x�i�����x�̕ω��ʁj
        float jumpForce; // �W�����v�̗�
        float gravity; // �d��
        float wallKickForce; // �ǃL�b�N�̗́i���j
        float wallFriction; // �ǖ��C

        float airMoveDecay; // �󒆎��̍��E�ړ��̌�����
        float moveFriction; // �����͎��̌���
        float moveSpeedMax; // �X�s�[�h�̍ő�

        float dushAttakSpeed; // �_�b�V���U���̑��x
        float dushAttakDistance; // �_�b�V���U���̋���
        float dushAttakCoolTime; // �_�b�V���U���̃N�[���^�C��

        int jumpEffectNum;

        float hitRectWidth; // �_���[�W���󂯂��`�̕�
        float hitRectHeight; // �_���[�W���󂯂��`�̍���

        float invincibleTime; // ���G����

        float knockBackCoolTime; // �m�b�N�o�b�N�̏����x
        float knockBackFirstSpeed; // �m�b�N�o�b�N�̏����x
        Vec2 knockBackDirection; // �m�b�N�o�b�N�̌���
        float startHitPoint; // ����hp

        ImageData slashImage;
        Quad slashImageQuad;
        float slashAnimeTime; // �U���̃A�j���[�V�����̐؂�ւ�鎞��
        int slashAnimeNum; // �U���̃A�j���[�V�����̖���
        Rect slashCollider;
        unsigned int slashColor;
        float slashCoolTime;
        float slashAttackPower;
    };

private:
    float mHitPoint = 0;

    Vec2 mPosition; // �ʒu
    Vec2 mVelocity; // ���x
    Vec2 mAcceleration; // �����x
    Vec2 mSize; // �傫��

    float mGravityAcc = 0;

    Rect mMapColliderRect; // �}�b�v�`�b�v�p�̋�`

    int mMoveInput = 0; // ���E�ړ�����
    bool mJumpInput = false; // �W�����v����
    bool mJumpInputRelease = false;
    bool mAttakInput = false; // �U������
    bool mDushAttakInput = false; // �_�b�V���U������
    Vec2 mDushAttakDirectionInput; // �_�b�V���U���̌���

    bool mIsDoubleJump = false; // ��i�W�����v�\
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
    
    void WallKick(int i); // ����
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


