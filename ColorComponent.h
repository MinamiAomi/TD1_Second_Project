#pragma once
#include "ParticleComponent.h"

class ColorComponent :
	public ParticleComponent
{
private:
	unsigned int mColor;


public:
	ColorComponent(class Particle& part) : ParticleComponent(part), mColor(0) {}
	virtual ~ColorComponent() {}

	unsigned int getColor() const { return mColor; }
	void setColor(unsigned int color) { mColor = color; }	

	virtual void Update() {}
};

