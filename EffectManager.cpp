#include "EffectManager.h"
#include "Effect.h"
#include "NormalEffect.h"
#include "Func.h"

EffectManager::EffectManager(class Game* game) :
	GameObject(game) {
	mEffects[kNormalEffect] = mNormalEffectPtr = new NormalEffect(game);
}

EffectManager::~EffectManager() {
	mNormalEffectPtr = nullptr;
	for (auto effect : mEffects) {
		Func::SafeDelete(effect);
	}
}

void EffectManager::Create() {
	
}

void EffectManager::Update() {
	for (auto effect : mEffects) {
		effect->Update();
	}
}