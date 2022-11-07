#pragma once
#include <Novice.h>

class Key {

private:
	static constexpr int kKeyDataNum = 256;

	char mKeys[kKeyDataNum] = {};
	char mPreKeys[kKeyDataNum] = {};
	bool mIsInput = false;

public:

	static Key* GetInstance() {
		static Key instance;
		return &instance;
	}

	// �L�[���͂��󂯎��
	void SetState() {
		mIsInput = false;
		memcpy(mPreKeys, mKeys, kKeyDataNum);
		Novice::GetHitKeyStateAll(mKeys);
		for (int i = 0; i < kKeyDataNum; i++) {
			mIsInput |= (mKeys[i] != 0);
		}
	}

	// �L�[�������ꂽ��
	bool IsTrigger(char keycode) const {
		return mPreKeys[keycode] == 0 && mKeys[keycode] != 0;
	}
	// �L�[�������Ă���Ƃ�
	bool IsPressed(char keycode) const {
		return mKeys[keycode] != 0;
	}
	// �L�[�𗣂����Ƃ�
	bool IsRelease(char keycode) const {
		return mPreKeys[keycode] != 0 && mKeys[keycode] == 0;
	}

	bool IsInput() const {
		return mIsInput;
	}

private:
	Key() = default;
	~Key() = default;
	Key(const Key&) = delete;
	const Key& operator=(const Key&) = delete;
};

