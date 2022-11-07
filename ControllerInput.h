#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <vector>

#pragma comment (lib, "xinput.lib")


// Xinputコントローラー
class Controller {

public:
	// ボタンコード
	enum Button {
		kButtonUp		= 0x0001,		// 上
		kButtonDown		= 0x0002,		// 下
		kButtonLeft		= 0x0004,		// 左
		kButtonRight	= 0x0008,		// 右
		kButtonStart	= 0x0010,		// メニュー
		kButtonBack		= 0x0020,		// ビュー
		kLeftThumb		= 0x0040,		// L3
		kRightThumb		= 0x0080,		// R3
		kLeftShoulder	= 0x0100,		// L1
		kRightShoulder	= 0x0200,		// R1
		kButtonA		= 0x1000,		// A
		kButtonB		= 0x2000,		// B
		kButtonX		= 0x4000,		// X
		kButtonY		= 0x8000,		// Y
		kLeftTrigger	= 0x000F0000,	// L2 (適当な数字を割り当て)
		kRightTrigger	= 0x00FF0000,	// R2 (適当な数字を割り当て)
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

	bool IsUse(const State& data) const;

	/// <summary>
	/// すべてのコントローラーの状態をセットする
	/// </summary>
	/// <returns>接続数</returns>
	void SetState();

	/// <summary>
	/// 現在使われているか
	/// </summary>
	bool IsInput() const { return mIsInput; }

	int GetConnectnNum() const  { return (int)mData.size(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// トリガーのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool SetTriggerDeadZone(int index, int deadzone);

	/// <summary>
	/// 右スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	bool SetRightStickDeadZone(int index, int deadzone);

	/// <summary>
	/// 左スティックのデッドゾーンを変更する
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="deadzone">デッドゾーン　：　0～32768</param>
	/// <returns>成功　or　失敗</returns>
	bool SetLeftStickDeadZone(int index, int deadzone);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// ボタンが押された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsTriggerButton(int index, Button button) const;

	/// <summary>
	/// ボタンが押されている時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsPressedButton(int index, Button button) const;

	/// <summary>
	/// ボタンが離された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="button">ボタン番号</param>
	/// <returns></returns>
	bool IsReleaseButton(int index, Button button) const;

	/// <summary>
	/// スティックが指定の向きに倒された時
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="direction">スティック向き</param>
	/// <returns></returns>
	bool IsStickDirection(int index, StickDirection direction) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool GetRightTrigger(int index, int& out) const;

	/// <summary>
	/// 左トリガー
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="out">0～255</param>
	/// <returns>成功　or　失敗</returns>
	bool GetLeftTrigger(int index, int& out) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// 右スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	bool GetRightStick(int index, int& outx, int& outy) const;
	bool GetRightStick(int index, float& outx, float& outy) const;
	bool GetRightStick(int index, StickMagnitude& out) const;

	/// <summary>
	/// 左スティック
	/// </summary>
	/// <param name="number">コントローラー番号</param>
	/// <param name="outx">X軸</param>
	/// <param name="outy">Y軸</param>
	/// <returns>成功　or　失敗</returns>
	bool GetLeftStick(int index, int& outx, int& outy) const;
	bool GetLeftStick(int index, float& outx, float& outy) const;
	bool GetLeftStick(int index, StickMagnitude& out) const;

private:

	Controller() { mData.emplace_back(); }
	~Controller() = default;
	Controller(const Controller&) = delete;
	const Controller& operator=(const Controller&) = delete;

};