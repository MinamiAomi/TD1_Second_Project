#pragma once
#include "NormalEffect.h"
#include "FadeStraightParticle.h"
#include "PlayerJumpEffect.h"

struct EffectData {
	NormalEffect::InitData normal;
	PlayerJumpEffect::InitData jumpEffect;
};

struct ParticleData {
	FadeStraightParticle::InitData fadeStraight;
	ImageData normal;
};