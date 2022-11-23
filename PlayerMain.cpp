#include "PlayerMain.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"
#include "InputDevice.h"
#include "DeltaTime.h"
#include "Boss.h"
#include "Debug.h"
#include "Collision.h"



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
	mMapColliderRect = Rect::CreateCenter(CONTAINER->getPlayerData().mapColliderSize);

	for (auto& it : mJumpEffect) {
		it.Create();
	}
	mHitRect = Rect({ -PLAYER_DATA.hitRectWidth / 2.0f, PLAYER_DATA.hitRectHeight / 2.0f }, PLAYER_DATA.hitRectWidth, PLAYER_DATA.hitRectHeight);
	mKnockBackVel.SetEnd(0.0f);
	mHitPoint = PLAYER_DATA.startHitPoint;

	mCurrentAnime = kWait;
	mRunAnimation.Init(PLAYER_DATA.runFrameNum, PLAYER_DATA.runAnimeTime, true);

	mSlashAnime.Init(PLAYER_DATA.slashAnimeNum, PLAYER_DATA.slashAnimeTime, false);
	mSlashLeft = { -256.0f + -32.0f,0.0f };
}

void Player::Init() {
	mPosition = CONTAINER->getPlayerData().position;
	mVelocity.SetZero();

	mSize = CONTAINER->getPlayerData().size;
	mMapColliderRect = Rect::CreateCenter(CONTAINER->getPlayerData().mapColliderSize);
	mHitRect = Rect({ -PLAYER_DATA.hitRectWidth / 2.0f, PLAYER_DATA.hitRectHeight / 2.0f }, PLAYER_DATA.hitRectWidth, PLAYER_DATA.hitRectHeight);
	mKnockBackVel.SetEnd(0.0f);
	mHitPoint = PLAYER_DATA.startHitPoint;

	mCurrentAnime = kWait;
	mRunAnimation.Init(PLAYER_DATA.runFrameNum, PLAYER_DATA.runAnimeTime, true);

	mSlashAnime.Init(PLAYER_DATA.slashAnimeNum, PLAYER_DATA.slashAnimeTime, false);
	mSlashLeft = { -256.0f + -32.0f,0.0f };

	mKnockBackVel.SetParam(1.0f);

	mInvincibleEffect = 0xFFFFFFFF;
	mInvincibleEffectCycleTime = 0.0f;
}

void Player::Update() {

	if (mKnockBackCoolTime > 0) {
		mKnockBackCoolTime += -DELTA_TIME->get();
	}	
	if (mInvincibleTime > 0) {
		mInvincibleTime += -DELTA_TIME->get();
	}
	if (mSlashCoolTime > 0) {
		mSlashCoolTime += -DELTA_TIME->get();
	}
	
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
	if (mInvincibleTime > 0.0f) {
		switch (mCurrentAnime)
		{
		case Player::kRun:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.runImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().runImage, mInvincibleEffect, mRunAnimation.getCurrentFrame());
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.runImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().runImage,mInvincibleEffect, mRunAnimation.getCurrentFrame());
			}
			break;
		case Player::kJump:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.jumpImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().jumpImage, mInvincibleEffect);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.jumpImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().jumpImage, mInvincibleEffect);
			}
			break;
		case Player::kFall:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.fallImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().fallImage, mInvincibleEffect);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.fallImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().fallImage, mInvincibleEffect);
			}
			break;
		case Player::kWait:
		case Player::kAnimeNum:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.waitImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().waitImage, mInvincibleEffect);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.waitImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().waitImage, mInvincibleEffect);
			}
			break;
		}
	}
	else {
		switch (mCurrentAnime)
		{
		case Player::kRun:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.runImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().runImage, WHITE, mRunAnimation.getCurrentFrame());
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.runImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().runImage, WHITE, mRunAnimation.getCurrentFrame());
			}
			break;
		default:
		case Player::kJump:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.jumpImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().jumpImage);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.jumpImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().jumpImage);
			}
			break;
		case Player::kFall:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.fallImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().fallImage);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.fallImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().fallImage);
			}
			break;
		case Player::kDush:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.dushImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().dushImage);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.dushImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().dushImage);
			}
			break;
		case Player::kWait:
		case Player::kAnimeNum:
			if (mIsRightDirection) {
				CAMERA->DrawQuad(PLAYER_DATA.waitImageQuad.TransForm(mPosition), CONTAINER->getPlayerData().waitImage);
			}
			else {
				CAMERA->DrawQuad(PLAYER_DATA.waitImageQuad.SideFlip().TransForm(mPosition), CONTAINER->getPlayerData().waitImage);
			}
			break;
		}
	}
	
	if (mIsSlash == true && mSlashCoolTime <= 0.0f) {
		Novice::SetBlendMode(kBlendModeAdd);
		if (mSlashDirection == true) {
			CAMERA->DrawQuad(PLAYER_DATA.slashImageQuad.TransForm(mSlashPos), PLAYER_DATA.slashImage, PLAYER_DATA.slashColor, mSlashAnime.getCurrentFrame());
		}
		else {
			CAMERA->DrawQuad(PLAYER_DATA.slashImageQuad.SideFlip().TransForm(mSlashPos + mSlashLeft), PLAYER_DATA.slashImage, PLAYER_DATA.slashColor, mSlashAnime.getCurrentFrame());
		}
		Novice::SetBlendMode(kBlendModeNormal);
		//CAMERA->DrawRect(getSlashRect(), 0x00FF00FF, kFillModeWireFrame);
	}

	
	
	//CAMERA->DrawRect(mHitRect.Translation(mPosition), 0xFF0000FF, kFillModeWireFrame);
	//
	//if (mIsInvincible) {
	//	CAMERA->DrawRect(mHitRect.Translation(mPosition), 0xFF00FFFF, kFillModeSolid);
	//}
	//Novice::ScreenPrintf(0, 0, "Player HP : %.2f", mHitPoint);
}

