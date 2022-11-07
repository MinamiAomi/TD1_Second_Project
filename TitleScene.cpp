#include "TitleScene.h"
#include "Game.h"
#include "Camera.h"
#include "Key.h"
#include "ControllerInput.h"
#include "EffectManager.h"
#include "NormalEffect.h"
#include "Map.h"
#include "Func.h"

#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


static float sizex = 128;
static float sizey = 128;
static Rect rect = { {-sizex/2,sizey/2},sizex,sizey };
static Vec2 pos = { 1040,500 };
static Vec2 prePos = pos;
static Vec2 vel;

void TitleScene::Create()
{
	
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	MAP->Update();

	if (Novice::IsTriggerMouse(0)) {
		getGame()->getEffectManager()->getNormalEffect()->Create(
			200,
			getGame()->getCamera()->getMousePosition(), 
			800, 64, 64,Math::ToRadians((float)Func::Random(0,360)), 100.0f);
	}

	vel.SetZero();
	if (getGame()->getUseController()) {
		CONTROLLER->GetLeftStick(0, vel.x, vel.y);
		//Debug::Print("%f,%f", vel.x, vel.y);
		if (!vel.IsZero()) {
			vel = vel.Magnituded(5);
		}
		if (CONTROLLER->IsPressedButton(0, Controller::kRightTrigger)) {
			sizex += 1;
		}
		if (CONTROLLER->IsPressedButton(0, Controller::kRightShoulder)) {
			sizex += -1;
		}
		if (CONTROLLER->IsPressedButton(0, Controller::kLeftTrigger)) {
			sizey += 1;
		}
		if (CONTROLLER->IsPressedButton(0, Controller::kLeftShoulder)) {
			sizey += -1;
		}
	}
	else {
		if (KEY->IsPressed(DIK_A)) {
			vel.x += -5;
		}
		if (KEY->IsPressed(DIK_D)) {
			vel.x += 5;
		}
		if (KEY->IsPressed(DIK_W)) {
			vel.y += 5;
		}
		if (KEY->IsPressed(DIK_S)) {
			vel.y += -5;
		}
		if (KEY->IsPressed(DIK_Q)) {
			vel.x += -5;
			vel.y += 5;
		}
	}
	
	rect = { {-sizex / 2,sizey / 2},sizex,sizey };
	pos += vel;
	prePos = pos;
	pos = getGame()->getMap()->PushOut(pos, vel, rect);
#ifdef _DEBUG
	//Debug::Print("size x %.2f  :  y %.2f", sizex, sizey);
#endif // _DEBUG


	getGame()->getEffectManager()->Update();
	getGame()->getCamera()->Update();
}

void TitleScene::Draw() {
	MAP->Draw();
	//getGame()->getCamera()->DrawRect(rect.Translation(pos), GREEN, kFillModeWireFrame);
	//Debug::Print("%f,%f", rect.Translation(pos).Right(), rect.Translation(pos).Bottom());
	getGame()->getEffectManager()->getNormalEffect()->Draw();

}

void TitleScene::NextScene() {
	if (getGame()->getKey()->IsTrigger(DIK_T)) {
		getGame()->ChangeScene(Game::kMainScene);
	}
}
