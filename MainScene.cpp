#include "MainScene.h"
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
#include "Easing.h"
#include "DeltaTime.h"

void MainScene::Create() {

}

void MainScene::Init() {
	PLAYER->Init();
	BOSS->Init();
	gameClear = false;
	lerp.Set(0.0f, 1.0f / 3.0f, -720.0f, 0.0f);
}

void MainScene::Update() {

	if (gameClear == false) {

		MAP->Update();

		PLAYER->Update();
		BOSS->Update();



		PLAYER->Collision();
		PLAYER->Animation();
		BOSS->Collision();
		BOSS->Animation();

		getGame()->getCamera()->Update();



		if (KEY->isTrigger(DIK_T) || CONTROLLER->isTrigger(0,kControllerButtonStart)) {
			getGame()->getFade()->Start();
		}
		if (PLAYER->isDeath() && playerDeth == false) {
			playerDeth = true;
			getGame()->getFade()->Start();
		}
		if (BOSS->isClear()) {
			gameClear = true;
			switchTime = 8.0f;
		}
	}
	else  {
		if (switchTime > 0) {
			switchTime += -DELTA_TIME->get();
		}
		lerp.Increment(DELTA_TIME->get());
		lerp.ParamClamp();
		if (lerp.IsEnd() && switchTime <= 0.0f) {
			getGame()->getFade()->Start();
		}
	}
}

void MainScene::Draw() {
	
	
	getGame()->getBack()->Draw();
	MAP->Draw();
	BOSS->Draw();
	PLAYER->Draw();
	getGame()->getEffectManager()->getNormalEffect()->Draw();

	Novice::DrawBox(299, 567 + 50,(int) 682.0f, 49, 0.0f, 0x000000CC, kFillModeSolid);
	Novice::DrawBox(299, 567 + 50, (int)Math::Map(BOSS->getHitPoint(), 0.0f, 682.0f, 0.0f, BOSS_DATA.startHitPoint), 49, 0.0f, 0x512839CC, kFillModeSolid);
	Novice::DrawSpriteRect(0, 720 - 206, 1280, 256, 0, 0, 1280, 256, CONTAINER->getHPBar(), 0.0f, 0xFFFFFFFF);
	
	Novice::DrawBox(20 + 26, 20 + 46, (int)147.0f, 38, 0.0f, 0x000000CC, kFillModeSolid);
	Novice::DrawBox(20 + 26, 20 + 46, (int)Math::Map(PLAYER->getHitPoint(), 0.0f, 147.0f, 0.0f, PLAYER_DATA.startHitPoint), 38, 0.0f, 0x9AF089CC, kFillModeSolid);
	Novice::DrawSpriteRect(20, 20, 200, 100, 0, 0, 512, 256, CONTAINER->getMainData().playerHpBarHandle, 0.0f, WHITE);

	if (gameClear == true) {
		Novice::DrawSprite(0, lerp.Calc(Easing::EaseOutBounce), CONTAINER->getMainData().clearHandle, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	}

}

void MainScene::NextScene() {
	if (getGame()->getFade()->Swich()) {
		if (playerDeth == true) {
			Init();
		}
		else {
			getGame()->ChangeScene(Game::kTitleScene);
		}
	}

	
}


//if (MOUSE->IsTrigger(kMouseButtonLeft)) {
//	getGame()->getEffectManager()->getNormalEffect()->Create(
//		200,
//		getGame()->getInput()->getMouse()->getPosition(),
//		1000, 300, 300,Math::ToRadians((float)Func::Random(0,360)), 11000.0f);
//}
//getGame()->getEffectManager()->Update();