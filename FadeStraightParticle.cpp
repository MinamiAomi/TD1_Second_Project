#include "FadeStraightParticle.h"
#include "Game.h"
#include "Camera.h"
#include "Container.h"
#include "MoveComponent.h"
#include "FadeAlphaComponent.h"
#include "SizeComponent.h"
#include "Func.h"
#include "DeltaTime.h"

FadeStraightParticle::FadeStraightParticle(class Game* game) :
	Particle(game) {
	mSizeComponent = new SizeComponent(*this);
	mMoveComponent = new MoveComponent(*this);
	mColorComponent = new FadeAlphaComponent(*this);
}

FadeStraightParticle::~FadeStraightParticle() {
	Func::SafeDelete(mSizeComponent);
	Func::SafeDelete(mMoveComponent);
	Func::SafeDelete(mColorComponent);
}

void FadeStraightParticle::ComponentCreate(class Game* game) {
	setGame(game);
	mSizeComponent = new SizeComponent(*this);
	mMoveComponent = new MoveComponent(*this);
	mColorComponent = new FadeAlphaComponent(*this);
}

void FadeStraightParticle::Create(const Vec2& pos, const Vec2& vel, float firstsize, float finalsize, unsigned int col, float exitT) {
	setAlive(true);
	setLeftTime(exitT);
	setExitTime(exitT);
	mSizeComponent->setFirstSize(firstsize);
	mSizeComponent->setFinalSize(finalsize);
	mMoveComponent->setPosition(pos);
	mMoveComponent->setVelocity(vel);
	mColorComponent->setColor(col);
}

void FadeStraightParticle::Update() {
	TimeUpdate();
	mMoveComponent->Update(getGame()->getDeltaTime()->get());
	float size = mSizeComponent->getSize();
	float hsize = size / 2.0f;
	Vec2 wall = false;
	mMoveComponent->setPosition(MAP->PushOut(
		mMoveComponent->getPosition(), mMoveComponent->getVelocity() * DELTA_TIME->get(),
		{ {-hsize,hsize},size,size }, &wall));

	if (wall.IsZero() == false) {
		mMoveComponent->setVelocity(mMoveComponent->getVelocity().Reflected(wall));
	}

	mColorComponent->Update();
}

void FadeStraightParticle::Draw() {
	float rad = mSizeComponent->getSize();
	Vec2 leftTop(-rad / 2.0f, rad / 2.0f);
	getGame()->getCamera()->DrawSpriteRect(
		{ leftTop + mMoveComponent->getPosition(), rad, rad}, 
		getGame()->getContainer()->getParticleData().fadeStraight.image, 
		mColorComponent->getColor());
}

//void FadeParticle::Update() {
//	mLeftTime += -getGame()->getDeltaTime()->get();
//	if (mLeftTime <= 0) {
//		mIsAlive = false;
//		return;
//	}
//	mPosition += mVelocity * getGame()->getDeltaTime()->get();
//	mColor = ((mColor >> 8) << 8) | static_cast<unsigned int>(Lerp<float>::Calc(mLeftTime / mExitTime,  kAlphaMin, kAlphaMax));
//}
//void FadeParticle::Draw() {
//	Vec2 leftTop(-mRadius / 2.0f, mRadius / 2.0f);
//	getGame()->getCamera()->DrawSpriteRect({ leftTop + mPosition, mRadius, mRadius }, getGame()->getContainer()->getParticleData().fade.image, mColor);
//}