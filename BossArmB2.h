#pragma once
#include "BossPart.h"
class BossArmB2 :
	public BossPart
{

public:
	struct InitData : public BossPart::InitData
	{

	};

private:


public:
	BossArmB2(class Boss* boss, TransForm* parent);
	~BossArmB2();

	void Create();
	void Update();
	void Draw();
};