void Player::Collision()
{
	const auto& player = mHitRect.Translation(mPosition);
	const auto& boss = BOSS->GetHitRect();

	bool bossHit = Collision::RectRect(player, boss.body) ||
		Collision::RectRect(player, boss.head);

	for (int i = 0; i < Boss::kArmNum; i++) {
		if (BOSS->IsHandAlive(i)) {
			bossHit = bossHit || Collision::RectRect(player, boss.hand[i]);
		}
	}

	if (mIsDushAttak == false) {
		if (bossHit == true) {
			if (mIsInvincible == false && mInvincibleTime <= 0.0f) {
				mHitPoint -= BOSS_DATA.bodyAttackPower;
				mIsInvincible = true;
				mInvincibleTime = PLAYER_DATA.invincibleTime;
				mInvincibleEffectCycleTime = 0.1f;
			}
			if (mKnockBackCoolTime <= 0.0f) {
				mKnockBackCoolTime = PLAYER_DATA.knockBackCoolTime;
				float bossPosX = BOSS->GetPosition().x;
				mKnockBackVel.SetParam(0.0f);
				mKnockBackVel.SetEnd(0.0f);
				mKnockBackVel.SetDeltaParam(1.0f / PLAYER_DATA.knockBackCoolTime);
				if (mPosition.x < bossPosX) {
					static const Vec2 invDirection(-PLAYER_DATA.knockBackDirection.x, PLAYER_DATA.knockBackDirection.y);
					mKnockBackVel.SetStart(invDirection * PLAYER_DATA.knockBackFirstSpeed);
				}
				else {
					mKnockBackVel.SetStart(PLAYER_DATA.knockBackDirection * PLAYER_DATA.knockBackFirstSpeed);
				}
			}
			return;
		}
		for (int i = 0; i < Boss::kArmNum; i++) {
			const auto& bullet = BOSS->getBulletManager(i).Bullets();
			for (const auto& it : bullet) {
				if (Collision::RectRect(player, it.GetRect()) == true) {
					if (mIsInvincible == false && mInvincibleTime <= 0.0f) {
						mHitPoint -= BOSS_DATA.bulletAttackPower;
						mIsInvincible = true;
						mInvincibleTime = PLAYER_DATA.invincibleTime;
						mInvincibleEffectCycleTime = 0.1f;
					}
					if (mKnockBackCoolTime <= 0.0f) {
						mKnockBackCoolTime = PLAYER_DATA.knockBackCoolTime;
						mKnockBackVel.SetParam(0.0f);
						mKnockBackVel.SetEnd(0.0f);
						mKnockBackVel.SetDeltaParam(1.0f / PLAYER_DATA.knockBackCoolTime);
						mKnockBackVel.SetStart(Vec2(it.GetVel().x , PLAYER_DATA.knockBackDirection.y).Normalized() * (PLAYER_DATA.knockBackFirstSpeed * 0.5f));
						
					}
					return;
				}
			}
		}
		
	}
	if (mPosition.x < 0.0f || CONTAINER->getMapData().mapWidth < mPosition.x ||
		mPosition.y < 0.0f || CONTAINER->getMapData().mapHeight < mPosition.y) {
		mPosition = { CONTAINER->getMapData().mapWidth / 2.0f , 200.0f };
	}
}

