#include "BossArmBulletManager.h"
#include "Game.h"
#include "Container.h"
#include "DeltaTime.h"

BossArmBulletManager::BossArmBulletManager(Game* game) :
	GameObject(game)
{
	mBullets.resize(BOSS_DATA.bulletMaxNum,game);
}

BossArmBulletManager::~BossArmBulletManager()
{}

void BossArmBulletManager::Create()
{
}

void BossArmBulletManager::Init()
{
	for (auto& it : mBullets) {
		it.Init();
	}
}


void BossArmBulletManager::Update(const Vec2& pos)
{
	if (mCoolTime > 0) {
		mCoolTime += -DELTA_TIME->get();
	}

	if (mIsFire == true) {
		if (mCoolTime <= 0.0f) {
			for (auto& it : mBullets) {
				if (it.IsAlive() == false) {
					it.Create(pos, PLAYER->getPosition());
					mCoolTime = BOSS_DATA.bulletCoolTime;
					break;
				}
			}
		}
	}
	for (auto& it : mBullets) {
		if (it.IsAlive() == true) {
			it.Update();
		}
	}
}

void BossArmBulletManager::Draw()
{
	for (auto& it : mBullets) {
		if (it.IsAlive() == true) {
			it.Draw();
		}
	}
}

std::vector<Rect> BossArmBulletManager::BulletRect() const {
	std::vector<Rect> result;
	for (auto& it : mBullets) {
		if (it.IsAlive() == true) {
			result.emplace_back(it.GetRect());
		}
	}
	return result;
}

std::vector<BossArmBullet> BossArmBulletManager::Bullets() const
{
	std::vector<BossArmBullet> result;
	for (auto& it : mBullets) {
		if (it.IsAlive() == true) {
			result.emplace_back(it);
		}
	}
	return result;
}
