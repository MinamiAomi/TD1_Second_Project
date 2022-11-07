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

	class Container* mContainer = nullptr; // �R���e�i
	class Key* mKey = nullptr; // �L�[�{�[�h
	class Controller* mController = nullptr; // �R���g���[���[
	class DeltaTime* mDeltaTime = nullptr; // �f���^�^�C��

	SceneId mCurrentSceneId = kTitleScene; // ���݂̃V�[��
	class Scene* mScenes[kSceneIdNum] = { nullptr }; // �V�[��
	class TitleScene* mTitleScenePtr = nullptr; // �^�C�g���V�[���|�C���^
	class MainScene* mMainScenePtr = nullptr; // ���C���V�[���|�C���^

	class Camera* mCamera = nullptr;
	class EffectManager* mEffectManager = nullptr;
	class Map* mMap = nullptr;
	// �Q�b�^�[��
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
	// ���C�����[�v
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

