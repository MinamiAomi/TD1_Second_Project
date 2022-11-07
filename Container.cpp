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
}

void Container::LoadImages() {
	mGameData.particle.fadeStraight.image.handle = Novice::LoadTexture("./resource/images/partical2.png");
	mGameData.map.chipImageHandle[kChipTypeNone] = -1;
	mGameData.map.chipImageHandle[kChipTypeBlock] = Novice::LoadTexture("./resource/images/chipBlock.png");
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