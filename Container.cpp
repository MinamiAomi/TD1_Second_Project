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
	LoadMapCSV();
	mGameData.map.mapWidth = mGameData.map.chipSize * mGameData.map.chipRowNum;
	mGameData.map.mapHeight = mGameData.map.chipSize * mGameData.map.chipColmunNum;

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
	mGameData.player.dushAttakSpeed = 50000.0f;
	mGameData.player.dushAttakDistance = 250.0f;
	mGameData.player.dushAttakCoolTime = 1.5f;
}

void Container::LoadImages() {
	mGameData.particle.fadeStraight.image.handle = Novice::LoadTexture("./resource/images/partical2.png");
	mGameData.map.chipImageHandle[kChipTypeNone] = -1;
	mGameData.map.chipImageHandle[kChipTypeBlock] = Novice::LoadTexture("./resource/images/chipBlock.png");

	mGameData.player.image.handle = Novice::LoadTexture("white1x1.png");
}

void Container::LoadMapCSV() {
	FILE* fp = NULL;
	fopen_s(&fp, mGameData.map.fileName, "r");
	if (fp == NULL) {
		return;
	}
	fscanf_s(fp, "%d,", &mGameData.map.chipRowNum);
	fscanf_s(fp, "%d,", &mGameData.map.chipColmunNum);
	fclose(fp);
}