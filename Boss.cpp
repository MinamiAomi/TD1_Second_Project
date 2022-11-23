#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "DeltaTime.h"
#include "Func.h"
#include "Collision.h"

Boss::Boss(class Game* game) :
	GameObject(game)
{
	mBulletManagers.resize(kArmNum, game);
}
Boss::~Boss() {


}

void Boss::Create() {
	mTransForm.pos = BOSS_DATA.position;
	mTransForm.angle = BOSS_DATA.angle;
	mTransForm.scale = BOSS_DATA.scale;
	for (int i = 0; i < kArmNum; i++) {
		mArm1[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mTransForm};
		mArm2[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mArm1[i]};
		mHand[i] = { BOSS_DATA.root[i] * 2,0.0f,1.0f,&mArm2[i] };
		mWaponAngle[i] = 0.0f;
		mBulletManagers[i].Create();
		mHandHitPoint[i] = BOSS_DATA.handStartHitPoint;
		mTragetPos[i] = BOSS_DATA.root[i] * 100;
		mTragetLerp->Set(0.0f, 0.0f, mTragetPos[i], mTragetPos[i]);
	}
	mHitRect = BOSS_DATA.hitRect;
	mHitPoint = BOSS_DATA.startHitPoint;

	IK();


}

void Boss::Init() {
	mTransForm.pos = BOSS_DATA.position;
	mTransForm.angle = BOSS_DATA.angle;
	mTransForm.scale = BOSS_DATA.scale;
	for (int i = 0; i < kArmNum; i++) {
		mArm1[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mTransForm };
		mArm2[i] = { BOSS_DATA.root[i],0.0f,1.0f,&mArm1[i] };
		mHand[i] = { BOSS_DATA.root[i] * 2,0.0f,1.0f,&mArm2[i] };
		mWaponAngle[i] = 0.0f;
		mBulletManagers[i].Create();
		mHandHitPoint[i] = BOSS_DATA.handStartHitPoint;
		mHandInvincibleEffect[i] = 0xFFFFFFFF;
		mHandInvincibleEffectCycleTime[i] = 0.0f;
		mTragetPos[i] = BOSS_DATA.root[i] * 100;
		mTragetLerp->Set(0.0f, 0.0f, mTragetPos[i], mTragetPos[i]);
	}
	mHitRect = BOSS_DATA.hitRect;
	mHitPoint = BOSS_DATA.startHitPoint;

	mPatternTime = BOSS_DATA.patternTime;
	mCurrentPattern = kWait;

	mHeadInvincibleEffect = 0xFFFFFFFF;
	mBodyInvincibleEffect = 0xFFFFFFFF;
	mHeadInvincibleEffectCycleTime = 0.0f;
	mBodyInvincibleEffectCycleTime = 0.0f;

	IK();
}

