#pragma once
#include "GameObject.h"

class Particle :
	public GameObject {

private:
	bool mIsAlive = false;
	float mLeftTime = 0.0f;		// ‚Ì‚±‚èŽžŠÔ
	float mExitTime = 0.0f;

public:
	bool IsAlive() const { return mIsAlive; }
	void setAlive(bool is) { mIsAlive = is; }
	float getLeftTime() const { return mLeftTime; }
	void setLeftTime(float leT) { mLeftTime = leT; };
	float getExitTime() const { return mExitTime; }
	void setExitTime(float exT) { mExitTime = exT; };

	float TimeRatio() { return mLeftTime / mExitTime; }

public:
	Particle() : GameObject(nullptr) {}
	Particle(class Game* game) : GameObject(game) {}
	virtual ~Particle() {}


	void TimeUpdate();
};