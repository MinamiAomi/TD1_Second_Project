#include "PlayerJumpEffect.h"
#include "Game.h"
#include "PlayerMain.h"
#include "Container.h"
#include "Camera.h"
#include "DeltaTime.h"


PlayerJumpEffect::PlayerJumpEffect(Game* game) :
	GameObject(game)
{
}

PlayerJumpEffect::~PlayerJumpEffect()
{
}

void PlayerJumpEffect::Create()
{
	mIsAlive = false;

	mParticles.New(CONTAINER->getEffectData().jumpEffect.particleNum);
}

void PlayerJumpEffect::Spawn(const Vec2& spawnPos)
{
	mIsAlive = true;
	mEmitterPos = spawnPos;
	mLeftTime = CONTAINER->getEffectData().jumpEffect.exitTime;

	float x = 2.0f * Math::Pi / mParticles.size();
	float spe = CONTAINER->getEffectData().jumpEffect.pariticleSpeed;
	for (int i = 0; i < mParticles.size(); i++) {
		mParticles[i].pos = mEmitterPos;
		mParticles[i].vel = Vec2::MakeDirection(x * i) * spe;
	}

}

void PlayerJumpEffect::Update()
{
	float dt = DELTA_TIME->get();
	mLeftTime -= dt;
	for (auto& it : mParticles) {
		it.pos += it.vel * dt;
	}
	if (mLeftTime <= 0.0f) {
		mIsAlive = false;
	}
}

void PlayerJumpEffect::Draw()
{
	Quad quad = CONTAINER->getEffectData().jumpEffect.imageQuad;
	for (auto& it : mParticles) {
		CAMERA->DrawQuad(quad.TransForm(Matrix33::MakeScaling(2.0f,1.0f) * Matrix33::MakeTranslation(it.pos)), CONTAINER->getParticleData().normal);
	}
}
