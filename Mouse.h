#pragma once
#include "MyMath.h"
#include <Novice.h>

// �}�E�X�{�^��
enum MouseButton {
	kMouseButtonLeft, // ���N���b�N
	kMouseButtonRight, // �E�N���b�N
	kMouseButtonWheel, // �z�C�[���{�^��
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

	// �L�[�������ꂽ��
	bool IsTrigger(MouseButton button) const {
		return mPreButtons[button] == false && mButtons[button] == true;
	}
	// �L�[�������Ă���Ƃ�
	bool IsPressed(MouseButton button) const {
		return mButtons[button] == true;
	}
	// �L�[�𗣂����Ƃ�
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

