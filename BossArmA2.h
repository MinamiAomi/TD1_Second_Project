#pragma once
#include "BossPart.h"
class BossArmA2 :
    public BossPart
{

public:
	struct InitData : public BossPart::InitData
	{

	};

private:
	

public:
	BossArmA2(class Boss* boss, TransForm* parent);
	~BossArmA2();

	void Create();
	void Update();
	void Draw();
};

