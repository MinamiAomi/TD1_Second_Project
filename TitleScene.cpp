#include "TitleScene.h"
#include "Game.h"
#include "Camera.h"
#include "InputDevice.h"
#include "EffectManager.h"
#include "NormalEffect.h"
#include "Map.h"
#include "Func.h"
#include "PlayerMain.h"
#include "Boss.h"
#include "Collision.h"
#include "Back.h"
#include "Container.h"
#include "MyMath.h"
#include "Fade.h"

#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


void TitleScene::Create()
{
	
}

void TitleScene::Init()
{
	mIsFead = false;
}

void TitleScene::Update()
{

	if (getGame()->getFade()->End()) {
		if (KEY->isTrigger(DIK_SPACE) || CONTROLLER->isPressed(0, kControllerButtonA)) {
			mIsGameStart = true;
			getGame()->getFade()->Start();
		}
		if (KEY->isTrigger(DIK_LSHIFT) || CONTROLLER->isPressed(0, kControllerButtonY)) {
			mIsGameStart = false;
			getGame()->getFade()->Start();
		}
	}

	getGame()->getCamera()->Update();
}

void TitleScene::Draw() {
	
	Novice::DrawSprite(0, 0, CONTAINER->getTitleData().backImage.handle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	static float angle = 0.0f;
	angle += Math::ToRadians(1.0f);
	float siny = Math::Sin(angle) * 50;
	Novice::DrawSprite(0, 550 + siny, CONTAINER->getTitleData().logoImage.handle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	Novice::DrawSprite(0, 450 + siny, CONTAINER->getTitleData().logoYImage.handle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

}

void TitleScene::NextScene() {
	if (getGame()->getFade()->Swich()) {
		if (mIsGameStart == true) {
			getGame()->ChangeScene(Game::kMainScene);
		}
		else {
			getGame()->ChangeScene(Game::kOption);
		}
	}
}
