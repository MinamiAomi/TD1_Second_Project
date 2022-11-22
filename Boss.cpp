#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "DeltaTime.h"
#include "Func.h"

#define BOSS_DATA getGame()->getContainer()->getBossData()

Boss::Boss(class Game* game) :
	GameObject(game)
{

}
Boss::~Boss() {


}

void Boss::Create() {
	mTransForm.pos = BOSS_DATA.position;
	mTransForm.angle = BOSS_DATA.angle;
	mTransForm.scale = BOSS_DATA.scale;
	TransForm tmp = { {0,0},0.0f,1.0f };
	for (int i = 0; i < kArmNum; i++) {
		mArm1[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mTransForm};
		mArm2[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mArm1[i]};
		mHand[i] = { BOSS_DATA.root[i] * 2,0.0f,1.0f,&mArm2[i] };
		mWaponAngle[i] = 0.0f;
	}
}

void Boss::Update() {

	//static float s[4] = {};
	///mTransForm.pos += {5, 0};
	//for (int i = 0; i < kArmNum; i++) {
	//	mTragetPos[i] = mTransForm.pos;
	//}
	//mTragetPos[0] = PLAYER->getPosition();
	static Vec2 vel(300.0f, 0.0f);
	//mTransForm.pos += vel * DELTA_TIME->get();
	//mTransForm.angle += Math::ToRadians(1.0f);
	if (mTransForm.pos.x <= 360 || 2060 <= mTransForm.pos.x) {
		vel = -vel;
	}

	switch (mCurrentPattern)
	{
	case Boss::kWait:
		Wait();
		break;
	case Boss::kArmAttack:
		ArmAttack();
		break;
	case Boss::kSpinAttack:
		SpinAttack();
		break;
	case Boss::kMovePattern:
		break;
	default:
		break;
	}

	IK();

	// ƒvƒŒƒCƒ„[‚ÉŒü‚¯‚é
	Vec2 ppos = PLAYER->getPosition();
	Vec2 bossPos = mTransForm.pos;
	for (int i = 0; i < kArmNum; i++) {

		Vec2 arm1Pos = mArm1[i].pos + bossPos;
		Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
		Vec2 handPos = mHand[i].pos + arm2Pos;
		Vec2 tra = handPos;
		mWaponAngle[i] = (ppos - tra).Angle();

	}




}


void Boss::Draw() {

	Matrix33 mat = mTransForm.GetMatrix();
	Quad bossQuad = BOSS_DATA.mainImageQuad.TransForm(mat);
	CAMERA->DrawQuad(bossQuad, BOSS_DATA.mainImage);
	CAMERA->DrawQuad(BOSS_DATA.headImageQuad.TransForm(Matrix33::MakeTranslation(BOSS_DATA.headPos) * mat), BOSS_DATA.headImage);
	
	Vec2 bossPos = mTransForm.pos;
	for (int i = 0; i < kArmNum; i++) {
		mArm1[i].angle = mArm1[i].pos.Angle();
		mArm2[i].angle = mArm2[i].pos.Angle();
		mHand[i].angle = mHand[i].pos.Angle();

		Vec2 arm1Pos = mArm1[i].pos + bossPos;
		Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
		Vec2 handPos = mHand[i].pos + arm2Pos;

		if (i % 2 == 0) {
			CAMERA->DrawQuad(BOSS_DATA.armImageQuad.TransForm(arm1Pos, mArm2[i].angle), BOSS_DATA.arm1Image);
			CAMERA->DrawQuad(BOSS_DATA.armImageQuad.TransForm(arm2Pos, mHand[i].angle), BOSS_DATA.arm2Image);
		}
		else {
			CAMERA->DrawQuad(BOSS_DATA.armImageQuad.VerticalFlip().TransForm(arm1Pos, mArm2[i].angle), BOSS_DATA.arm1Image);
			CAMERA->DrawQuad(BOSS_DATA.armImageQuad.VerticalFlip().TransForm(arm2Pos, mHand[i].angle), BOSS_DATA.arm2Image);
		}
		
		Matrix33 waponMat = Matrix33::MakeRotation(mWaponAngle[i]) * Matrix33::MakeTranslation(handPos);
		if (i % 2 == 0) {
			if (i / 2 == 0) {
				CAMERA->DrawQuad(BOSS_DATA.gunHandImageQuad.TransForm(waponMat), BOSS_DATA.gunHandImage);
			}
			else {
				CAMERA->DrawQuad(BOSS_DATA.swordHandImageQuad.TransForm(waponMat), BOSS_DATA.swordHandImage);
			}
		}
		else {
			if (i / 2 == 0) {
				CAMERA->DrawQuad(BOSS_DATA.gunHandImageQuad.VerticalFlip().TransForm(waponMat), BOSS_DATA.gunHandImage);
			}
			else {
				CAMERA->DrawQuad(BOSS_DATA.swordHandImageQuad.VerticalFlip().TransForm(waponMat), BOSS_DATA.swordHandImage);
			}
		}
	}
}


void Boss::IK() {
	float len = BOSS_DATA.armLength;
	for (int i = 0; i < kArmNum; i++) {

		Vec2 endroot = mTragetPos[i] - mArm1[i].pos - mTransForm.pos;
		float A = endroot.Length();
		endroot = endroot.Normalized();

		float angleFromX = endroot.Angle();
		float theta = Math::Acos((A * A + len * len - len * len) / (2.0f * A * len));

		if (i == 0 || i == 2) {
			angleFromX += theta;
		}
		else {
			angleFromX += -theta;
		}
		if (A < len * 2) {
			mArm2[i].pos = Vec2(Math::Cos(angleFromX), Math::Sin(angleFromX)) * len;
			mHand[i].pos = mTragetPos[i] - mArm2[i].pos - mArm1[i].pos - mTransForm.pos;
		}
		else {
			mArm2[i].pos = endroot * len;
			mHand[i].pos = endroot * len;
		}

	}
}

void Boss::Wait() {
	for (int i = 0; i < kArmNum; i++) {
		if (mTragetLerp[i].IsEdge() == true) {
			float len = BOSS_DATA.armLength * 2.5f;
			int xsign = 1;
			int ysign = 1;
			if (i % 2 == 0) {
				xsign = -1;
			}
			if ((int)(i / 2) != 0) {
				ysign = -1;
			}
			Vec2 end = { Func::Random(0.0f,len) * xsign,Func::Random(0.0f,len) * ysign };
			float tm = Func::Random(0.5f, 3.0f);
			mTragetLerp[i].SetStart(mTragetPos[i] - mTransForm.pos);
			mTragetLerp[i].SetEnd(end);
			mTragetLerp[i].SetParam(0.0f);
			mTragetLerp[i].SetDeltaParam(1.0f / tm);
		}
		
		mTragetLerp[i].Increment(DELTA_TIME->get());
		mTragetLerp[i].ParamClamp();
		mTragetPos[i] = mTransForm.pos + mTragetLerp[i].Calc();
	}
}
void Boss::ArmAttack() {

}
void Boss::SpinAttack() {

}