#pragma once
#include "Camera.h"
#include "DataStruct.h"
#include "Map.h"

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
		Camera::InitData camera = {}; // カメラ

		EffectData effect = {}; // エフェクト
		ParticleData particle = {};
		
		Map::InitData map = {};
	};

private:
	WindowData mWindowData;
	GameData mGameData;

	// ゲッター類 
public:
	const WindowData& getWindow() const { return mWindowData; } 
	const Camera::InitData& getCameraData() const { return mGameData.camera; }
	const EffectData& getEffectData() const { return mGameData.effect; }
	const ParticleData& getParticleData() const { return mGameData.particle; }
	const Map::InitData& getMapData() const { return mGameData.map; }

public:
	Container();
	~Container();

	void Load();

private:
	void LoadData();
	void LoadImages();
	void LoadMapCSV();
};

