#pragma once
#include "Camera.h"
#include "DataStruct.h"
#include "Map.h"
#include "PlayerMain.h"
#include "Boss.h"
#include "Back.h"
#include "TitleScene.h"
#include "MainScene.h"

class Container {

public:
	struct WindowData {
		const int kWidth = 1280;
		const int kHeight = 720;
		const char* kTitle = "タイトル";
		const unsigned int kClearColor = 0x000000FF;
	};
private:

	struct GameData {
		TitleScene::Data title = {};
		MainScene::Data main = {};

		Camera::InitData camera = {}; // カメラ

		EffectData effect = {}; // エフェクト
		ParticleData particle = {};
		
		Map::InitData map = {};

		Player::InitData player = {};
		Boss::InitData boss = {};

		Back::Data back = {};
		int HPBarHandle;
	};

private:
	WindowData mWindowData;
	GameData mGameData;

	// ゲッター類 
public:
	const WindowData& getWindow() const { return mWindowData; } 
	const TitleScene::Data& getTitleData() const { return mGameData.title; }
	const MainScene::Data& getMainData() const { return mGameData.main; }
	const Camera::InitData& getCameraData() const { return mGameData.camera; }
	const EffectData& getEffectData() const { return mGameData.effect; }
	const ParticleData& getParticleData() const { return mGameData.particle; }
	const Map::InitData& getMapData() const { return mGameData.map; }
	const Player::InitData& getPlayerData() const { return mGameData.player; }
	const Boss::InitData& getBossData() const { return mGameData.boss; }
	const Back::Data& getBackData() const { return mGameData.back; }
	
	int getHPBar() const { return mGameData.HPBarHandle; }

public:
	Container();
	~Container();

	void Load();

private:
	void LoadData();
	void LoadImages();
	void LoadBoss();
};

