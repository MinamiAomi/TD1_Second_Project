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
        kStateGround, // �n�ʂɂ���
        kStateAir, // �󒆂ɂ���

        kStateNum
    };

    struct InitData {
        ImageData image;

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
    };

private:
    Vec2 mPosition; // �ʒu
    Vec2 mVelocity; // ���x
    Vec2 mAcceleration; // �����x
    Vec2 mSize; // �傫��

    float mGravityAcc = 0;

    Rect mImageRect; // �摜�̋�`
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
    
    void WallKick(int i); // ����


    void SetState();

private:
    void Input();
    void ApplyForce();
};


