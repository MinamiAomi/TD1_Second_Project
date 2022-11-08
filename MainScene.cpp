#include "MainScene.h"
#include "Game.h"
#include "Camera.h"
#include "InputDevice.h"

void MainScene::Create() {

}

void MainScene::Init() {

}

void MainScene::Update() {

	getGame()->getCamera()->Update();
}

void MainScene::Draw() {
	
	
	if (Game::_debugMode) {
		Novice::ScreenPrintf(0, 0, "MAIN");
	}
}

void MainScene::NextScene() {
	if (KEY->isTrigger(DIK_T)) {
		getGame()->ChangeScene(Game::kTitleScene);
	}
}
