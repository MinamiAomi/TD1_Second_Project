#include "Camera.h"
#include "Game.h"
#include "Container.h"
#include "DeltaTime.h"
#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


#define CAMERA_DATA getGame()->getContainer()->getCameraData()

constexpr float kScaleMin = 0.01f;

Camera::Camera(class Game* game) :
	GameObject(game) , mWindowSize((float)game->getContainer()->getWindow().kWidth, (float)game->getContainer()->getWindow().kHeight) {

}

void Camera::Create() {
	mWorldPosition = getGame()->getContainer()->getCameraData().worldPosition;
	mScale = getGame()->getContainer()->getCameraData().scele;
	mTheta = getGame()->getContainer()->getCameraData().theta;
	mDrawArea = { {mWorldPosition.x - mWindowSize.x / 2.0f,mWorldPosition.y + mWindowSize.y / 2.0f },mWindowSize.x,mWindowSize.y };
	lerp.SetParam(1.0f);
}

void Camera::Update() {
	Vec2 ppos = PLAYER->getPosition();
	mWorldPosition = ppos;
	mWorldPosition.x = Math::Clamp<float>(mWorldPosition.x, CAMERA_DATA.scrollMin.x, CAMERA_DATA.scrollMax.x);
	mWorldPosition.y = Math::Clamp<float>(mWorldPosition.y, CAMERA_DATA.scrollMin.y, CAMERA_DATA.scrollMax.y);

#ifdef _DEBUG
	if (Game::_debugMode) {
		constexpr float zoomSpeed = 0.03f;
		constexpr float rotateSpeed = Math::ToRadians(1.0f);
		int n = Math::GetSign(Novice::GetWheel());
		if (Novice::IsPressMouse(1)) {
			mTheta += rotateSpeed * n;
		} else {
			mScale += zoomSpeed * n;
		}
		if (mScale < kScaleMin) {
			mScale = kScaleMin;
		}
		if(Novice::IsPressMouse(0)){
			mWorldPosition += (dPreMousePosition - dCurMousePosition) / mScale;
		}

	}
#endif // _DEBUG

	
	if (mScale < kScaleMin) {
		mScale = kScaleMin;
	}

	CalcData();

#ifdef _DEBUG
	if (Game::_debugMode) {
		Debug::Print("Scale  : %8.2f  |  Theta   : %8.2f", mScale, mTheta);
		Debug::Print("Left   : %8.2f  |  Right   : %8.2f", mDrawArea.Left(), mDrawArea.Right());
		Debug::Print("Top    : %8.2f  |  Bottom  : %8.2f", mDrawArea.Top(), mDrawArea.Bottom());
		Debug::Print("width  : %8.2f  |  height  : %8.2f", mDrawArea.width, mDrawArea.height);
	}
#endif // _DEBUG
}

void Camera::CalcData() {
	// 画面に映る範囲
	Vec2 drawRange = mWindowSize / mScale;
	mDrawArea = { {mWorldPosition.x - drawRange.x / 2.0f,mWorldPosition.y + drawRange.y / 2.0f }, drawRange.x, drawRange.y };
	
	mMatrix.SetIdentity();
	// 画面の中心で拡縮回転
	mMatrix *= Matrix33::MakeTranslation(-mWorldPosition);
	mMatrix *= Matrix33::MakeScaling(mScale);
	mMatrix *= Matrix33::MakeRotation(mTheta);
	// スクロール
	mMatrix *= Matrix33::MakeTranslation(getGame()->getContainer()->getCameraData().worldPosition);
	// デカルト座標からスクリーン座標
	mMatrix *= Matrix33::MakeScaling(1, -1);
	mMatrix *= Matrix33::MakeTranslation(0, (float)getGame()->getContainer()->getWindow().kHeight);
	
	mInverseMatrix = Matrix33::MakeInverse(mMatrix);
}

#ifdef _DEBUG
void Camera::debugMousePosition() {
	int x = 0, y = 0;
	Novice::GetMousePosition(&x, &y);
	Vec2 tmp((float)x, (float)y);

	dPreMousePosition = dCurMousePosition;
	dCurMousePosition = { tmp.x, (tmp.y - 720) * -1 };
}
#endif // _DEBUG

