#include "Game.h"
#include <Novice.h>
#include "Func.h"
#include "Container.h"
#include "Key.h"
#include "ControllerInput.h"
#include "DeltaTime.h"
#include "Scene.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "Camera.h"
#include "EffectManager.h"
#include "Map.h"

#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


Game::Game() {
	Func::Srand();
	this->Initialize();
}

Game::~Game() {
	this->Finalize();
}

void Game::Run() {
	this->ObjCreate();
	this->ChangeScene(kTitleScene); // タイトルから始まる
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		mDeltaTime->CalcDeltaTime();
		// フレームの開始
		Novice::BeginFrame();
		mKey->SetState();
		mController->SetState();
		mCamera->setMousePosition();

		mUseController = mController->IsInput() ? true : mUseController;
		mUseController = mKey->IsInput() ? false : mUseController;
	
#ifdef _DEBUG
		Debug::PrintCountReset();
		if (mKey->IsTrigger(DIK_TAB)) {
			_debugMode ^= true;
		}
		if (_debugMode) {
			switch (mCurrentSceneId)
			{
			case Game::kTitleScene:
				Debug::Print("Title");
				break;
			case Game::kMainScene:
				Debug::Print("Main");
				break;
			}
		}
#endif // _DEBUG

		mScenes[mCurrentSceneId]->Proc();

#ifdef _DEBUG
		if (_debugMode) {
			static const Rect scrRect = { {0,(float)mContainer->getWindow().kHeight},(float)mContainer->getWindow().kWidth,(float)mContainer->getWindow().kHeight };
			mCamera->DrawRect(scrRect, WHITE, kFillModeWireFrame); // カメラ初期位置の四角
			Novice::SetBlendMode(kBlendModeAdd);
			mCamera->DrawCircle({ mCamera->getWorldPosition(), 5}, RED); // ワールド座標の点
			mCamera->DrawCircle({ mContainer->getCameraData().worldPosition, 5}, GREEN); // カメラ初期位置座標の点
			mCamera->DrawCircle({ mCamera->getMousePosition(), 5 }, BLUE); // マウスの座標の点
			Novice::SetBlendMode(kBlendModeNormal);
		}
#endif // _DEBUG

		// フレームの終了
		Novice::EndFrame();
	}
}

void Game::ChangeScene(SceneId nextscene) {
	mCurrentSceneId = nextscene;
	mScenes[mCurrentSceneId]->Init();
}

void Game::Initialize() {
	mContainer = new Container();
	
	Novice::Initialize(
		mContainer->getWindow().kTitle,
		mContainer->getWindow().kWidth,
		mContainer->getWindow().kHeight);
	
	mContainer->Load();

	mKey = Key::GetInstance();
	mController = Controller::GetInstance();
	mDeltaTime = DeltaTime::GetInstance();

	mScenes[kTitleScene] = mTitleScenePtr = new TitleScene(this);
	mScenes[kMainScene] = mMainScenePtr = new MainScene(this);

	mCamera = new Camera(this);
	mEffectManager = new EffectManager(this);
	mMap = new Map(this);
	// 背景は黒
	Novice::SetClearColor(mContainer->getWindow().kClearColor);
}

void Game::Finalize() {
	Func::SafeDelete(mMap);
	Func::SafeDelete(mEffectManager);
	Func::SafeDelete(mCamera);
	mTitleScenePtr = nullptr;
	mMainScenePtr = nullptr;
	for (auto scene : mScenes) {
		Func::SafeDelete(scene);
	}
	Novice::Finalize();
	Func::SafeDelete(mContainer);
}

void Game::ObjCreate() {
	for (auto scene : mScenes) {
		scene->Create();
	}
	mCamera->Create();
	mEffectManager->Create();
	mMap->Create();
}

#ifdef _DEBUG
bool Game::_debugMode = false;
#endif