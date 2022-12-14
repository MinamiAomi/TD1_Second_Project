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

#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


void TitleScene::Create()
{
	
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	MAP->Update();

	PLAYER->Update();
	BOSS->Update();

	if (MOUSE->IsTrigger(kMouseButtonLeft)) {
		getGame()->getEffectManager()->getNormalEffect()->Create(
			7,
			getGame()->getInput()->getMouse()->getPosition(),
			1000, 32, 32,Math::ToRadians((float)Func::Random(0,360)), 0.1f);
	}

	


	getGame()->getEffectManager()->Update();
	getGame()->getCamera()->Update();
}

void TitleScene::Draw() {
	MAP->Draw();
	BOSS->Draw();
	PLAYER->Draw();
	getGame()->getEffectManager()->getNormalEffect()->Draw();

}

void TitleScene::NextScene() {
	if (KEY->isTrigger(DIK_T)) {
		getGame()->ChangeScene(Game::kMainScene);
	}
}
