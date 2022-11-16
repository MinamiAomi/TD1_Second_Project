#include "BossPart.h"
#include "Boss.h"

BossPart::BossPart(class Boss* boss, TransForm* parent) :
	mBoss(boss)
{
	mTransForm.parent = parent;
}
BossPart::~BossPart(){}
