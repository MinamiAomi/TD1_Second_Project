#pragma once
#include "MyMath.h"
#include "Shape.h"
#include "ImageData.h"

#ifndef BOSSPART_H_
#define BOSSPART_H_

#define BOSS_INITDATA GetBoss()->getGame()->getContainer()->getBossData()
#define BOSS_GAME GetBoss()->getGame()
#define BOSS_CAMERA GetBoss()->getGame()->getCamera()


class BossPart 
{
public:
	struct InitData
	{
		ImageData image;
		Quad imageQuad;

		Vec2 position;
		float angle;
		float scale;
	};

private:
	class Boss* mBoss;
protected:
	TransForm mTransForm;
public:
	class Boss* GetBoss() { return mBoss; }
	TransForm* GetTransFormPtr() { return &mTransForm; }

public:
	BossPart(class Boss* boss, TransForm* parent);
	virtual ~BossPart();

	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif
