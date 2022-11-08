#include "ControllerInput.h"
#include <Novice.h>

// メンバ関数の定義

Controller* Controller::GetInstance() {
	static Controller instance;
	return &instance;
}

bool Controller::isUse(const State& data) const {
	return data.state.Gamepad.wButtons != 0 ||
		data.state.Gamepad.bRightTrigger != 0 ||
		data.state.Gamepad.bLeftTrigger != 0 ||
		(data.state.Gamepad.sThumbRX >= data.rightStickDeadZone || data.state.Gamepad.sThumbRX <= -data.rightStickDeadZone) ||
		(data.state.Gamepad.sThumbRY >= data.rightStickDeadZone || data.state.Gamepad.sThumbRY <= -data.rightStickDeadZone) ||
		(data.state.Gamepad.sThumbLX >= data.leftStickDeadZone ||  data.state.Gamepad.sThumbLX <= -data.leftStickDeadZone) ||
		(data.state.Gamepad.sThumbLY >= data.leftStickDeadZone ||  data.state.Gamepad.sThumbLY <= -data.leftStickDeadZone);
}

void Controller::SetState(){
	int n = 0;
	mIsInput = false;
	for (auto& it : mData) {
		it.preState = it.state;
		it.isConnect =  XInputGetState(n++, &it.state) == ERROR_SUCCESS;
		if (it.isConnect == true) {
			if (isUse(it)) {
				mIsInput = true;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::setTriggerDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].triggerDeadZone = deadzone;
		return true;
	}
	return false;
}

bool Controller::setRightStickDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].rightStickDeadZone = deadzone;
		return true;
	}
	return false;
}

bool Controller::setLeftStickDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].leftStickDeadZone = deadzone;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::isTrigger(int index, ControllerButton button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case kControllerLeftTrigger: // 左トリガー
				return (mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone) &&
					!(mData[index].preState.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
			
			case kControllerRightTrigger: // 右トリガー
				return (mData[index].state.Gamepad.bRightTrigger > mData[index].triggerDeadZone) &&
					!(mData[index].preState.Gamepad.bRightTrigger > mData[index].triggerDeadZone);

			default: // その他ボタン
				return (mData[index].state.Gamepad.wButtons & button) &&
					!(mData[index].preState.Gamepad.wButtons & button);
				
			}
		}
	}
	return false;
}

bool Controller::isPressed(int index, ControllerButton button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case kControllerLeftTrigger: // 左トリガー
				return (mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
			
			case kControllerRightTrigger: // 右トリガー
				return (mData[index].state.Gamepad.bRightTrigger > mData[index].triggerDeadZone);
				
			default: // その他ボタン
				return (mData[index].state.Gamepad.wButtons & button);
		
			}
		}
	}
	return false;
}

bool Controller::isRelease(int index, ControllerButton button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case kControllerLeftTrigger: // 左トリガー
				return !(mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone) &&
					(mData[index].preState.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
				
			case kControllerRightTrigger: // 右トリガー
				return !(mData[index].state.Gamepad.bRightTrigger > mData[index].triggerDeadZone) &&
					(mData[index].preState.Gamepad.bRightTrigger > mData[index].triggerDeadZone);
				
			default: // その他ボタン
				return !(mData[index].state.Gamepad.wButtons & button) &&
					(mData[index].preState.Gamepad.wButtons & button);
				
			}
		}
	}
	return false;
}

bool Controller::isStickDirection(int index, StickDirection direction) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (direction)
			{
			case kLeftStickDirectionUp:
				return mData[index].state.Gamepad.sThumbLY >= mData[index].leftStickDeadZone ? true : false;

			case kLeftStickDirectionDown:
				return mData[index].state.Gamepad.sThumbLY <= -mData[index].leftStickDeadZone ? true : false;

			case kLeftStickDirectionRight:
				return mData[index].state.Gamepad.sThumbLX >= mData[index].leftStickDeadZone ? true : false;

			case kLeftStickDirectionLeft:
				return mData[index].state.Gamepad.sThumbLX <= -mData[index].leftStickDeadZone ? true : false;

			case kRightStickDirectionUp:
				return mData[index].state.Gamepad.sThumbLY >= mData[index].rightStickDeadZone ? true : false;

			case kRightStickDirectionDown:
				return mData[index].state.Gamepad.sThumbLY <= -mData[index].rightStickDeadZone ? true : false;

			case kRightStickDirectionRight:
				return mData[index].state.Gamepad.sThumbLX >= mData[index].rightStickDeadZone ? true : false;

			case kRightStickDirectionLeft:
				return mData[index].state.Gamepad.sThumbLX <= -mData[index].rightStickDeadZone ? true : false;
			default:
				break;
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::getRightTrigger(int index, int& out) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			if (mData[index].state.Gamepad.bRightTrigger > mData[index].triggerDeadZone) {
				out = mData[index].state.Gamepad.bRightTrigger;
			} else {
				out = 0;
			}
			return true;
		}
	}
	return false;
}

bool Controller::getLeftTrigger(int index, int& out) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			if (mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone){
				out = mData[index].state.Gamepad.bLeftTrigger;
			}
			else {
				out = 0;
			}
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::getRightStick(int index, int& outx, int& outy) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			if ((mData[index].state.Gamepad.sThumbRX <  mData[index].rightStickDeadZone &&
				mData[index].state.Gamepad.sThumbRX > -mData[index].rightStickDeadZone)) {
				outx = 0;
			}
			else {
				outx = mData[index].state.Gamepad.sThumbRX;
			}
			if ((mData[index].state.Gamepad.sThumbRY <  mData[index].rightStickDeadZone &&
				mData[index].state.Gamepad.sThumbRY > -mData[index].rightStickDeadZone)) {
				outy = 0;
			}
			else {
				outy = mData[index].state.Gamepad.sThumbRY;
			}
			return true;
		}
	}
	return false;
}
bool Controller::getRightStick(int index, float& outx, float& outy) const {
	int x, y;
	bool is = getRightStick(index, x, y);
	outx = (float)x;
	outy = (float)y;
	return is;
}
bool Controller::getRightStick(int index, StickMagnitude& out) const {
	return getRightStick(index, out.x, out.y);
}

bool Controller::getLeftStick(int index, int& outx, int& outy) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			if ((mData[index].state.Gamepad.sThumbLX <  mData[index].leftStickDeadZone &&
				mData[index].state.Gamepad.sThumbLX > -mData[index].leftStickDeadZone)) {
				outx = 0;
			}
			else {
				outx = mData[index].state.Gamepad.sThumbLX;
			}
			if ((mData[index].state.Gamepad.sThumbLY <  mData[index].leftStickDeadZone &&
				mData[index].state.Gamepad.sThumbLY > -mData[index].leftStickDeadZone)) {
				outy = 0;
			}
			else {
				outy = mData[index].state.Gamepad.sThumbLY;
			}
			return true;
		}
	}
	return false;
}
bool Controller::getLeftStick(int index, float& outx, float& outy) const {
	int x, y;
	bool is = getLeftStick(index, x, y);
	outx = (float)x;
	outy = (float)y;
	return is;
}
bool Controller::getLeftStick(int index, StickMagnitude& out) const {
	return getLeftStick(index, out.x, out.y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////