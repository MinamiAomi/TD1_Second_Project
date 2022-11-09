#include "PlayerMain.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "InputDevice.h"
#include "DeltaTime.h"


#include "Debug.h"

Player::Player(class Game* game) : 
	GameObject(game) {

}


Player::~Player() {
	
}


void Player::Create() {

	mPosition = CONTAINER->getPlayerData().position;
	mVelocity.SetZero();

	mSize = CONTAINER->getPlayerData().size;
	mImageRect = Rect::CreateCenter(mSize);
	mMapColliderRect = Rect::CreateCenter(CONTAINER->getPlayerData().mapColliderSize);
}

void Player::Update() {

	this->Input();


	Move();
	StateUpdate();
	
	Debug::Print("Acc  %f  :  %f", mAcceleration.x, mAcceleration.y);
	Debug::Print("Vel  %f  :  %f", mVelocity.x, mVelocity.y);
	Debug::Print("Pos  %f  :  %f", mPosition.x, mPosition.y);
	


}

void Player::Draw() {

	CAMERA->DrawSpriteRect(mImageRect.Translation(mPosition), CONTAINER->getPlayerData().image);
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
			mPosition = mDushAttakStartPosition + mDushAttakDirection.Magnituded(CONTAINER->getPlayerData().dushAttakDistance);
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
	Debug::Print("Ground       :  %d", mIsGround);
	Debug::Print("Ceiling      :  %d", mIsCeiling);
	Debug::Print("LeftonWall   :  %d", mIsLeftonWall);
	Debug::Print("RightonWall  :  %d", mIsRightonWall);
	Debug::Print("RightDirection  :  %d", mIsRightDirection);
}

void Player::Move() {

	if (mIsDushAttak) {
		
		mAcceleration = mDushAttakDirection.Magnituded(CONTAINER->getPlayerData().dushAttakSpeed);
	}
	else {
		if (mDushCoolTime > 0) {
			mDushCoolTime += -DELTA_TIME->get();
		}

		mAcceleration.x = CONTAINER->getPlayerData().movementJerk * mMoveInput;
		
		if (mJumpInput && mIsGround && mIsJump == false) {
			mIsJump = true;
			mJumpInputRelease = false;
			mAcceleration.y += CONTAINER->getPlayerData().jumpForce;
		}
		if (mJumpInput && mIsGround == false && mIsDoubleJump == false && mJumpInputRelease == true) {
			mIsDoubleJump = true;
			mAcceleration.y = CONTAINER->getPlayerData().jumpForce;
		}
		if (mIsGround == false) {
			mAcceleration.y += CONTAINER->getPlayerData().gravity;
		}
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
	}
	mVelocity = mAcceleration;

	mPosition += mVelocity * DELTA_TIME->get();
	mPosition = MAP->PushOut(mPosition, mVelocity * DELTA_TIME->get(), mMapColliderRect, &mIsMapCollsion);
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

void Player::ApplyForce() {

}