#pragma once
#include "GameObject.h"
#include "ImageData.h"
class Back :
    public GameObject
{
public:
	struct Data
	{
		ImageData image;
	};



public:
	Back(class Game* game) : GameObject(game){}
	~Back() {}

	void Draw();
};

