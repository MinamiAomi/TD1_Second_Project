#pragma once
#include "ParticleComponent.h"


class SizeComponent :
	public ParticleComponent {

private:
	float mFinalSize = 0.0f;
	float mFirstSize = 0.0f;

public:
	SizeComponent(class Particle& part) : ParticleComponent(part) {}
	virtual ~SizeComponent() {}

	float getSize() const;
	
	void setFirstSize(float size) { mFirstSize = size; }
	void setFinalSize(float size) { mFinalSize = size; }

	virtual void Update();
};