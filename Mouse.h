#pragma once
#include "MyMath.h"
#include <Novice.h>

// マウスボタン
enum MouseButton {
	kMouseButtonLeft, // 左クリック
	kMouseButtonRight, // 右クリック
	kMouseButtonWheel, // ホイールボタン
	kMouseButton3,
	kMouseButton4,
	kMouseButton5,
	kMouseButton6,

	kMouseButtonNum
};
class Mouse
{
private:

	bool mButtons[kMouseButtonNum] = {};
	bool mPreButtons[kMouseButtonNum] = {};
	Vec2 mPreMousePosition;
	Vec2 mMousePosition;
	int mWheel = 0;

public:

	static Mouse* GetInstance() {
		static Mouse instance;
		return &instance;
	}

	void SetState(const Matrix33& inverse) {
		int x = 0, y = 0;
		Novice::GetMousePosition(&x, &y);
		Vec2 tmp((float)x, (float)y);
		mPreMousePosition = mMousePosition;
		mMousePosition = tmp * inverse;
		mWheel = Novice::GetWheel();
		std::copy(std::begin(mButtons), std::end(mButtons), mPreButtons);
		for (int i = 0; i < kMouseButtonNum; i++) {
			 mButtons[i] = (bool)Novice::IsPressMouse(i);
		}
	}

	const Vec2& getPosition() const { return mMousePosition; }
	const Vec2& getPrePosition() const { return mPreMousePosition; }
	Vec2 getVector() const { return mMousePosition - mPreMousePosition; }

	// キーが押された時
	bool IsTrigger(MouseButton button) const {
		return mPreButtons[button] == false && mButtons[button] == true;
	}
	// キーを押しているとき
	bool IsPressed(MouseButton button) const {
		return mButtons[button] == true;
	}
	// キーを離したとき
	bool IsRelease(MouseButton button) const {
		return mPreButtons[button] == true && mButtons[button] == false;
	}

	float getWheel() const { return static_cast<float>(mWheel); }

private:
	Mouse() = default;
	~Mouse() = default;
	Mouse(const Mouse&) = delete;
	const Mouse& operator=(const Mouse&) = delete;

};

