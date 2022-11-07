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

	// キー入力を受け取る
	void SetState() {
		mIsInput = false;
		memcpy(mPreKeys, mKeys, kKeyDataNum);
		Novice::GetHitKeyStateAll(mKeys);
		for (int i = 0; i < kKeyDataNum; i++) {
			mIsInput |= (mKeys[i] != 0);
		}
	}

	// キーが押された時
	bool IsTrigger(char keycode) const {
		return mPreKeys[keycode] == 0 && mKeys[keycode] != 0;
	}
	// キーを押しているとき
	bool IsPressed(char keycode) const {
		return mKeys[keycode] != 0;
	}
	// キーを離したとき
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

