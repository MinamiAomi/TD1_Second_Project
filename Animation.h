#pragma once

class Animation {

private:
	int mAnimeFrameNum = 0; // コマ数
	int mCurrentFrame = 0; // 現在のコマ
	float mIntervalSecond = 0.0f; // 切り替わる時間（秒）
	float mSwitchSecond = 0.0f; // 切り替わるまでの時間（秒）
	bool mIsLoop = true; // ループするか
	

public:
	int getAnimeFrameNum() const { return mAnimeFrameNum; }
	int getCurrentFrame() const { return mCurrentFrame; }
	float getIntervalSecond() const { return mIntervalSecond; }
	float getSwitchSecond() const { return mSwitchSecond; }
	bool isLoop() const { return mIsLoop; }

	void setAnimeFrameNum(int animeframenum) { mAnimeFrameNum = animeframenum; }
	void setCurrentFrame(int currentframe) { mCurrentFrame = currentframe; }
	void setIntervalSecond(float intervalsecond) { mIntervalSecond = intervalsecond; }
	void setSwitchSecond(float switchsecond) { mSwitchSecond = switchsecond; }
	void setIsLoop(bool isloop) { mIsLoop = isloop; }
	
	// ループしない場合に使う関数
	bool isPlaying() const { return mCurrentFrame > 0; };
	bool isEnd() const { return mCurrentFrame == -1; }

public:
	Animation() {}
	Animation(int afn, float ins, bool loop = true) : 
		mAnimeFrameNum(afn), mIntervalSecond(ins), mIsLoop(loop) {}
	~Animation() {}

	void Init(int afn, float ins, bool loop = true) {
		mAnimeFrameNum = afn;
		mIntervalSecond = ins;
		mIsLoop = loop;
		Start();
	}

	void Start() {
		mSwitchSecond = mIntervalSecond;
		mCurrentFrame = 0;
	}

	void Update(float deltatime) {
		if (mCurrentFrame != -1) {
			mSwitchSecond -= deltatime;
			if (mSwitchSecond <= 0.0f) {
				mSwitchSecond = 0.0f;
			}
			if (mSwitchSecond <= 0.0f) {
				mSwitchSecond = mIntervalSecond;
				mCurrentFrame++;
				if (mCurrentFrame >= mAnimeFrameNum) {
					if (mIsLoop == true) {
						mCurrentFrame = 0;
					}
					else {
						mCurrentFrame = -1;
						mSwitchSecond = 0.0f;
					}
				}
			}
		}
	}



};