void Camera::DrawCircle(const Circle& circle, unsigned int color, FillMode fillmode )  const {
	Vec2 center(circle.position * mMatrix);
	float radius = circle.radius * mScale;
	Novice::DrawEllipse((int)center.x, (int)center.y, (int)radius, (int)radius, 0.0f, color, fillmode);
}
void Camera::DrawRect(const Rect& rect, unsigned int color, FillMode fillmode)  const {
	this->DrawQuad(ToQuad(rect), color, fillmode);
}
void Camera::DrawRectAngle(const RectAngle& rectangle, unsigned int color, FillMode fillmode) const {
	this->DrawQuad(ToQuad({ rectangle.getRect(),rectangle.theta }), color, fillmode);
}
void Camera::DrawTriangle(const Triangle& tri, unsigned int color, FillMode fillmode) const {
	constexpr int kVertexNum = 3;
	Vec2 vert[kVertexNum] = {
		tri.vertex_1 * mMatrix,
		tri.vertex_2 * mMatrix,
		tri.vertex_3 * mMatrix, };
	Novice::DrawTriangle((int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y, color, fillmode);
}
void Camera::DrawQuad(const Quad& quad, unsigned int color, FillMode fillmode) const {
	constexpr int kVertexNum = 4;
	Vec2 vert[kVertexNum] = {
		quad.leftTop * mMatrix,
		quad.rightTop * mMatrix,
		quad.leftBottom * mMatrix,
		quad.rightBottom * mMatrix };
	Novice::DrawBox((int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y, color, fillmode);
}

void Camera::DrawLine(const Segment& seg, unsigned int color) const {
	Vec2 sta(seg.startPosition * mMatrix);
	Vec2 end(seg.endPosition * mMatrix);
	Novice::DrawLine((int)sta.x, (int)sta.y, (int)end.x, (int)end.y, color);
}

void Camera::DrawLine(const Segment& seg, float width, unsigned int color) const {
	Vec2 norm = seg.getVector().Normalized();
	Vec2 upper = norm.Normal() * width;
	Vec2 lower = norm.NegNormal() * width;
	this->DrawQuad({ seg.startPosition + upper,seg.endPosition + upper,seg.startPosition + lower,seg.endPosition + lower }, color);
}

void Camera::DrawSprite(const Vec2& lefttop, int texturehandle, float scale, unsigned int color) const {
	Vec2 pos = lefttop * mMatrix;
	Novice::DrawSprite((int)pos.x, (int)pos.y, texturehandle, scale * mScale, scale * mScale, -mTheta, color);
}

void Camera::DrawSpriteRect(const Rect& rect, const ImageData& image, unsigned int color) const{
	Vec2 lefttop = rect.leftTop * mMatrix;
	Novice::DrawSpriteRect(
		(int)lefttop.x, (int)lefttop.y, (int)(rect.width * mScale), (int)(rect.height * mScale),
		image.left, image.top, image.width, image.height,
		image.handle, -mTheta, color);
}

void Camera::DrawSpriteRect(const RectAngle& rectangle, const ImageData& image, unsigned int color) const {
	Vec2 lefttop = rectangle.leftTop * mMatrix;
	Novice::DrawSpriteRect(
		(int)lefttop.x, (int)lefttop.y, (int)(rectangle.width * mScale), (int)(rectangle.height * mScale),
		image.left, image.top, image.width, image.height,
		image.handle, -(rectangle.theta + mTheta), color);
}

void Camera::DrawQuad(const Quad& quad, const ImageData& image, unsigned int color, int animeCount) const {
	constexpr int kVertexNum = 4;
	Vec2 vert[kVertexNum] = {
		quad.leftTop * mMatrix,
		quad.rightTop * mMatrix,
		quad.leftBottom * mMatrix,
		quad.rightBottom * mMatrix };
	Novice::DrawQuad(
		(int)vert[0].x, (int)vert[0].y,
		(int)vert[1].x, (int)vert[1].y,
		(int)vert[2].x, (int)vert[2].y,
		(int)vert[3].x, (int)vert[3].y,
		image.left + image.width * animeCount, image.top, image.width, image.height,
		image.handle, color);
}
