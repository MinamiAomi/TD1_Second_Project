#pragma once
#include "BossPart.h"
class BossHandA :
    public BossPart
{
public:
	struct InitData : public BossPart::InitData
	{

	};


private:


public:
	BossHandA(class Boss* boss, TransForm* parent);
	~BossHandA();

	void Create();
	void Update();
	void Draw();
};
