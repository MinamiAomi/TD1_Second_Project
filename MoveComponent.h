#pragma once
#include "ParticleComponent.h"
#include "Vector2Math.h"

class MoveComponent :
	public ParticleComponent {

private:
	Vec2 mPosition;
	Vec2 mVelocity;

public:
	MoveComponent(class Particle& part) : ParticleComponent(part) {}
	virtual ~MoveComponent() {}

	const Vec2& getPosition() const { return mPosition; }
	void setPosition(const Vec2& pos) { mPosition = pos; }

	void setVelocity(const Vec2& vel) { mVelocity = vel; }
	const Vec2& getVelocity() const { return mVelocity; }
	virtual void Update(float deltaTime) { mPosition += mVelocity * deltaTime; }
};