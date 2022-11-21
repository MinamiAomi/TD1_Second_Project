#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"

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
		kArmAttack,
		kSpinAttack,

		kMovePattern
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
	};

private:
	TransForm mTransForm;
	
	TransForm mArm1[kArmNum] = {};
	TransForm mArm2[kArmNum] = {};
	TransForm mHand[kArmNum] = {};
	float mWaponAngle[kArmNum] = {};
	Lerp<Vec2> mTragetLerp[kArmNum];
	Vec2 mTragetPos[kArmNum];

	MovePattern mCurrentPattern = kWait;


public:
	Boss(class Game* game);
	~Boss();

	void Create();
	void Update();
	void Draw();

	const Vec2& GetPosition() const { return mTransForm.pos; }
	float GetAngle() const { return mTransForm.angle; }
	float GetScale() const { return mTransForm.scale; }
	void SetPosition(const Vec2& pos) { mTransForm.pos = pos; }
	void SetAngle(float angle) { mTransForm.angle = angle; }
	void SetScale(float scale) { mTransForm.scale = scale; }


private:

	void Wait();
	void ArmAttack();
	void SpinAttack();
	void IK();

};