void Player::Animation()
{


	if (mIsGround == true) {
		if (mMoveInput != 0 && mIsLeftonWall == false && mIsRightonWall == false) {
			mCurrentAnime = kRun;
		}
		else {
			mCurrentAnime = kWait;
		}
	}
	else {
		if (mVelocity.y > 0.0f) {
			mCurrentAnime = kJump;
		}
		else {
			mCurrentAnime = kFall;
		}
	}

	if (mIsDushAttak == true) {
		mCurrentAnime = kDush;
	}
	if (mCurrentAnime == kRun) {
		mRunAnimation.Update(DELTA_TIME->get());
	}

	if (mIsSlash == true) {
		mSlashAnime.Update(DELTA_TIME->get());
		if (mSlashAnime.isEnd()) {
			mIsSlash = false;
			mSlashCoolTime = PLAYER_DATA.slashCoolTime;
		}
	}

	float cycleTime = 0.1f;
	if (mInvincibleTime > 0.0f) {
		if (mInvincibleEffectCycleTime > 0) {
			mInvincibleEffectCycleTime += -DELTA_TIME->get();
		}
		if (mInvincibleEffectCycleTime <= 0.0f) {
			mInvincibleEffectCycleTime = cycleTime;
			if (mInvincibleEffect == 0xFFFFFFFF) {
				mInvincibleEffect = 0;
			}
			else {
				mInvincibleEffect = 0xFFFFFFFF;
			}
		}
	}
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
	if (mKnockBackCoolTime <= 0) {
		mKnockBackVel.SetParam(1.0f);
	}
	if (mAcceleration.x > 0) {
		mIsRightDirection = true;
	}
	if (mAcceleration.x < 0) {
		mIsRightDirection = false;
	}
	if (mInvincibleTime <= 0.0f) {
		mIsInvincible = false;
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

Rect Player::getSlashRect() const
{
	Rect result;
	if (mSlashDirection) {
		result = PLAYER_DATA.slashCollider.Translation(mSlashPos);
	}
	else {
		static Vec2 pos = { -PLAYER_DATA.slashCollider.width - 32.0f, 0.0f };
		result = PLAYER_DATA.slashCollider.Translation(mSlashPos + pos);
	}
	return result;
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
	// Eキー or Xボタン or R2トリガーで攻撃
	mAttakInput = KEY->isPressed(DIK_E) | CONTROLLER->isPressed(0, kControllerButtonX) | CONTROLLER->isPressed(0, kControllerRightTrigger);
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
	if (mKnockBackCoolTime > 0.0f) {
		mKnockBackVel.Increment(DELTA_TIME->get());
		mKnockBackVel.ParamClamp();
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
	if (mKnockBackVel.IsEdge() == false) {
		mVelocity += mKnockBackVel;
	}

	mPosition += mVelocity * DELTA_TIME->get();
	mPosition = MAP->PushOut(mPosition, mVelocity * DELTA_TIME->get(), mMapColliderRect, &mIsMapCollsion);


	if (mIsSlash == false && mAttakInput == true && mSlashCoolTime <= 0.0f) {
		mSlashAnime.Start();
		mIsSlash = true;
		mSlashPos = mPosition;
		mSlashDirection = mIsRightDirection;
	}

}

void Player::DushAttakState() {

	mAcceleration = mDushAttakDirection.Magnituded(CONTAINER->getPlayerData().dushAttakSpeed);

	mVelocity = mAcceleration;

	mPosition += mVelocity * DELTA_TIME->get();
	mPosition = MAP->HighSpeedPushOut(mPosition, mVelocity * DELTA_TIME->get(), mMapColliderRect, &mIsMapCollsion);

}