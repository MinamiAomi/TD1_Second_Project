#pragma once
#include "GameObject.h"
#include "Lerp.h"

class Fade :
    public GameObject
{

public:
	

private:

	unsigned int color;
	Lerp<float> lerp;
	bool mIsLight;
	bool mIsDarken;

	float time = 1.0f;

public:
	Fade(class Game* game) : GameObject(game){}
	~Fade(){}

	void Start();
	void Update();
	void Draw();

	bool End() const { return mIsLight == false && mIsDarken == false; }
	bool Swich() const { return mIsLight == true && mIsDarken == false && lerp.IsEnd(); }
};

