#include "MainScene.h"
#include "Game.h"
#include "Camera.h"
#include "Key.h"

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
	if (getGame()->getKey()->IsTrigger(DIK_T)) {
		getGame()->ChangeScene(Game::kTitleScene);
	}
}
