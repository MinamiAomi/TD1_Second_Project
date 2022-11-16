#include "BossArmA2.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossArmA2::BossArmA2(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossArmA2::~BossArmA2() {

}

void BossArmA2::Create() {
	mTransForm.pos = BOSS_INITDATA.armA2.position;
	mTransForm.angle = BOSS_INITDATA.armA2.angle;
	mTransForm.scale = BOSS_INITDATA.armA2.scale;
}

void BossArmA2::Update() {
	//mTransForm.angle += Math::ToRadians(2.0f);
}

void BossArmA2::Draw() {
	Quad quad = BOSS_INITDATA.armA2.imageQuad.TransForm(mTransForm.GetConnectMatrix());
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.armA2.image);
}