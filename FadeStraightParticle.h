#pragma once
#include "Particle.h"
#include "ImageData.h"

class FadeStraightParticle :
	public Particle {

public:

public:
	struct InitData	{
		ImageData image;
	};

private:

	class SizeComponent* mSizeComponent;
	class MoveComponent* mMoveComponent;
	class ColorComponent* mColorComponent;

public:
	FadeStraightParticle() : Particle(), mSizeComponent(nullptr), mMoveComponent(nullptr), mColorComponent(nullptr) {}
	FadeStraightParticle(class Game* game);
	~FadeStraightParticle();

	void ComponentCreate(class Game* game);

	void Create(const class Vec2& pos, const class Vec2& vel, float firstsize, float finalsize, unsigned int col, float exitT);
	
	void Update();
	void Draw();
};




//class FadeParticle :
//	public GameObject {
//
//public:
//	struct InitData	{
//		ImageData image;
//	};
//
//private:
//	static constexpr float kAlphaMax = 0xFF;
//	static constexpr float kAlphaMin = 0x00;
//
//	bool mIsAlive = false;
//	Vec2 mPosition;				// à íu
//	Vec2 mVelocity;				// ë¨ìx
//	float mRadius = 0.0f;		// ëÂÇ´Ç≥
//	unsigned int mColor = 0;	// êF
//	float mLeftTime = 0.0f;		// ÇÃÇ±ÇËéûä‘
//	float mExitTime = 0.0f;
//
//
//
//public:
//	FadeParticle() : GameObject(nullptr) {}
//	~FadeParticle() {}
//
//	bool IsAlive() const { return mIsAlive; }
//
//	void Create(const Vec2& pos, const Vec2& vel, float rad, unsigned int col, float exitT) {
//		mIsAlive = true;
//		mPosition = pos;
//		mVelocity = vel;
//		mRadius = rad;
//		mColor = col;
//		mLeftTime = exitT;
//		mExitTime = exitT;
//	}
//
//
//	void Update();
//	void Draw();
//};