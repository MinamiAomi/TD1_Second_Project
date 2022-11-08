#include "PlayerMain.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "InputDevice.h"
#include "DeltaTime.h"

#include "PlayerStateWait.h"

Player::Player(class Game* game) : 
	GameObject(game) {
	mStates[kStateWait] = new PlayerStateWait(this);
}

Player::~Player() {
	delete mStates[kStateWait];
}


void Player::Create() {

	mPosition = CONTAINER->getPlayerData().position;
	mVelocity.SetZero();
	mAcceleration.SetZero();
	mSize = CONTAINER->getPlayerData().size;
	mImageRect = Rect::CreateCenter(mSize);
	mMapColliderRect = Rect::CreateCenter(CONTAINER->getPlayerData().mapColliderSize);
}

void Player::Update() {

	this->Input();

	mStates[mCurrentState]->Proc();

	
}

void Player::Draw() {

	CAMERA->DrawSpriteRect(mImageRect.Translation(mPosition), CONTAINER->getPlayerData().image);

}


void Player::Input() {
	mMoveInput = 0;
	if (INPUT_DEV->isUseController()) {

	}
	else {

	}


}

void Player::ApplyForce() {

}