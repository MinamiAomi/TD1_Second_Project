#include "PlayerMain.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "InputDevice.h"
#include "DeltaTime.h"

#include "Debug.h"

Player::Player(class Game* game) : 
	GameObject(game)
{
	mJumpEffect.resize(CONTAINER->getPlayerData().jumpEffectNum, game);
}


Player::~Player() {
	
}


void Player::Create() {

	mPosition = CONTAINER->getPlayerData().position;
	mVelocity.SetZero();

	mSize = CONTAINER->getPlayerData().size;
	mImageRect = Rect::CreateCenter(mSize);
	mMapColliderRect = Rect::CreateCenter(CONTAINER->getPlayerData().mapColliderSize);

	for (auto& it : mJumpEffect) {
		it.Create();
	}
}

void Player::Update() {

	this->Input();

	Move();
	StateUpdate();
	for (auto& it : mJumpEffect) {
		if (it.getIsAlive()) {
			it.Update();
		}
	}
}

void Player::Draw() {



	for (auto& it : mJumpEffect) {
		if (it.getIsAlive()) {
			it.Draw();
		}
	}

	if (mIsRightDirection) {
	CAMERA->DrawSpriteRect(mImageRect.Translation(mPosition), CONTAINER->getPlayerData().image);
	}
	else {
		CAMERA->DrawQuad(ToQuad(mImageRect.Translation(mPosition)).SideFlip(), CONTAINER->getPlayerData().image);
	}
	CAMERA->DrawRect(mMapColliderRect.Translation(mPosition), 0xFF0000FF, kFillModeWireFrame);
}

void Player::StateUpdate() {
	Rect rect = mMapColliderRect.Translation(mPosition);
	mIsGround = MAP->isGround(rect);
	mIsCeiling = MAP->isCeiling(rect);
	mIsLeftonWall = MAP->isWallonLeft(rect);
	mIsRightonWall = MAP->isWallonRight(rect);
	if (mIsGround) {
		mIsJump = false;
		mIsDoubleJump = false;
		mAcceleration.y = 0;
	}
	if (mIsCeiling) {
		mAcceleration.y = 0;
	}
	if (mIsLeftonWall && mAcceleration.x < 0) {
		mAcceleration.x = 0;
	}
	if (mIsRightonWall && mAcceleration.x > 0) {
		mAcceleration.x = 0;
	}
	if (mIsDushAttak) {
		if (mPosition.Distance(mDushAttakStartPosition) > CONTAINER->getPlayerData().dushAttakDistance && mIsDushAttak || mIsMapCollsion) {
			mIsDushAttak = false;
			if (mIsMapCollsion == false) {
				mPosition = mDushAttakStartPosition + mDushAttakDirection.Magnituded(CONTAINER->getPlayerData().dushAttakDistance);
			}
			mAcceleration.SetZero();
			mDushCoolTime = CONTAINER->getPlayerData().dushAttakCoolTime;
		}
	}
	if (mAcceleration.x > 0) {
		mIsRightDirection = true;
	}
	if (mAcceleration.x < 0) {
		mIsRightDirection = false;
	}
}

void Player::Move() {

	if (mIsDushAttak) {
		DushAttakState();
	}
	else {
		NormalState();
	}
	
}


void Player::WallKick(int i) {

	mVelocity.x = CONTAINER->getPlayerData().wallKickForce * i * DELTA_TIME->get();
	mVelocity.y = CONTAINER->getPlayerData().jumpForce * DELTA_TIME->get();

}


void Player::Input() {
	mDushAttakDirectionInput.SetZero();
	
	Vec2 stick;
	Vec2 wasd;

	if (CONTROLLER->isInput()) {
		CONTROLLER->getLeftStick(0, &stick.x, &stick.y);
	}
	if (KEY->isPressed(DIK_D)) {
		wasd.x += 1;
	}
	if (KEY->isPressed(DIK_A)) {
		wasd.x += -1;
	}
	if (KEY->isPressed(DIK_W)) {
		wasd.y += 1;
	}
	if (KEY->isPressed(DIK_S)) {
		wasd.y += -1;
	}

	if (wasd.IsZero() == false) {
		mDushAttakDirectionInput = wasd.Normalized();
	}
	if (stick.IsZero() == false) {
		mDushAttakDirectionInput = stick.Normalized();
	}
	mMoveInput = Math::GetSign(mDushAttakDirectionInput.x);
	
	// スペース or Aボタンでジャンプ
	mJumpInput = KEY->isPressed(DIK_SPACE) | CONTROLLER->isPressed(0, kControllerButtonA);
	// Eキー or Yボタン or R2トリガーで攻撃
	mAttakInput = KEY->isPressed(DIK_E) | CONTROLLER->isPressed(0, kControllerButtonY) | CONTROLLER->isPressed(0, kControllerRightTrigger);
	// SHIFTキー or Bボタン or L2トリガーでダッシュ攻撃
	mDushAttakInput = KEY->isPressed(DIK_LSHIFT) | CONTROLLER->isPressed(0, kControllerButtonB) | CONTROLLER->isPressed(0, kControllerLeftTrigger);
	if (mIsJump) {
		if (KEY->isRelease(DIK_SPACE) | CONTROLLER->isRelease(0, kControllerButtonA)) {
			mJumpInputRelease = true;
		}
	}
}

void Player::NormalState() {
	if (mDushCoolTime > 0) {
		mDushCoolTime += -DELTA_TIME->get();
	}

	mAcceleration.x = CONTAINER->getPlayerData().movementJerk * mMoveInput;

	// ジャンプ
	if (mJumpInput && mIsGround && mIsJump == false) {
		mIsJump = true;
		mJumpInputRelease = false;
		mAcceleration.y += CONTAINER->getPlayerData().jumpForce;
		for (auto& it : mJumpEffect) {
			if (it.getIsAlive() == false) {
				it.Spawn(mPosition);
				break;
			}
		}
	}
	// 二段ジャンプ
	if (mJumpInput && mIsGround == false && mIsDoubleJump == false && mJumpInputRelease == true) {
		mIsDoubleJump = true;
		mAcceleration.y = CONTAINER->getPlayerData().jumpForce;
		for (auto& it : mJumpEffect) {
			if (it.getIsAlive() == false) {
				it.Spawn(mPosition);
				break;
			}
		}
	}
	// 重力
	if (mIsGround == false) {
		mAcceleration.y += CONTAINER->getPlayerData().gravity;
	}
	// ダッシュ攻撃
	if (mDushAttakInput && mDushCoolTime <= 0.0f) {
		mIsDushAttak = true;
		if (mDushAttakDirectionInput.IsZero()) {
			if (mIsRightDirection) {
				mDushAttakDirectionInput = { 1,0 };
			}
			else {
				mDushAttakDirectionInput = { -1,0 };
			}
		}
		mDushAttakDirection = mDushAttakDirectionInput;
		mDushAttakStartPosition = mPosition;
	}
	mVelocity = mAcceleration;

	mPosition += mVelocity * DELTA_TIME->get();
	mPosition = MAP->PushOut(mPosition, mVelocity * DELTA_TIME->get(), mMapColliderRect, &mIsMapCollsion);
}

void Player::DushAttakState() {

	mAcceleration = mDushAttakDirection.Magnituded(CONTAINER->getPlayerData().dushAttakSpeed);

	mVelocity = mAcceleration;

	mPosition += mVelocity * DELTA_TIME->get();
	mPosition = MAP->HighSpeedPushOut(mPosition, mVelocity * DELTA_TIME->get(), mMapColliderRect, &mIsMapCollsion);

}