#include "OptionScene.h"
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


void OptionScene::Create()
{
	handle = Novice::LoadTexture("./resource/images/operation.png");
}

void OptionScene::Init()
{

}

void OptionScene::Update()
{
	
	if (KEY->isTrigger(DIK_SPACE) || CONTROLLER->isPressed(0, kControllerButtonA)) {
		getGame()->getFade()->Start();
	}
	
}

void OptionScene::Draw() {

	Novice::DrawSprite(0, 0, handle, 1.0f, 1.0f, 0.0f, WHITE);
}

void OptionScene::NextScene() {
	if (getGame()->getFade()->Swich()) {
		getGame()->ChangeScene(Game::kTitleScene);
	}
}