#include "BossArmA1.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossArmA1::BossArmA1(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossArmA1::~BossArmA1() {

}

void BossArmA1::Create() {
	mTransForm.pos = BOSS_INITDATA.armA1.position;
	mTransForm.angle = BOSS_INITDATA.armA1.angle;
	mTransForm.scale = BOSS_INITDATA.armA1.scale;


}

void BossArmA1::Update() {
	//mTransForm.angle += Math::ToRadians(2.0f);
}

void BossArmA1::Draw() {
	Quad quad = BOSS_INITDATA.armA1.imageQuad.TransForm(mTransForm.GetConnectMatrix());
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.armA1.image);
}