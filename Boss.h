#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"
#include "BossArmBulletManager.h"
#include <vector>
class Boss :
	public GameObject
{
public:
	enum ArmId 
	{
		kArmLeftTop,
		kArmRightTop,
		kArmLeftBottom,
		kArmRightBottom,

		kArmNum
	};
	
	enum MovePattern
	{
		kWait,
		kBulletAttack,
		kSpinAttack,

		kMovePattern
	};

	

	struct HitRect {
		Rect head;
		Rect body;
		Rect hand[kArmNum];
	};
	struct InitData
	{
		ImageData mainImage;
		ImageData arm1Image;
		ImageData arm2Image;
		ImageData swordHandImage;
		ImageData gunHandImage;
		ImageData headImage;
		Quad mainImageQuad;
		Quad armImageQuad;
		Quad arm2ImageQuad;
		Quad swordHandImageQuad;
		Quad gunHandImageQuad;
		Quad headImageQuad;

		Vec2 position;
		float angle;
		float scale;

		float armLength;
		float rootLength;
		Vec2 root[kArmNum];
		Vec2 headPos;

		float patternTime;

		float startHitPoint;
		float bodyAttackPower;
		HitRect hitRect;
		float hitRectLen;

		ImageData bulletImage;
		Quad bulletImageQuad;
		Rect bulletHitRect;
		float bulletSpeed;
		float bulletAttackPower;
		float bulletCoolTime;
		int bulletMaxNum; // マネージャー一つつき
		float bulletAttackTime;

		
		float invincibleTime;
		float handStartHitPoint;
	};


private:
	TransForm mTransForm;
	
	TransForm mArm1[kArmNum] = {};
	TransForm mArm2[kArmNum] = {};
	TransForm mHand[kArmNum] = {};
	float mWaponAngle[kArmNum] = {};
	Lerp<Vec2> mTragetLerp[kArmNum];
	Vec2 mTragetPos[kArmNum];

	std::vector<BossArmBulletManager> mBulletManagers;
	MovePattern mCurrentPattern = kWait;
	float mPatternTime = 0.0f;

	HitRect mHitRect;
	float mHitPoint = 0.0f;

	float mBulletAttackTime = 0.0f;

	float mHeadInvincibleTime = false;
	float mBodyInvincibleTime = false;
	float mHandInvincibleTime[kArmNum] = { false };
	unsigned int mHeadInvincibleEffect;
	unsigned int mBodyInvincibleEffect;
	unsigned int mHandInvincibleEffect[kArmNum];
	float mHeadInvincibleEffectCycleTime;
	float mBodyInvincibleEffectCycleTime;
	float mHandInvincibleEffectCycleTime[kArmNum];


	float mHandHitPoint[kArmNum] = { 0.0f };

	float mSpinAngle = 0.0f;

public:
	Boss(class Game* game);
	~Boss();

	void Create();
	void Init();
	void Update();
	void Draw();
	void Collision();
	void Animation();

	const Vec2& GetPosition() const { return mTransForm.pos; }
	float GetAngle() const { return mTransForm.angle; }
	float GetScale() const { return mTransForm.scale; }
	void SetPosition(const Vec2& pos) { mTransForm.pos = pos; }
	void SetAngle(float angle) { mTransForm.angle = angle; }
	void SetScale(float scale) { mTransForm.scale = scale; }
	HitRect GetHitRect();
	Vec2 GetHandPosition(int i);
	const BossArmBulletManager& getBulletManager(int i) const { return mBulletManagers[i]; }
	bool IsHandAlive(int i) const { return mHandHitPoint[i] > 0.0f; }

	float getHitPoint() const { return mHitPoint; }

	bool isClear() const { return mHitPoint <= 0.0f; }

private:

	void Wait();
	void BulletAttack();
	void SpinAttack();
	void LaserAttack();
	void IK();

};
