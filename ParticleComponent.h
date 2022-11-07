#pragma once

class ParticleComponent {

private:
	class Particle& mParticle;

public:
	ParticleComponent(class Particle& part) : mParticle(part) {}
	virtual ~ParticleComponent() {}

	class Particle& getParticle() const { return mParticle; }

	
};