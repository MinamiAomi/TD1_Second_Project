#pragma once
#include "BossPart.h"
class BossHandB :
	public BossPart
{
public:
	struct InitData : public BossPart::InitData
	{

	};


private:


public:
	BossHandB(class Boss* boss, TransForm* parent);
	~BossHandB();

	void Create();
	void Update();
	void Draw();
};
