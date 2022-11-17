#include "BossHandA.h"
#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

BossHandA::BossHandA(class Boss* boss, TransForm* parent) :
	BossPart(boss, parent) {

}

BossHandA::~BossHandA() {

}

void BossHandA::Create() {
	mTransForm.pos = BOSS_INITDATA.handA.position;
	mTransForm.angle = BOSS_INITDATA.handA.angle;
	mTransForm.scale = BOSS_INITDATA.handA.scale;
}

void BossHandA::Update() {
	mTransForm.angle += Math::ToRadians(2.0f);
}

void BossHandA::Draw() {
	Matrix33 mat = mTransForm.GetParentMatrix();

	BOSS_CAMERA->DrawCircle({ mTransForm.pos * mat,20 });
	Quad quad = BOSS_INITDATA.handA.imageQuad.TransForm(mTransForm.GetMatrix() * mat);
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.handA.image);
}