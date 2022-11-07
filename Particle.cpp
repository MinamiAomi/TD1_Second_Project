#include "Particle.h"
#include "Game.h"
#include "DeltaTime.h"

void Particle::TimeUpdate() {
	mLeftTime += -getGame()->getDeltaTime()->get();
	if (mLeftTime <= 0) {
		mIsAlive = false;
	}
}