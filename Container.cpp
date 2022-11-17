#include "Container.h"
#include <Novice.h>

Container::Container() {
}

Container::~Container() {
}

void Container::Load() {
	LoadData();
	LoadImages();
}

void Container::LoadData() {
	mGameData.camera.windowCenter = { (float)mWindowData.kWidth / 2.0f,(float)mWindowData.kHeight / 2.0f };
	mGameData.camera.worldPosition = mGameData.camera.windowCenter;
	mGameData.camera.scele = 1.0f;
	mGameData.camera.theta = 0.0f;		

	mGameData.effect.normal.particleNum = 18;

	mGameData.particle.fadeStraight.image.left = 0;
	mGameData.particle.fadeStraight.image.top = 0;
	mGameData.particle.fadeStraight.image.width = 128;
	mGameData.particle.fadeStraight.image.height = 128;


	mGameData.map.fileName = "./resource/text/map.csv";
	mGameData.map.chipImageSize = 32;
	mGameData.map.chipSize = 32;
	mGameData.map.chipRowNum = 120;
	mGameData.map.chipColmunNum = 33;
	mGameData.map.mapWidth = mGameData.map.chipSize * mGameData.map.chipRowNum;
	mGameData.map.mapHeight = mGameData.map.chipSize * mGameData.map.chipColmunNum;
	
	// カメラスクロール
	mGameData.camera.scrollMin = { (float)mWindowData.kWidth / 2.0f,(float)mWindowData.kHeight / 2.0f };
	mGameData.camera.scrollMax = { mGameData.map.mapWidth - mGameData.camera.scrollMin.x,mGameData.map.mapHeight - mGameData.camera.scrollMin.y };

	// プレイヤー
	mGameData.player.image.left = 0;
	mGameData.player.image.top = 0;
	mGameData.player.image.width = 256;
	mGameData.player.image.height = 256;
	mGameData.player.position = { 600,500 };
	mGameData.player.size = { 48,64 };
	mGameData.player.mapColliderSize = { 32,64 };

	mGameData.player.movementJerk = 300.0f;
	mGameData.player.jumpForce = 1000.0f; 
	mGameData.player.gravity = -45.0f;
	mGameData.player.wallKickForce = 800.0f;
	mGameData.player.wallFriction = 0.6f;
	mGameData.player.airMoveDecay = 0.8f;
	mGameData.player.moveFriction = 0.9f;
	mGameData.player.moveSpeedMax = 300.0f;
	mGameData.player.dushAttakSpeed = 4000.0f;
	mGameData.player.dushAttakDistance = 300.0f;
	mGameData.player.dushAttakCoolTime = 1.5f;

	LoadBoss();
}

void Container::LoadImages() {
	mGameData.particle.fadeStraight.image.handle = Novice::LoadTexture("./resource/images/effect/partical2.png");
	mGameData.map.chipImageHandle[kChipTypeNone] = -1;
	mGameData.map.chipImageHandle[kChipTypeBlock] = Novice::LoadTexture("./resource/images/map/chipBlock.png");

	mGameData.player.image.handle = Novice::LoadTexture("./resource/images/player/test.png");
	
	mGameData.boss.mainImage.handle = Novice::LoadTexture("./resource/images/boss/test.png");
	mGameData.boss.armImage.handle = Novice::LoadTexture("./resource/images/boss/arm.png");
	mGameData.boss.handImage.handle = Novice::LoadTexture("./resource/images/boss/hand.png");
}


void Container::LoadBoss() {
	float size = (float)mGameData.map.chipSize;

	// Main
	mGameData.boss.mainImage.left = 0;
	mGameData.boss.mainImage.top = 0;
	mGameData.boss.mainImage.width = 512;
	mGameData.boss.mainImage.height = 256;
	mGameData.boss.mainImageQuad = ToQuad({ {-size * 3.0f, size * 1.5f }, size * 6.0f, size * 3.0f });
	mGameData.boss.position = { 1280,500 };
	mGameData.boss.angle = 0.0f;
	mGameData.boss.scale = 1.0f;


	// Arm
	mGameData.boss.armImage.left = 0;
	mGameData.boss.armImage.top = 0;
	mGameData.boss.armImage.width = 256;
	mGameData.boss.armImage.height = 128;
	mGameData.boss.armImageQuad = ToQuad({ { 0, size * 0.75f }, -size * 3.0f, size * 1.5f });

	// Hand
	mGameData.boss.handImage.left = 0;
	mGameData.boss.handImage.top = 0;
	mGameData.boss.handImage.width = 512;
	mGameData.boss.handImage.height = 512;
	mGameData.boss.handImageQuad = ToQuad({ { -size * 3.0f, size * 5.0f }, size * 6.0f, size * 6.0f });

	mGameData.boss.armLength = size * 5.0f;
	float rootlen = size * 3.0f;
	mGameData.boss.root[0] = Vec2{-2,1}.Normalized() * rootlen;
	mGameData.boss.root[1] = Vec2{ 2,1 }.Normalized() * rootlen;
	mGameData.boss.root[2] = Vec2{ -2,-1 }.Normalized() * rootlen;
	mGameData.boss.root[3] = Vec2{ 2,-1 }.Normalized() * rootlen;
}