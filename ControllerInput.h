#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>

#pragma comment (lib, "xinput.lib")


// Xinput�R���g���[���[
class Controller {

public:
	// �{�^���R�[�h
	enum Button {
		kButtonUp		= 0x0001,		// ��
		kButtonDown		= 0x0002,		// ��
		kButtonLeft		= 0x0004,		// ��
		kButtonRight	= 0x0008,		// �E
		kButtonStart	= 0x0010,		// ���j���[
		kButtonBack		= 0x0020,		// �r���[
		kLeftThumb		= 0x0040,		// L3
		kRightThumb		= 0x0080,		// R3
		kLeftShoulder	= 0x0100,		// L1
		kRightShoulder	= 0x0200,		// R1
		kButtonA		= 0x1000,		// A
		kButtonB		= 0x2000,		// B
		kButtonX		= 0x4000,		// X
		kButtonY		= 0x8000,		// Y
		kLeftTrigger	= 0x000F0000,	// L2 (�K���Ȑ��������蓖��)
		kRightTrigger	= 0x00FF0000,	// R2 (�K���Ȑ��������蓖��)
	};

	// �X�e�B�b�N�̌���
	enum StickDirection {
		kLeftStickDirectionUp,			// LEFT STICK DIRECTION UP
		kLeftStickDirectionDown,		// LEFT STICK DIRECTION DOWN
		kLeftStickDirectionRight,		// LEFT STICK DIRECTION RIGHT
		kLeftStickDirectionLeft,		// LEFT STICK DIRECTION LEFT
		kRightStickDirectionUp,			// RIGHT STICK DIRECTION UP
		kRightStickDirectionDown,		// RIGHT STICK DIRECTION DOWN
		kRightStickDirectionRight,		// RIGHT STICK DIRECTION RIGHT
		kRightStickDirectionLeft		// RIGHT STICK DIRECTION LEFT
	};

	struct StickMagnitude {
		int x;
		int y;
	};

private:
	struct State {
		bool isConnect = false;				// �ڑ��ł�����
		XINPUT_STATE state = {};			// ���݂̓��͏��
		XINPUT_STATE preState = {};		// �O��̓��͏��
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;		// �g���K�[�̃f�b�h�]�[��
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;	// ���X�e�B�b�N�̃f�b�h�]�[��
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// �E�X�e�B�b�N�̃f�b�h�]�[��
	};

public:
	static constexpr int kMaxConnectionNum = 4;

private:
	std::vector<State> mData;
	bool mIsInput = false;

public:

	// �V���O���g���C���X�^���X�̎擾
	static Controller* GetInstance();

	/// <summary>
	/// �R���g���[���[��ǉ�����
	/// </summary>
	/// <returns> ���ɂS�ڑ�����Ă���ꍇ false</returns>
	bool Add() {
		if (mData.size() < kMaxConnectionNum) {
			mData.emplace_back();
			return true;
		}
		return false;
	}

	bool IsUse(const State& data) const;

	/// <summary>
	/// ���ׂẴR���g���[���[�̏�Ԃ��Z�b�g����
	/// </summary>
	/// <returns>�ڑ���</returns>
	void SetState();

	/// <summary>
	/// ���ݎg���Ă��邩
	/// </summary>
	bool IsInput() const { return mIsInput; }

	int GetConnectnNum() const  { return (int)mData.size(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �g���K�[�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`255</param>
	/// <returns>�����@or�@���s</returns>
	bool SetTriggerDeadZone(int index, int deadzone);

	/// <summary>
	/// �E�X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768</param>
	/// <returns>�����@or�@���s</returns>
	bool SetRightStickDeadZone(int index, int deadzone);

	/// <summary>
	/// ���X�e�B�b�N�̃f�b�h�]�[����ύX����
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="deadzone">�f�b�h�]�[���@�F�@0�`32768</param>
	/// <returns>�����@or�@���s</returns>
	bool SetLeftStickDeadZone(int index, int deadzone);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsTriggerButton(int index, Button button) const;

	/// <summary>
	/// �{�^����������Ă��鎞
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsPressedButton(int index, Button button) const;

	/// <summary>
	/// �{�^���������ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="button">�{�^���ԍ�</param>
	/// <returns></returns>
	bool IsReleaseButton(int index, Button button) const;

	/// <summary>
	/// �X�e�B�b�N���w��̌����ɓ|���ꂽ��
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="direction">�X�e�B�b�N����</param>
	/// <returns></returns>
	bool IsStickDirection(int index, StickDirection direction) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �E�g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	bool GetRightTrigger(int index, int& out) const;

	/// <summary>
	/// ���g���K�[
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="out">0�`255</param>
	/// <returns>�����@or�@���s</returns>
	bool GetLeftTrigger(int index, int& out) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// �E�X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	/// <returns>�����@or�@���s</returns>
	bool GetRightStick(int index, int& outx, int& outy) const;
	bool GetRightStick(int index, float& outx, float& outy) const;
	bool GetRightStick(int index, StickMagnitude& out) const;

	/// <summary>
	/// ���X�e�B�b�N
	/// </summary>
	/// <param name="number">�R���g���[���[�ԍ�</param>
	/// <param name="outx">X��</param>
	/// <param name="outy">Y��</param>
	/// <returns>�����@or�@���s</returns>
	bool GetLeftStick(int index, int& outx, int& outy) const;
	bool GetLeftStick(int index, float& outx, float& outy) const;
	bool GetLeftStick(int index, StickMagnitude& out) const;

private:

	Controller() { mData.emplace_back(); }
	~Controller() = default;
	Controller(const Controller&) = delete;
	const Controller& operator=(const Controller&) = delete;

};