void Boss::Update() {

	if (mHeadInvincibleTime > 0) {
		mHeadInvincibleTime += -DELTA_TIME->get();
	}
	if (mBodyInvincibleTime > 0) {
		mBodyInvincibleTime += -DELTA_TIME->get();
	}
	for (int i = 0; i < kArmNum; i++) {
		if (mHandInvincibleTime[i] > 0) {
			mHandInvincibleTime[i] += -DELTA_TIME->get();
		}
	}


	if (mPatternTime > 0) {
		mPatternTime += -DELTA_TIME->get();
	}
	if (mPatternTime <= 0.0f) {
		for (int i = 0; i < kArmNum; i++) {
			mBulletManagers[i].SetFire(false);
		}
		int pattern = Func::Random(0,40);
		if (10 <= pattern && pattern < 20) {
			mCurrentPattern = kBulletAttack;
			for (int i = 0; i < kArmNum; i++) {
				if (mHandHitPoint[i] > 0.0f) {
					mBulletManagers[i].SetFire(true);
				}
			}
		}
		else if (20 <= pattern && pattern < 30) {
			mCurrentPattern = kSpinAttack;
		}
		else {
			mCurrentPattern = kWait;
		}
		mPatternTime = BOSS_DATA.patternTime;
	}


	switch (mCurrentPattern)
	{
	case Boss::kWait:
		Wait();
		break;
	case Boss::kBulletAttack:

		BulletAttack();
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

	// ’eˆ—
	for (int i = 0; i < kArmNum; i++) {
		mBulletManagers[i].Update(GetHandPosition(i));
	}


	// ƒvƒŒƒCƒ„[‚ÉŒü‚¯‚é
	if (mCurrentPattern != kSpinAttack) {
		Vec2 ppos = PLAYER->getPosition();
		Vec2 bossPos = mTransForm.pos;
		for (int i = 0; i < kArmNum; i++) {
			if (mHandHitPoint[i] > 0.0f) {
				Vec2 arm1Pos = mArm1[i].pos + bossPos;
				Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
				Vec2 handPos = mHand[i].pos + arm2Pos;
				Vec2 tra = handPos;
				mWaponAngle[i] = (ppos - tra).Angle();
			}

		}
	}

}


void Boss::Draw() {

	Matrix33 mat = mTransForm.GetMatrix();
	Quad bossQuad = BOSS_DATA.mainImageQuad.TransForm(mat);
	if (mBodyInvincibleTime > 0.0f) {
		CAMERA->DrawQuad(bossQuad, BOSS_DATA.mainImage, mBodyInvincibleEffect);
	}
	else {
		CAMERA->DrawQuad(bossQuad, BOSS_DATA.mainImage);
	}
	if (mHeadInvincibleTime > 0.0f) {
		CAMERA->DrawQuad(BOSS_DATA.headImageQuad.TransForm(Matrix33::MakeTranslation(BOSS_DATA.headPos) * mat), BOSS_DATA.headImage, mHeadInvincibleEffect);
	}
	else {
		CAMERA->DrawQuad(BOSS_DATA.headImageQuad.TransForm(Matrix33::MakeTranslation(BOSS_DATA.headPos) * mat), BOSS_DATA.headImage);
	}

	Vec2 bossPos = mTransForm.pos;
	for (int i = 0; i < kArmNum; i++) {
		if (mHandHitPoint[i] > 0.0f) {
			mArm1[i].angle = mArm1[i].pos.Angle();
			mArm2[i].angle = mArm2[i].pos.Angle();
			mHand[i].angle = mHand[i].pos.Angle();

			Vec2 arm1Pos = mArm1[i].pos + bossPos;
			Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
			Vec2 handPos = mHand[i].pos + arm2Pos;

			if (i % 2 == 0) {
				CAMERA->DrawQuad(BOSS_DATA.armImageQuad.TransForm(arm1Pos, mArm2[i].angle), BOSS_DATA.arm1Image);
				CAMERA->DrawQuad(BOSS_DATA.arm2ImageQuad.TransForm(arm2Pos, mHand[i].angle), BOSS_DATA.arm2Image);
			}
			else {
				CAMERA->DrawQuad(BOSS_DATA.armImageQuad.VerticalFlip().TransForm(arm1Pos, mArm2[i].angle), BOSS_DATA.arm1Image);
				CAMERA->DrawQuad(BOSS_DATA.arm2ImageQuad.VerticalFlip().TransForm(arm2Pos, mHand[i].angle), BOSS_DATA.arm2Image);
			}

			Matrix33 waponMat = Matrix33::MakeRotation(mWaponAngle[i]) * Matrix33::MakeTranslation(handPos);
			if (mHandInvincibleTime[i] > 0.0f) {
				CAMERA->DrawQuad(BOSS_DATA.gunHandImageQuad.TransForm(waponMat), BOSS_DATA.gunHandImage, mHandInvincibleEffect[i]);
			}
			else {
				CAMERA->DrawQuad(BOSS_DATA.gunHandImageQuad.TransForm(waponMat), BOSS_DATA.gunHandImage);
			}
		}
		mBulletManagers[i].Draw();
	}
	//const auto& boss = GetHitRect();
	//CAMERA->DrawRect(boss.body, RED, kFillModeWireFrame);
	//CAMERA->DrawRect(boss.head, RED, kFillModeWireFrame);
	//if (mHeadInvincibleTime > 0.0f) {
	//	CAMERA->DrawRect(boss.head, 0xFF00FF, kFillModeSolid);
	//}
	//if (mBodyInvincibleTime > 0.0f) {
	//	CAMERA->DrawRect(boss.body, 0xFF00FF, kFillModeSolid);
	//}
	//for (int i = 0; i < kArmNum; i++) {
	//	if (mHandHitPoint[i] > 0.0f) {
	//		CAMERA->DrawRect(boss.hand[i], RED, kFillModeWireFrame);
	//		if (mHandInvincibleTime[i] > 0.0f) {
	//			CAMERA->DrawRect(boss.hand[i], 0xFF00FF, kFillModeSolid);
	//		}
	//	}
	//}


	

}

void Boss::Collision()
{
	const auto& boss = GetHitRect();
	if (PLAYER->IsSlash()) {
		const auto& player = PLAYER->getSlashRect();
		if (Collision::RectRect(player, boss.head) && mHeadInvincibleTime <= 0.0f) {
			mHeadInvincibleTime = BOSS_DATA.invincibleTime;
			mHitPoint -= PLAYER_DATA.slashAttackPower * 1.5f;
			mHeadInvincibleEffectCycleTime = 0.1f;
		}
		else {
			if (Collision::RectRect(player, boss.body) && mBodyInvincibleTime <= 0.0f) {
				mHitPoint -= PLAYER_DATA.slashAttackPower;
				mBodyInvincibleTime = BOSS_DATA.invincibleTime;
				mBodyInvincibleEffectCycleTime = 0.1f;
			}
			for (int i = 0; i < kArmNum; i++) {
				if (mHandHitPoint[i] > 0.0f) {
					if (Collision::RectRect(player, boss.hand[i]) && mHandInvincibleTime[i] <= 0.0f) {
						mHandInvincibleTime[i] = BOSS_DATA.invincibleTime;
						mHandHitPoint[i] -= PLAYER_DATA.slashAttackPower;
						mHitPoint -= PLAYER_DATA.slashAttackPower;
						mHandInvincibleEffectCycleTime[i] = 0.1f;
					}
				}
			}
		}
	}







}

void Boss::Animation() {

	float cycleTime = 0.1f;
	if (mHeadInvincibleTime > 0.0f) {
		if (mHeadInvincibleEffectCycleTime > 0) {
			mHeadInvincibleEffectCycleTime += -DELTA_TIME->get();
		}
		if (mHeadInvincibleEffectCycleTime <= 0.0f) {
			mHeadInvincibleEffectCycleTime = cycleTime;
			if (mHeadInvincibleEffect == 0xFFFFFFFF) {
				mHeadInvincibleEffect = 0;
			}
			else {
				mHeadInvincibleEffect = 0xFFFFFFFF;
			}
		}
	}
	if (mBodyInvincibleTime > 0.0f) {
		if (mBodyInvincibleEffectCycleTime > 0) {
			mBodyInvincibleEffectCycleTime += -DELTA_TIME->get();
		}
		if (mBodyInvincibleEffectCycleTime <= 0.0f) {
			mBodyInvincibleEffectCycleTime = cycleTime;
			if (mBodyInvincibleEffect == 0xFFFFFFFF) {
				mBodyInvincibleEffect = 0;
			}
			else {
				mBodyInvincibleEffect = 0xFFFFFFFF;
			}
		}
	}
	for (int i = 0; i < kArmNum; i++) {
		if (mHandHitPoint[i] > 0.0f) {
			if (mHandInvincibleTime[i] > 0.0f) {
				if (mHandInvincibleEffectCycleTime[i] > 0) {
					mHandInvincibleEffectCycleTime[i] += -DELTA_TIME->get();
				}
				if (mHandInvincibleEffectCycleTime[i] <= 0.0f) {
					mHandInvincibleEffectCycleTime[i] = cycleTime;
					if (mHandInvincibleEffect[i] == 0xFFFFFFFF) {
						mHandInvincibleEffect[i] = 0;
					}
					else {
						mHandInvincibleEffect[i] = 0xFFFFFFFF;
					}
				}
			}
		}
	}

}

Boss::HitRect Boss::GetHitRect()
{
	HitRect result = {};
	result.body = mHitRect.body.Translation(mTransForm.pos);
	result.head = mHitRect.head.Translation((Matrix33::MakeTranslation(BOSS_DATA.headPos) * mTransForm.GetMatrix()).GetTrans());
	
	for (int i = 0; i < kArmNum; i++) {
		result.hand[i] = mHitRect.hand[i].Translation(GetHandPosition(i));
	}
	return result;
}

Vec2 Boss::GetHandPosition(int i) {
	Vec2 bossPos = mTransForm.pos;
	Vec2 arm1Pos = mArm1[i].pos + bossPos;
	Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
	Vec2 handPos = mHand[i].pos + arm2Pos;
	Vec2 waponPos = Vec2 { BOSS_DATA.hitRectLen,0.0f } * Matrix33::MakeRotation(mWaponAngle[i]);
	return waponPos + handPos;
}

void Boss::IK() {
	float len = BOSS_DATA.armLength;
	for (int i = 0; i < kArmNum; i++) {
		if (mHandHitPoint[i] > 0.0f) {
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
}

void Boss::Wait() {
	for (int i = 0; i < kArmNum; i++) {
		if (mHandHitPoint[i] > 0.0f) {
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
				float tm = Func::Random(0.5f, 3.0f);
				Vec2 end = { Func::Random(0.0f,len) * xsign,Func::Random(0.0f,len) * ysign };
				if (Func::Random(0, 20) == 0) {
					end = PLAYER->getPosition() - mTransForm.pos;
					tm = 3.0f;
				}
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
}
void Boss::BulletAttack() 
{
}
void Boss::SpinAttack() 
{
	mSpinAngle += Math::ToRadians(5.0f);
	for (int i = 0; i < kArmNum; i++) {
		Vec2 pos = BOSS_DATA.root[i].Rotated(mSpinAngle).Normalized() * 1000.0f;
		mTragetPos[i] = mTransForm.pos + pos;
	}
}

