#include "FadeAlphaComponent.h"
#include "Particle.h"
#include "Easing.h"
void FadeAlphaComponent::Update() {
	setColor((getColor() >> 8) << 8 | static_cast<unsigned int>(getParticle().TimeRatio() * kAlphaMax));
}