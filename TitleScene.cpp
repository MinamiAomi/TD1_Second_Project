#include "TitleScene.h"
#include "Game.h"
#include "Camera.h"
#include "InputDevice.h"
#include "EffectManager.h"
#include "NormalEffect.h"
#include "Map.h"
#include "Func.h"
#include "PlayerMain.h"

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

	if (MOUSE->IsTrigger(kMouseButtonLeft)) {
		getGame()->getEffectManager()->getNormalEffect()->Create(
			200,
			getGame()->getInput()->getMouse()->getPosition(),
			1000, 16, 16,Math::ToRadians((float)Func::Random(0,360)), 10000.2f);
	}

	


	getGame()->getEffectManager()->Update();
	getGame()->getCamera()->Update();
}

void TitleScene::Draw() {
	MAP->Draw();
	PLAYER->Draw();
	getGame()->getEffectManager()->getNormalEffect()->Draw();

}

void TitleScene::NextScene() {
	if (KEY->isTrigger(DIK_T)) {
		getGame()->ChangeScene(Game::kMainScene);
	}
}
