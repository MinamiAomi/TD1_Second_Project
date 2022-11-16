#pragma once
#include "BossPart.h"
class BossArmA1 :
	public BossPart
{
public:
	struct InitData : public BossPart::InitData
	{

	};


private:


public:
	BossArmA1(class Boss* boss, TransForm* parent);
	~BossArmA1();

	void Create();
	void Update();
	void Draw();
};