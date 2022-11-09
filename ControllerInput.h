#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>

#pragma comment (lib, "xinput.lib")

// コントローラーボタン
enum ControllerButton {
	kControllerButtonUp			= 0x0001,		// 上
	kControllerButtonDown		= 0x0002,		// 下
	kControllerButtonLeft		= 0x0004,		// 左
	kControllerButtonRight		= 0x0008,		// 右
	kControllerButtonStart		= 0x0010,		// メニュー
	kControllerButtonBack		= 0x0020,		// ビュー
	kControllerLeftThumb		= 0x0040,		// L3
	kControllerRightThumb		= 0x0080,		// R3
	kControllerLeftShoulder		= 0x0100,		// L1
	kControllerRightShoulder	= 0x0200,		// R1
	kControllerButtonA			= 0x1000,		// A
	kControllerButtonB			= 0x2000,		// B
	kControllerButtonX			= 0x4000,		// X
	kControllerButtonY			= 0x8000,		// Y
	kControllerLeftTrigger		= 0x000F0000,	// L2 (適当な数字を割り当て)
	kControllerRightTrigger		= 0x00FF0000,	// R2 (適当な数字を割り当て)
};

// スティックの向き
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

// Xinputコントローラー
class Controller {

public:
	
	struct StickMagnitude {
		int x;
		int y;
	};

private:
	struct State {
		bool isConnect = false;				// 接続できたか
		XINPUT_STATE state = {};			// 現在の入力状態
		XINPUT_STATE preState = {};		// 前回の入力状態
		BYTE triggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;		// トリガーのデッドゾーン
		SHORT leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;	// 左スティックのデッドゾーン
		SHORT rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;	// 右スティックのデッドゾーン
	};

public:
	static constexpr int kMaxConnectionNum = 4;

private:
	std::vector<State> mData;
	bool mIsInput = false;

public:

	// シングルトンインスタンスの取得
	static Controller* GetInstance();

	/// <summary>
	/// コントローラーを追加する
	/// </summary>
	/// <returns> 既に４つ接続されている場合 false</returns>
	bool Add() {
		if (mData.size() < kMaxConnectionNum) {
			mData.emplace_back();
			return true;
		}
		return false;
	}

	bool isUse(const State& data) const;

	/// <summary>
	/// すべてのコントローラーの状態をセットする
	/// </summary>
	/// <returns>接続数</returns>
	void SetState();

	/// <summary>
	/// 現在使われているか
	/// </summary>
	bool isInput() const { return mIsInput; }

	int getConnectnNum() const  { return (int)mData.size(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// トリガーのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool setTriggerDeadZone(int index, int deadzone);

	/// <summary>
	/// 右スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	bool setRightStickDeadZone(int index, int deadzone);

	/// <summary>
	/// 左スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	bool setLeftStickDeadZone(int index, int deadzone);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// ボタンが押された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool isTrigger(int index, ControllerButton button) const;

	/// <summary>
	/// ボタンが押されている時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool isPressed(int index, ControllerButton button) const;

	/// <summary>
	/// ボタンが離された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool isRelease(int index, ControllerButton button) const;

	/// <summary>
	/// スティックが指定の向きに倒された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="direction">スティック向き</param>
	/// <returns></returns>
	bool isStickDirection(int index, StickDirection direction) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool getRightTrigger(int index, int* out) const;

	/// <summary>
	/// 左トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool getLeftTrigger(int index, int* out) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	bool getRightStick(int index, int* outx, int* outy) const;
	bool getRightStick(int index, float* outx, float* outy) const;
	bool getRightStick(int index, StickMagnitude* out) const;

	bool getRightStickNoDeadZone(int index, int* outx, int* outy) const;
	bool getRightStickNoDeadZone(int index, float* outx, float* outy) const;

	/// <summary>
	/// 左スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	bool getLeftStick(int index, int* outx, int* outy) const;
	bool getLeftStick(int index, float* outx, float* outy) const;
	bool getLeftStick(int index, StickMagnitude* out) const;

	bool getLeftStickNoDeadZone(int index, int* outx, int* outy) const;
	bool getLeftStickNoDeadZone(int index, float* outx, float* outy) const;
private:

	Controller() { mData.emplace_back(); }
	~Controller() = default;
	Controller(const Controller&) = delete;
	const Controller& operator=(const Controller&) = delete;

};