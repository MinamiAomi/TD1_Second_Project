#pragma once
#include "BossPart.h"
class BossArmB1 :
    public BossPart
{

public:
	struct InitData : public BossPart::InitData
	{

	};

private:
	

public:
	BossArmB1(class Boss* boss, TransForm* parent);
	~BossArmB1();

	void Create();
	void Update();
	void Draw();
};

