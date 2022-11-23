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
	mGameData.title.backImage = { 0,0,0,1280,720 };
	mGameData.title.logoImage = { 0,0,0,700,100 };
	
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
	mGameData.map.chipSize = 32;
	mGameData.map.chipRowNum = 80;
	mGameData.map.chipColmunNum = 70;
	mGameData.map.mapWidth = mGameData.map.chipSize * mGameData.map.chipRowNum;
	mGameData.map.mapHeight = mGameData.map.chipSize * mGameData.map.chipColmunNum;
	
	// カメラスクロール
	mGameData.camera.scrollMin = { (float)mWindowData.kWidth / 2.0f,(float)mWindowData.kHeight / 2.0f };
	mGameData.camera.scrollMax = { mGameData.map.mapWidth - mGameData.camera.scrollMin.x,mGameData.map.mapHeight - mGameData.camera.scrollMin.y };

	// プレイヤー
	mGameData.player.waitImage = { 0,0,0,256,256 };
	mGameData.player.waitImageQuad = ToQuad({ {-78.0f / 2.0f,78.0f * 4 / 7.0f},78,78 });

	mGameData.player.runImage = { 0,0,0,256,256 };
	mGameData.player.runImageQuad = ToQuad({ {-85.0f / 2.0f,85.0f * 6 / 9.0f},85,85 });
	mGameData.player.runFrameNum = 6;
	mGameData.player.runAnimeTime = 0.15f;

	mGameData.player.jumpImage = { 0,0,0,256,256 };
	mGameData.player.fallImage = { 0,0,0,256,256 };
	mGameData.player.dushImage = { 0,0,0,256,256 };
	mGameData.player.jumpImageQuad = ToQuad({ {-85.0f / 2.0f,85.0f * 6 / 9.0f},85,85 });
	mGameData.player.fallImageQuad = ToQuad({ {-85.0f / 2.0f,85.0f * 6 / 9.0f},85,85 });
	mGameData.player.dushImageQuad = ToQuad({ {-85.0f / 2.0f,85.0f * 6 / 9.0f},85,85 });

	mGameData.player.position = { mGameData.map.mapWidth / 2.0f, 200 };
	mGameData.player.size = { 64,64};
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
	mGameData.player.dushAttakDistance = 400.0f;
	mGameData.player.dushAttakCoolTime = 0.5f;
	
	mGameData.player.jumpEffectNum = 2;

	mGameData.player.hitRectWidth = 32.0f;
	mGameData.player.hitRectHeight = 64.0f;
	mGameData.player.invincibleTime = 1.0f;
	
	mGameData.player.knockBackCoolTime = 1.5f;
	mGameData.player.knockBackFirstSpeed = 1000.0f;
	mGameData.player.knockBackDirection = Vec2::MakeDirection(Math::ToRadians(40.0f));
	mGameData.player.startHitPoint = 100.0f;

	mGameData.player.slashImage = { 0,0,0,256,128 };
	mGameData.player.slashImageQuad = ToQuad({ { 16.0f,64 / 2.0f + 32 }, 256,96 });
	mGameData.player.slashAnimeTime = 0.03f;
	mGameData.player.slashAnimeNum = 5;
	mGameData.player.slashCollider = { { 16,64 / 2.0f + 32 }, 256,96 };
	mGameData.player.slashColor = 0x9AF089CC;
	mGameData.player.slashCoolTime = 0.3f;
	mGameData.player.slashAttackPower = 10.0f;


	float size = 12.0f;
	mGameData.effect.jumpEffect.imageQuad = ToQuad({{-size / 2.0f,size / 2.0f},size , size}) ;
	mGameData.effect.jumpEffect.particleNum = 12;
	mGameData.effect.jumpEffect.exitTime = 0.1f;
	mGameData.effect.jumpEffect.pariticleSpeed = 500.0f;

	mGameData.particle.normal = { 0,0,0,128,128 };



	LoadBoss();
}

