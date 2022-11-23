#include "Fade.h"
#include <Novice.h>
#include "Game.h"
#include "DeltaTime.h"
#include "Easing.h"
void Fade::Start() {
	if (mIsLight == false && mIsDarken == false) {
		mIsDarken = true;
		lerp.Set(0.0f, time, 0.0f, (float)0xFF);
	}
}
void Fade::Update() {

	if (mIsLight == true || mIsDarken == true) {
		if (mIsLight == true) {
			lerp.Decrement(DELTA_TIME->get());
			lerp.ParamClamp();
			if (lerp.IsStart()) {
				mIsDarken = false;
				mIsLight = false;
			}
		}
		if (mIsDarken == true) {
			lerp.Increment(DELTA_TIME->get());
			lerp.ParamClamp();
			if (lerp.IsEnd()) {
				mIsDarken = false;
				mIsLight = true;
			}
		}
		color = 0 | (unsigned int)lerp.Calc(Easing::EaseInSine);
	}
}

void Fade::Draw() {
	if (mIsLight == true || mIsDarken == true) {
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, color, kFillModeSolid);
	}
}