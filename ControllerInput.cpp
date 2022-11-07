#include "ControllerInput.h"
#include <Novice.h>

// メンバ関数の定義

Controller* Controller::GetInstance() {
	static Controller instance;
	return &instance;
}

bool Controller::IsUse(const State& data) const {
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
			if (IsUse(it)) {
				mIsInput = true;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::SetTriggerDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].triggerDeadZone = deadzone;
		return true;
	}
	return false;
}

bool Controller::SetRightStickDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].rightStickDeadZone = deadzone;
		return true;
	}
	return false;
}

bool Controller::SetLeftStickDeadZone(int index, int deadzone) {
	if (index < mData.size()) {
		mData[index].leftStickDeadZone = deadzone;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::IsTriggerButton(int index, Button button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case Controller::kLeftTrigger: // 左トリガー
				return (mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone) &&
					!(mData[index].preState.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
			
			case Controller::kRightTrigger: // 右トリガー
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

bool Controller::IsPressedButton(int index, Button button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case Controller::kLeftTrigger: // 左トリガー
				return (mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
			
			case Controller::kRightTrigger: // 右トリガー
				return (mData[index].state.Gamepad.bRightTrigger > mData[index].triggerDeadZone);
				
			default: // その他ボタン
				return (mData[index].state.Gamepad.wButtons & button);
		
			}
		}
	}
	return false;
}

bool Controller::IsReleaseButton(int index, Button button) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (button)
			{
			case Controller::kLeftTrigger: // 左トリガー
				return !(mData[index].state.Gamepad.bLeftTrigger > mData[index].triggerDeadZone) &&
					(mData[index].preState.Gamepad.bLeftTrigger > mData[index].triggerDeadZone);
				
			case Controller::kRightTrigger: // 右トリガー
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

bool Controller::IsStickDirection(int index, StickDirection direction) const {
	if (index < mData.size()) {
		if (mData[index].isConnect == true) {
			switch (direction)
			{
			case Controller::kLeftStickDirectionUp:
				return mData[index].state.Gamepad.sThumbLY >= mData[index].leftStickDeadZone ? true : false;

			case Controller::kLeftStickDirectionDown:
				return mData[index].state.Gamepad.sThumbLY <= -mData[index].leftStickDeadZone ? true : false;

			case Controller::kLeftStickDirectionRight:
				return mData[index].state.Gamepad.sThumbLX >= mData[index].leftStickDeadZone ? true : false;

			case Controller::kLeftStickDirectionLeft:
				return mData[index].state.Gamepad.sThumbLX <= -mData[index].leftStickDeadZone ? true : false;

			case Controller::kRightStickDirectionUp:
				return mData[index].state.Gamepad.sThumbLY >= mData[index].rightStickDeadZone ? true : false;

			case Controller::kRightStickDirectionDown:
				return mData[index].state.Gamepad.sThumbLY <= -mData[index].rightStickDeadZone ? true : false;

			case Controller::kRightStickDirectionRight:
				return mData[index].state.Gamepad.sThumbLX >= mData[index].rightStickDeadZone ? true : false;

			case Controller::kRightStickDirectionLeft:
				return mData[index].state.Gamepad.sThumbLX <= -mData[index].rightStickDeadZone ? true : false;
			default:
				break;
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Controller::GetRightTrigger(int index, int& out) const {
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

bool Controller::GetLeftTrigger(int index, int& out) const {
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

bool Controller::GetRightStick(int index, int& outx, int& outy) const {
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
bool Controller::GetRightStick(int index, float& outx, float& outy) const {
	int x, y;
	bool is = GetRightStick(index, x, y);
	outx = (float)x;
	outy = (float)y;
	return is;
}
bool Controller::GetRightStick(int index, StickMagnitude& out) const {
	return GetRightStick(index, out.x, out.y);
}

bool Controller::GetLeftStick(int index, int& outx, int& outy) const {
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
bool Controller::GetLeftStick(int index, float& outx, float& outy) const {
	int x, y;
	bool is = GetLeftStick(index, x, y);
	outx = (float)x;
	outy = (float)y;
	return is;
}
bool Controller::GetLeftStick(int index, StickMagnitude& out) const {
	return GetLeftStick(index, out.x, out.y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////