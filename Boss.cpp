#include "Boss.h"
#include "Game.h"
#include "Container.h"
#include "Camera.h"

#include "Func.h"

#define BOSS_DATA getGame()->getContainer()->getBossData()

Boss::Boss(class Game* game) :
	GameObject(game)
{

}
Boss::~Boss() {


}

void Boss::Create() {
	mTransForm.pos = BOSS_DATA.position;
	mTransForm.angle = BOSS_DATA.angle;
	mTransForm.scale = BOSS_DATA.scale;
	TransForm tmp = { {0,0},0.0f,1.0f };
	for (int i = 0; i < kArmNum; i++) {
		mArm1[i] = { BOSS_DATA.root[i],0.0f,1.0f};
		mArm2[i] = { BOSS_DATA.root[i],0.0f,1.0f};
		mHand[i] = { BOSS_DATA.root[i] * 2,0.0f,1.0f };
	}
}

void Boss::Update() {

	

	Vec2 tmpHand = PLAYER->getPosition() - mArm2[0].pos - mArm1[0].pos - mTransForm.pos;
	mTragetPos[0] = PLAYER->getPosition();

	float len = BOSS_DATA.armLength;
	for (int i = 0; i < kArmNum; i++) {
	
		Vec2 endroot = mTragetPos[i] - mArm1[i].pos - mTransForm.pos;
		float A = endroot.Length();
		endroot = endroot.Normalized();
	
		float angleFromX = endroot.Angle();
		float theta = Math::Acos((A * A + len * len - len * len) / (2.0f * A * len)); 
		
		if (i % 2 == 0 ) {
			angleFromX += theta ;
		}
		else {
			angleFromX += -theta;
		}
		if (A < len * 2) {
			mArm2[i].pos = Vec2(Math::Cos(angleFromX), Math::Sin(angleFromX)) * len;
			mHand[i].pos = mTragetPos[i] - mArm2[i].pos - mArm1[i].pos - mTransForm.pos;
		}
		else {
			mArm2[i].pos = endroot * len;
			mHand[i].pos = endroot * len;
		}
	}

}


void Boss::Draw() {

	Matrix33 mat = mTransForm.GetMatrix();
	Quad bossQuad = BOSS_DATA.mainImageQuad.TransForm(mat);
	CAMERA->DrawQuad(bossQuad, BOSS_DATA.mainImage);



	Vec2 bossPos = mTransForm.pos;
	for (int i = 0; i < kArmNum; i++) {
		Vec2 arm1Pos = mArm1[i].pos + bossPos;
		Vec2 arm2Pos = mArm2[i].pos + arm1Pos;
		Vec2 handPos = mHand[i].pos + arm2Pos;
		CAMERA->DrawCircle({ arm1Pos, 20 });
		CAMERA->DrawCircle({ arm2Pos, 20 });
		CAMERA->DrawCircle({ handPos, 20 });
		
		CAMERA->DrawLine({ arm1Pos , arm2Pos });
		CAMERA->DrawLine({ arm2Pos , handPos });
				
	}

}