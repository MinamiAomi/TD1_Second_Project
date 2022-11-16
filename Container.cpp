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
	
	mGameData.boss.main.image.handle = Novice::LoadTexture("./resource/images/boss/test.png");
	int arm = Novice::LoadTexture("./resource/images/boss/arm.png");
	int hand = Novice::LoadTexture("./resource/images/boss/hand.png");
	mGameData.boss.armA1.image.handle = arm;
	mGameData.boss.armA2.image.handle = arm;
	mGameData.boss.handA.image.handle = hand;
	mGameData.boss.armB1.image.handle = arm;
	mGameData.boss.armB2.image.handle = arm;
	mGameData.boss.handB.image.handle = hand;
}


void Container::LoadBoss() {
	float size = (float)mGameData.map.chipSize;

	mGameData.boss.main.image.left = 0;
	mGameData.boss.main.image.top = 0;
	mGameData.boss.main.image.width = 512;
	mGameData.boss.main.image.height = 256;
	mGameData.boss.main.imageQuad = ToQuad({ {-size * 3.0f, size * 1.5f }, size * 6.0f, size * 3.0f });
	mGameData.boss.main.position = { 1280,500 };
	mGameData.boss.main.angle = 0.0f;
	mGameData.boss.main.scale = 1.0f;


	// A Arm
	mGameData.boss.armA1.image.left = 0;
	mGameData.boss.armA1.image.top = 0;
	mGameData.boss.armA1.image.width = 256;
	mGameData.boss.armA1.image.height = 128;
	mGameData.boss.armA1.imageQuad = ToQuad({ { 0, size * 0.75f }, -size * 3.0f, size * 1.5f });
	mGameData.boss.armA1.position = { -size * 4, 0 };
	mGameData.boss.armA1.angle = 0.0f;
	mGameData.boss.armA1.scale = 1.0f;

	mGameData.boss.armA2.image.left = 0;
	mGameData.boss.armA2.image.top = 0;
	mGameData.boss.armA2.image.width = 256;
	mGameData.boss.armA2.image.height = 128;
	mGameData.boss.armA2.imageQuad = ToQuad({ { 0, size * 0.75f }, -size * 3.0f, size * 1.5f });
	mGameData.boss.armA2.position = { -size * 4, 0 };
	mGameData.boss.armA2.angle = 0.0f;
	mGameData.boss.armA2.scale = 1.0f;

	mGameData.boss.handA.image.left = 0;
	mGameData.boss.handA.image.top = 0;
	mGameData.boss.handA.image.width = 512;
	mGameData.boss.handA.image.height = 512;
	mGameData.boss.handA.imageQuad = ToQuad({ { -size * 3.0f, size * 5.0f }, size * 6.0f, size * 6.0f });
	mGameData.boss.handA.position = { -size * 5, 0 };
	mGameData.boss.handA.angle = 0.0f;
	mGameData.boss.handA.scale = 1.0f;


	// B Arm
	mGameData.boss.armB1.image.left = 256;
	mGameData.boss.armB1.image.top = 0;
	mGameData.boss.armB1.image.width = -256;
	mGameData.boss.armB1.image.height = 128;
	mGameData.boss.armB1.imageQuad = ToQuad({ { 0, size * 0.75f }, size * 3.0f, size * 1.5f });
	mGameData.boss.armB1.position = { size * 4, 0 };
	mGameData.boss.armB1.angle = 0.0f;
	mGameData.boss.armB1.scale = 1.0f;

	mGameData.boss.armB2.image.left = 256;
	mGameData.boss.armB2.image.top = 0;
	mGameData.boss.armB2.image.width = -256;
	mGameData.boss.armB2.image.height = 128;
	mGameData.boss.armB2.imageQuad = ToQuad({ { 0, size * 0.75f }, size * 3.0f, size * 1.5f });
	mGameData.boss.armB2.position = { size * 4, 0 };
	mGameData.boss.armB2.angle = 0.0f;
	mGameData.boss.armB2.scale = 1.0f;

	mGameData.boss.handB.image.left = 512;
	mGameData.boss.handB.image.top = 0;
	mGameData.boss.handB.image.width = -512;
	mGameData.boss.handB.image.height = 512;
	mGameData.boss.handB.imageQuad = ToQuad({ { -size * 3.0f, size * 5.0f }, size * 6.0f, size * 6.0f });
	mGameData.boss.handB.position = { size * 5, 0 };
	mGameData.boss.handB.angle = 0.0f;
	mGameData.boss.handB.scale = 1.0f;

}