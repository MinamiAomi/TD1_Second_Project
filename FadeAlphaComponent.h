#pragma once
#include "ColorComponent.h"

class FadeAlphaComponent :
	public ColorComponent {

private:
	static constexpr float kAlphaMax = 0xFF;

public:
	FadeAlphaComponent(class Particle& part) : ColorComponent(part) {}
	~FadeAlphaComponent() {}

	void Update();
};