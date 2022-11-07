#include "SizeComponent.h"
#include "Particle.h"
#include "Lerp.h"

float SizeComponent::getSize() const { return Lerp<float>::Calc(1.0f - getParticle().TimeRatio(), mFirstSize, mFinalSize); }

void SizeComponent::Update() {
}