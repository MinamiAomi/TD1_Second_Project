#include "BossArmB1.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossArmB1::BossArmB1(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossArmB1::~BossArmB1() {

}

void BossArmB1::Create() {
	mTransForm.pos = BOSS_INITDATA.armB1.position;
	mTransForm.angle = BOSS_INITDATA.armB1.angle;
	mTransForm.scale = BOSS_INITDATA.armB1.scale;
}

void BossArmB1::Update() {
	mTransForm.angle += Math::ToRadians(-2.0f);
}

void BossArmB1::Draw() {
	Quad quad = BOSS_INITDATA.armB1.imageQuad.TransForm(mTransForm.GetConnectMatrix());
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.armB1.image);
}