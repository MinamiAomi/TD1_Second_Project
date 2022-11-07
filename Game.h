#pragma once

class Game {

public:
	enum SceneId {
		kTitleScene,
		kMainScene,

		kSceneIdNum
	};

private:

	bool mUseController = false;

	class Container* mContainer = nullptr; // コンテナ
	class Key* mKey = nullptr; // キーボード
	class Controller* mController = nullptr; // コントローラー
	class DeltaTime* mDeltaTime = nullptr; // デルタタイム

	SceneId mCurrentSceneId = kTitleScene; // 現在のシーン
	class Scene* mScenes[kSceneIdNum] = { nullptr }; // シーン
	class TitleScene* mTitleScenePtr = nullptr; // タイトルシーンポインタ
	class MainScene* mMainScenePtr = nullptr; // メインシーンポインタ

	class Camera* mCamera = nullptr;
	class EffectManager* mEffectManager = nullptr;
	class Map* mMap = nullptr;
	// ゲッター類
public:
	bool getUseController() const { return mUseController; }

	const class Container* getContainer() const { return mContainer; }
	const class Key* getKey() const { return mKey; }
	const class Controller* getController() const { return mController; }
	const class DeltaTime* getDeltaTime() const { return mDeltaTime; }
	class TitleScene* getTitleScen() { return mTitleScenePtr; }
	class MainScene* getMainScen() { return mMainScenePtr; }
	class Camera* getCamera() { return mCamera; }
	class EffectManager* getEffectManager() { return mEffectManager; }
	class Map* getMap() { return mMap; }

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

