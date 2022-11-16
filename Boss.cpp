#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "BossArmA1.h"
#include "BossArmA2.h"
#include "BossHandA.h"
#include "BossArmB1.h"
#include "BossArmB2.h"
#include "BossHandB.h"
#include "Func.h"

#define BOSS_DATA getGame()->getContainer()->getBossData()

Boss::Boss(class Game* game) :
	GameObject(game)
{
	mParts[kBossPartArmA1] = mArmA1 = new BossArmA1(this,&mTransForm);
	mParts[kBossPartArmB1] = mArmB1 = new BossArmB1(this, &mTransForm);

	mParts[kBossPartArmA2] = mArmA2 = new BossArmA2(this,mParts[kBossPartArmA1]->GetTransFormPtr());
	mParts[kBossPartArmB2] = mArmB2 = new BossArmB2(this,mParts[kBossPartArmB1]->GetTransFormPtr());
	
	mParts[kBossPartHandA] = mHandA = new BossHandA(this, mParts[kBossPartArmA2]->GetTransFormPtr());
	mParts[kBossPartHandB] = mHandB = new BossHandB(this, mParts[kBossPartArmB2]->GetTransFormPtr());
}
Boss::~Boss() {
	mHandB = nullptr;
	mHandA = nullptr;
	
	mArmB2 = nullptr;
	mArmA2 = nullptr;
	
	mArmB1 = nullptr;
	mArmA1 = nullptr;
	for (auto it : mParts) {
		Func::SafeDelete(it);
	}
}

void Boss::Create() {
	mTransForm.pos = BOSS_DATA.main.position;
	mTransForm.angle = BOSS_DATA.main.angle;
	mTransForm.scale = BOSS_DATA.main.scale;

	for (auto it : mParts) {
		it->Create();
	}
}

void Boss::Update() {
	
	for (auto it : mParts) {
		it->Update();
	}
}
void Boss::Draw() {
	Quad bossQuad = BOSS_DATA.main.imageQuad.TransForm(mTransForm.GetMatrix());
	CAMERA->DrawQuad(bossQuad, BOSS_DATA.main.image);
	for (auto it : mParts) {
		it->Draw();
	}
}