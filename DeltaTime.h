#pragma once
#include <time.h>

class DeltaTime {

private:
	clock_t nowTime;
	clock_t oldTime;
	float deltaTime = 0.0f;
	float speedRate = 1.0f;

public:
	static DeltaTime* GetInstance() {
		static DeltaTime instance;
		return &instance;
	}
	void CalcDeltaTime() {
		while (!((oldTime + 16) - clock() <= 0)) // 時間がたつまで止める
			;
		nowTime = clock();
		deltaTime = static_cast<float>(nowTime - oldTime) / CLOCKS_PER_SEC;
		deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime; // デルタタイムが増えすぎないように
		oldTime = nowTime;
	}
	float get() const { return deltaTime * speedRate; }
	
	void setDeltaSpeed(float ds) { speedRate = ds; }
	float getDeltaSpeed() const { return speedRate; }

private:
	DeltaTime() : nowTime(clock()), oldTime(nowTime) {}

};