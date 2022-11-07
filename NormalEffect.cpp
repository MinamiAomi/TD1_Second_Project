#include "NormalEffect.h"
#include "Game.h"
#include "Container.h"
#include "Func.h"

NormalEffect::NormalEffect(class Game* game) :
	Effect(game) {
}
NormalEffect::~NormalEffect() {

}

void NormalEffect::Create(int particlenum, const Vec2& pos, float speed, float firstsize, float finalsize, float theta, float time) {
	
	mParticles.New(particlenum);
	for (auto& it : mParticles) {
		it.ComponentCreate(getGame());
	}
	

	float x = (float)SinCosTable::kDegreeMax / (float)mParticles.size();
	DynamicArray<Vec2> vel(mParticles.size());
	DynamicArray<unsigned int> col(mParticles.size());
	for (int i = 0; i < mParticles.size(); i++) {
		float t = i * x;
		float c = SinCosTable::getInstance().getCos(t);
		float s = SinCosTable::getInstance().getSin(t);
		vel[i] = { c, s };
		col[i] = Func::HSVAToRGBA(t, (float)0xFF, (float)0xFF, 0xFF);
	}

	
	Matrix33 mat;
	mat.MultiplyScaling(speed);
	mat.MultiplyRotation(theta);

	for (int i = 0; i < mParticles.size(); i++) {
		vel[i] = vel[i] * mat;
		mParticles[i].Create(pos, vel[i], firstsize, finalsize, col[i], time);
	}

}

void NormalEffect::Update() {
	bool allAlive = false;
	for (auto& it : mParticles) {
		if (it.IsAlive() == true) {
			it.Update();
			allAlive = true;
		}
	}
	if (allAlive == false && mParticles.size() != 0) {
		mParticles.Delete();
	}
}
void NormalEffect::Draw() {
	Novice::SetBlendMode(kBlendModeAdd);
	for (auto& it : mParticles) {
		if (it.IsAlive() == true) {
			it.Draw();
		}
	}
	Novice::SetBlendMode(kBlendModeNormal);
}