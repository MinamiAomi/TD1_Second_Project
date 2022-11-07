#pragma once
#include "Effect.h"
#include "Array.h"
#include "FadeStraightParticle.h"
#include <vector>

class NormalEffect :
	public Effect {

public:
	struct InitData	{
		int particleNum;
	};

private:
	DynamicArray<FadeStraightParticle> mParticles;

public:
	NormalEffect(class Game* game);
	~NormalEffect();

	void Create(int particlenum, const Vec2& pos, float speed, float firstsize, float finalsize, float theta, float time);
	void Update();
	void Draw();
};