#include "BossArmB2.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossArmB2::BossArmB2(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossArmB2::~BossArmB2() {

}

void BossArmB2::Create() {
	mTransForm.pos = BOSS_INITDATA.armB2.position;
	mTransForm.angle = BOSS_INITDATA.armB2.angle;
	mTransForm.scale = BOSS_INITDATA.armB2.scale;
}

void BossArmB2::Update() {
	mTransForm.angle += Math::ToRadians(-2.0f);
}

void BossArmB2::Draw() {
	Quad quad = BOSS_INITDATA.armB2.imageQuad.TransForm(mTransForm.GetConnectMatrix());
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.armB2.image);
}