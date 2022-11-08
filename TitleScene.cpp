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
			800, 64, 64,Math::ToRadians((float)Func::Random(0,360)), 100.0f);
	}

	//vel.SetZero();
	//if (getGame()->getUseController()) {
	//	CONTROLLER->GetLeftStick(0, vel.x, vel.y);
	//	//Debug::Print("%f,%f", vel.x, vel.y);
	//	if (!vel.IsZero()) {
	//		vel = vel.Magnituded(5);
	//	}
	//	if (CONTROLLER->IsPressedButton(0, Controller::kRightTrigger)) {
	//		sizex += 1;
	//	}
	//	if (CONTROLLER->IsPressedButton(0, Controller::kRightShoulder)) {
	//		sizex += -1;
	//	}
	//	if (CONTROLLER->IsPressedButton(0, Controller::kLeftTrigger)) {
	//		sizey += 1;
	//	}
	//	if (CONTROLLER->IsPressedButton(0, Controller::kLeftShoulder)) {
	//		sizey += -1;
	//	}
	//}
	//else {
	//	if (KEY->IsPressed(DIK_A)) {
	//		vel.x += -5;
	//	}
	//	if (KEY->IsPressed(DIK_D)) {
	//		vel.x += 5;
	//	}
	//	if (KEY->IsPressed(DIK_W)) {
	//		vel.y += 5;
	//	}
	//	if (KEY->IsPressed(DIK_S)) {
	//		vel.y += -5;
	//	}
	//	if (KEY->IsPressed(DIK_Q)) {
	//		vel.x += -5;
	//		vel.y += 5;
	//	}
	//}
	//
	//rect = { {-sizex / 2,sizey / 2},sizex,sizey };
	//pos += vel;
	//prePos = pos;
	//pos = getGame()->getMap()->PushOut(pos, vel, rect);
#ifdef _DEBUG
	//Debug::Print("size x %.2f  :  y %.2f", sizex, sizey);
#endif // _DEBUG


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