void Container::LoadImages() {

	mGameData.title.logoImage.handle = Novice::LoadTexture("./resource/images/push.png");
	mGameData.title.backImage.handle = Novice::LoadTexture("./resource/images/title.png");
	mGameData.title.logoYImage.handle = Novice::LoadTexture("./resource/images/pushY.png");

	mGameData.main.clearHandle = Novice::LoadTexture("./resource/images/clear.png");
	mGameData.main.playerHpBarHandle = Novice::LoadTexture("./resource/images/player/HpBar.png");

	mGameData.particle.fadeStraight.image.handle = Novice::LoadTexture("./resource/images/effect/partical2.png");
	mGameData.particle.normal.handle = mGameData.particle.fadeStraight.image.handle;
	mGameData.map.chipImageHandle[kChipTypeNone] = -1;
	mGameData.map.chipImageSize = 64;
	mGameData.map.chipImageHandle[kChipTypeBlock] = Novice::LoadTexture("./resource/images/map/block.png");

	mGameData.player.waitImage.handle = Novice::LoadTexture("./resource/images/player/wait.png");
	mGameData.player.runImage.handle = Novice::LoadTexture("./resource/images/player/run.png");
	mGameData.player.jumpImage.handle = Novice::LoadTexture("./resource/images/player/jump.png");
	mGameData.player.fallImage.handle = Novice::LoadTexture("./resource/images/player/fall.png");
	mGameData.player.dushImage.handle = Novice::LoadTexture("./resource/images/player/dushattack.png");
	mGameData.player.slashImage.handle = Novice::LoadTexture("./resource/images/player/slash.png");
	
	mGameData.boss.mainImage.handle = Novice::LoadTexture("./resource/images/boss/body.png");
	mGameData.boss.arm1Image.handle = Novice::LoadTexture("./resource/images/boss/arm1.png");
	mGameData.boss.arm2Image.handle = Novice::LoadTexture("./resource/images/boss/arm2.png");
	mGameData.boss.swordHandImage.handle = Novice::LoadTexture("./resource/images/boss/sword.png");
	mGameData.boss.gunHandImage.handle = Novice::LoadTexture("./resource/images/boss/agon2.png");
	mGameData.boss.headImage.handle = Novice::LoadTexture("./resource/images/boss/head.png");
	mGameData.boss.bulletImage.handle = Novice::LoadTexture("./resource/images/boss/bullet.png");


	mGameData.back.image = { 0,0,0,2560,2240 };
	mGameData.back.image.handle = Novice::LoadTexture("./resource/images/back.png");

	mGameData.HPBarHandle = Novice::LoadTexture("./resource/images/HPBar.png");

}


void Container::LoadBoss() {
	float size = (float)mGameData.map.chipSize;

	// Main
	mGameData.boss.mainImage.left = 0;
	mGameData.boss.mainImage.top = 0;
	mGameData.boss.mainImage.width = 256;
	mGameData.boss.mainImage.height = 256;
	mGameData.boss.mainImageQuad = ToQuad({ {-size * 4.0f, size * 4.0f }, size * 8.0f, size * 8.0f });
	mGameData.boss.position = { mGameData.map.mapWidth / 2.0f,800 };
	mGameData.boss.angle = 0.0f;
	mGameData.boss.scale = 1.7f;

	float scale = mGameData.boss.scale;

	mGameData.boss.armLength = size * 5.0f * scale;
	float arm2Len = size * 4.0f * scale;
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
	mGameData.boss.arm2ImageQuad = ToQuad({ Vec2{ 0, size * 1.25f } *scale, (arm2Len +18 * scale), size * 2.5f * scale }).SideFlip();

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
	mGameData.boss.gunHandImageQuad = ToQuad({ { -size * 1.0f * scale * handScale, size * 3.0f * scale * handScale}, size * 6.0f * scale * handScale, size * 6.0f * scale * handScale }).SideFlip();

	mGameData.boss.headImage = { 0,0,0,128,128 };
	mGameData.boss.headImageQuad = ToQuad({ {-size * 3.0f, size * 3.0f },size * 6,size * 6 });
	mGameData.boss.headPos = { 0,size * 4.0f };


	mGameData.boss.root[0] = Vec2{-2,1}.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[1] = Vec2{ 2,1 }.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[2] = Vec2{ -2,-1 }.Normalized() * mGameData.boss.rootLength;
	mGameData.boss.root[3] = Vec2{ 2,-1 }.Normalized() * mGameData.boss.rootLength;
	
	mGameData.boss.bodyAttackPower = 10.0f;

	mGameData.boss.startHitPoint = 1000.0f;

	mGameData.boss.hitRect.body = { {-size * 4.0f, size * 4.0f }, size * 8.0f, size * 8.0f };
	mGameData.boss.hitRect.head = { {-size * 3.0f, size * 3.0f },size * 6,size * 6 };
	mGameData.boss.hitRectLen = size * 3.0f * scale * handScale;
	mGameData.boss.hitRect.hand[0] = { { -size * 1.5f * scale * handScale, size * 1.5f * scale * handScale}, size * 3.0f * scale * handScale, size * 3.0f * scale * handScale };
	mGameData.boss.hitRect.hand[1] = { { -size * 1.5f * scale * handScale, size * 1.5f * scale * handScale}, size * 3.0f * scale * handScale, size * 3.0f * scale * handScale };
	mGameData.boss.hitRect.hand[2] = { { -size * 1.5f * scale * handScale, size * 1.5f * scale * handScale}, size * 3.0f * scale * handScale, size * 3.0f * scale * handScale };
	mGameData.boss.hitRect.hand[3] = { { -size * 1.5f * scale * handScale, size * 1.5f * scale * handScale}, size * 3.0f * scale * handScale, size * 3.0f * scale * handScale };

	mGameData.boss.bulletImage = { 0,0,0,64,64 };
	mGameData.boss.bulletImageQuad = ToQuad({ {-16,16},32,32 });
	mGameData.boss.bulletHitRect = { {-14,14},28,28 };
	mGameData.boss.bulletSpeed = 200.0f;
	mGameData.boss.bulletAttackPower = 5.0f;
	mGameData.boss.bulletCoolTime = 0.8f;
	mGameData.boss.bulletMaxNum = 20;
	mGameData.boss.bulletAttackTime = 10.0f;
	mGameData.boss.patternTime = 10.0f;

	mGameData.boss.invincibleTime = 0.5f;
	mGameData.boss.handStartHitPoint = 200.0f;
}