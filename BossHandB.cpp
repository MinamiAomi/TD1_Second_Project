#include "BossHandB.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossHandB::BossHandB(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossHandB::~BossHandB() {

}

void BossHandB::Create() {
	mTransForm.pos = BOSS_INITDATA.handB.position;
	mTransForm.angle = BOSS_INITDATA.handB.angle;
	mTransForm.scale = BOSS_INITDATA.handB.scale;
}

void BossHandB::Update() {
	mTransForm.angle += Math::ToRadians(-2.0f);
}

void BossHandB::Draw() {
	Quad quad = BOSS_INITDATA.handB.imageQuad.TransForm(mTransForm.GetConnectMatrix());
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.handB.image);
}