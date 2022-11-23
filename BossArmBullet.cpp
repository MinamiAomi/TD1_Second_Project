#include "BossArmBullet.h"
#include "Game.h"
#include "Container.h"
#include "DeltaTime.h"
#include "Map.h"
#include "Camera.h"

BossArmBullet::BossArmBullet(Game* game) :
	GameObject(game)
{
}

BossArmBullet::~BossArmBullet()
{
}

void BossArmBullet::Create(const Vec2& pos, const Vec2& target)
{
	mIsAlive = true;
	mPosition = pos;
	mVelocity = (target - pos).Normalized() * BOSS_DATA.bulletSpeed;
	mAngle = mVelocity.Angle();
}

void BossArmBullet::Init()
{
	mIsAlive = false;
}

void BossArmBullet::Update()
{
	
	Vec2 vel = mVelocity * DELTA_TIME->get();
	mPosition += vel;
	bool ishit = false;
	mPosition = MAP->PushOut(mPosition, vel, BOSS_DATA.bulletHitRect, &ishit);
	if (ishit) {
		mIsAlive = false;
	}
	
}

void BossArmBullet::Draw()
{
	
	CAMERA->DrawQuad(BOSS_DATA.bulletImageQuad.TransForm(mPosition, mAngle), BOSS_DATA.bulletImage);
}

Rect BossArmBullet::GetRect() const 
{
	return BOSS_DATA.bulletHitRect.Translation(mPosition);
}
