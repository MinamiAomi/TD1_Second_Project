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
	mGameData.map.chipRowNum = 80;
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
	
	mGameData.player.jumpEffectNum = 2;

	float size = 12.0f;
	mGameData.effect.jumpEffect.imageQuad = ToQuad({{-size / 2.0f,size / 2.0f},size , size}) ;
	mGameData.effect.jumpEffect.particleNum = 12;
	mGameData.effect.jumpEffect.exitTime = 0.1f;
	mGameData.effect.jumpEffect.pariticleSpeed = 500.0f;

	mGameData.particle.normal = { 0,0,0,128,128 };

	LoadBoss();
}

void Container::LoadImages() {
	mGameData.particle.fadeStraight.image.handle = Novice::LoadTexture("./resource/images/effect/partical2.png");
	mGameData.particle.normal.handle = mGameData.particle.fadeStraight.image.handle;
	mGameData.map.chipImageHandle[kChipTypeNone] = -1;
	mGameData.map.chipImageHandle[kChipTypeBlock] = Novice::LoadTexture("./resource/images/map/chipBlock.png");

	mGameData.player.image.handle = Novice::LoadTexture("./resource/images/player/test.png");
	
	mGameData.boss.mainImage.handle = Novice::LoadTexture("./resource/images/boss/body.png");
	mGameData.boss.arm1Image.handle = Novice::LoadTexture("./resource/images/boss/arm1.png");
	mGameData.boss.arm2Image.handle = Novice::LoadTexture("./resource/images/boss/arm2.png");
	mGameData.boss.swordHandImage.handle = Novice::LoadTexture("./resource/images/boss/sword.png");
	mGameData.boss.gunHandImage.handle = Novice::LoadTexture("./resource/images/boss/gun.png");
	mGameData.boss.headImage.handle = Novice::LoadTexture("./resource/images/boss/head.png");
}


void Container::LoadBoss() {
	float size = (float)mGameData.map.chipSize;

	// Main
	mGameData.boss.mainImage.left = 0;
	mGameData.boss.mainImage.top = 0;
	mGameData.boss.mainImage.width = 256;
	mGameData.boss.mainImage.height = 256;
	mGameData.boss.mainImageQuad = ToQuad({ {-size * 4.0f, size * 4.0f }, size * 8.0f, size * 8.0f });
	mGameData.boss.position = { 1200,500 };
	mGameData.boss.angle = 0.0f;
	mGameData.boss.scale = 1.7f;

	float scale = mGameData.boss.scale;

	mGameData.boss.armLength = size * 5.0f * scale;
	mGameData.boss.rootLength = size * 3.0f * scale;
	// Arm
	mGameData.boss.arm1Image.left = 0;
	mGameData.boss.arm1Image.top = 0;
	mGameData.boss.arm1Image.width = 256;
	mGameData.boss.arm1Image.height = 128;
	mGameData.boss.arm2Image.left = 0;
	mGameData.boss.arm2Image.top = 0;
	mGameData.boss.arm2Image.width = 256;
	mGameData.boss.arm2Image.height = 128;
	mGameData.boss.armImageQuad = ToQuad({ Vec2{ 0, size * 1.25f } *scale, (mGameData.boss.armLength +18 * scale), size * 2.5f * scale }).SideFlip();

	float handScale = 0.7f;
	// Hand
	mGameData.boss.swordHandImage.left = 0;
	mGameData.boss.swordHandImage.top = 0;
	mGameData.boss.swordHandImage.width = 256;
	mGameData.boss.swordHandImage.height = 128;
	mGameData.boss.swordHandImageQuad = ToQuad({ { -size * 3.0f * scale * handScale, size * 3.0f * scale * handScale}, size * 12.0f * scale * handScale, size * 6.0f * scale * handScale }).SideFlip();


	mGameData.boss.gunHandImage.left = 0;
	mGameData.boss.gunHandImage.top = 0;
	mGameData.boss.gunHandImage.width = 128;
	mGameData.boss.gunHandImage.height = 128;
	mGameData.boss.gunHandImageQuad = ToQuad({ { -size * 3.0f * scale * handScale, size * 3.0f * scale * handScale}, size * 6.0f * scale * handScale, size * 6.0f * scale * handScale }).SideFlip();

	mGameData.boss.headImage = { 0,0,0,128,128 };
	mGameData.boss.headImageQuad = ToQuad({ {-size * 3.0f, size * 3.0f },size * 6,size * 6 });
	mGameData.boss.headPos = { 0,size * 4.0f };


	mGameData.boss.root[0] = Vec2{-2,1}.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[1] = Vec2{ 2,1 }.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[2] = Vec2{ -2,-1 }.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[3] = Vec2{ 2,-1 }.Normalized() * mGameData.boss.rootLength;
}