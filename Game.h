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

	class Container* mContainer = nullptr; // �R���e�i
	class InputDevice* mInput = nullptr;
	class DeltaTime* mDeltaTime = nullptr; // �f���^�^�C��

	SceneId mCurrentSceneId = kTitleScene; // ���݂̃V�[��
	class Scene* mScenes[kSceneIdNum] = { nullptr }; // �V�[��
	class TitleScene* mTitleScenePtr = nullptr; // �^�C�g���V�[���|�C���^
	class MainScene* mMainScenePtr = nullptr; // ���C���V�[���|�C���^
	class OptionScene* mOptionScenePtr = nullptr; // �ݒ�V�[���|�C���^

	class Camera* mCamera = nullptr;
	class EffectManager* mEffectManager = nullptr;
	class Map* mMap = nullptr;
	class Player* mPlayer = nullptr;
	class Boss* mBoss = nullptr;
	class Back* mBack = nullptr;
	class Fade* mFade = nullptr;
	// �Q�b�^�[��
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

