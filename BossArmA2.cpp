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
	Matrix33 mat = mTransForm.GetParentMatrix();

	BOSS_CAMERA->DrawCircle({ mTransForm.pos * mat,20 });
	Quad quad = BOSS_INITDATA.armA2.imageQuad.TransForm(mTransForm.GetMatrix() * mat);
	BOSS_CAMERA->DrawQuad(quad, BOSS_INITDATA.armA2.image);
}