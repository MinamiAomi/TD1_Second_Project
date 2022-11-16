#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"

class Boss :
	public GameObject
{
public:
	struct InitData
	{
		ImageData image;
		Quad imageQuad;

		Vec2 position;
		float angle;
		float scale;
	};

	enum BossPartId
	{
		kBossPartArmA1,
		kBossPartArmB1,

		kBossPartArmA2,
		kBossPartArmB2,
		
		kBossPartHandA,
		kBossPartHandB,


		kBossPartIdNum
	};

private:
	TransForm mTransForm;
	class BossPart* mParts[kBossPartIdNum];
	class BossArmA1* mArmA1 = nullptr;
	class BossArmB1* mArmB1 = nullptr;

	class BossArmA2* mArmA2 = nullptr;
	class BossArmB2* mArmB2 = nullptr;

	class BossHandA* mHandA = nullptr;
	class BossHandB* mHandB = nullptr;

public:
	Boss(class Game* game);
	~Boss();

	TransForm* TransFormPtr() { return &mTransForm; }

	void Create();
	void Update();
	void Draw();

	const Vec2& GetPosition() const { return mTransForm.pos; }
	float GetAngle() const { return mTransForm.angle; }
	float GetScale() const { return mTransForm.scale; }
	void SetPosition(const Vec2& pos) { mTransForm.pos = pos; }
	void SetAngle(float angle) { mTransForm.angle = angle; }
	void SetScale(float scale) { mTransForm.scale = scale; }
};
