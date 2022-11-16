#pragma once
#include "Boss.h"
#include "BossArmA1.h"
#include "BossArmA2.h"
#include "BossHandA.h"
#include "BossArmB1.h"
#include "BossArmB2.h"
#include "BossHandB.h"

struct BossInitData
{
	Boss::InitData main;
	BossArmA1::InitData armA1;
	BossArmA2::InitData armA2;
	BossHandA::InitData handA;
	BossArmB1::InitData armB1;
	BossArmB2::InitData armB2;
	BossHandB::InitData handB;
};