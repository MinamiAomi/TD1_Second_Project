#pragma once

class Game {

public:
	enum SceneId {
		kTitleScene,
		kMainScene,
		kOption,

		kSceneIdNum
	};

private:

	bool IsFullScreen = true;

	class Container* mContainer = nullptr; // コンテナ
	class InputDevice* mInput = nullptr;
	class DeltaTime* mDeltaTime = nullptr; // デルタタイム

	SceneId mCurrentSceneId = kTitleScene; // 現在のシーン
	class Scene* mScenes[kSceneIdNum] = { nullptr }; // シーン
	class TitleScene* mTitleScenePtr = nullptr; // タイトルシーンポインタ
	class MainScene* mMainScenePtr = nullptr; // メインシーンポインタ
	class OptionScene* mOptionScenePtr = nullptr; // 設定シーンポインタ

	class Camera* mCamera = nullptr;
	class EffectManager* mEffectManager = nullptr;
	class Map* mMap = nullptr;
	class Player* mPlayer = nullptr;
	class Boss* mBoss = nullptr;
	class Back* mBack = nullptr;
	class Fade* mFade = nullptr;
	// ゲッター類
public:

	const class Container* getContainer() const { return mContainer; }
	const class InputDevice* getInput() const { return mInput; }
	class InputDevice* getInput() { return mInput; }

	const class DeltaTime* getDeltaTime() const { return mDeltaTime; }
	 class DeltaTime* getDeltaTime() { return mDeltaTime; }

	class TitleScene* getTitleScen() { return mTitleScenePtr; }
	class MainScene* getMainScen() { return mMainScenePtr; }
	class Camera* getCamera() { return mCamera; }
	class EffectManager* getEffectManager() { return mEffectManager; }
	class Map* getMap() { return mMap; }
	class Player* getPlayer() { return mPlayer; }
	class Boss* getBoss() { return mBoss; }
	class Back* getBack() { return mBack; }
	class Fade* getFade() { return mFade; }

public:
	Game();
	~Game();
	// メインループ
	void Run();
	void ChangeScene(SceneId nextscene);
private:
	void Initialize();
	void Finalize();
	void ObjCreate();

#ifdef _DEBUG
public:
	static bool _debugMode;
#endif // _DEBUG
};

