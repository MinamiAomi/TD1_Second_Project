#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include <Novice.h>
#include "ImageData.h"
#include "Shape.h"

class Camera :
    public GameObject {

public:
	struct InitData	{
		Vec2 windowCenter;
		Vec2 worldPosition;
		float scele;
		float theta;
	};

private:
	const Vec2 mWindowSize;
	Vec2 mWorldPosition; // ÉJÉÅÉâç¿ïW
	float mScale = 1.0f; // ÉYÅ[ÉÄî{ó¶
	float mTheta = 0.0f; // åXÇ´
	Matrix33 mMatrix;
	Matrix33 mInverseMatrix;
	Rect mDrawArea;

public:
	const Vec2& getWorldPosition() const { return mWorldPosition; }
	float getScale() const { return mScale; }
	float getTheta() const { return mTheta; }
	const Matrix33& getMatrix() const { return mMatrix; }
	const Matrix33& getInverseMatrix() const { return mInverseMatrix; }


	void setWorldPosition(const Vec2& pos) { mWorldPosition = pos; }
	void setScale(float sca) { mScale = sca; }
	void setTheta(float the) { mTheta = the; }

	const Rect& getDrawArea() const { return mDrawArea; }

	bool isInsideDrawArea(const Vec2& pos) const {
		return mDrawArea.isInsidePoint(pos);
	}

public:
	Camera(class Game* game);
	~Camera() {}

	void Create();
	void Update();

	void CalcData();

public:
	void DrawCircle(const Circle& circle, unsigned int color = WHITE, FillMode fillmode = kFillModeSolid) const;
	void DrawRect(const Rect& rect, unsigned int color = WHITE, FillMode fillmode = kFillModeSolid) const;
	void DrawRectAngle(const RectAngle& rectangle, unsigned int color = WHITE, FillMode fillmode = kFillModeSolid) const;
	void DrawTriangle(const Triangle& tri, unsigned int color = WHITE, FillMode fillmode = kFillModeSolid) const;
	void DrawQuad(const Quad& quad, unsigned int color = WHITE, FillMode fillmode = kFillModeSolid) const;
	void DrawLine(const Segment& seg, unsigned int color = WHITE) const;
	void DrawLine(const Segment& seg, float width, unsigned int color = WHITE) const;
	void DrawSprite(const Vec2& lefttop, int texturehandle, float scale, unsigned int color = WHITE) const;
	void DrawSpriteRect(const Rect& rect, const ImageData& image, unsigned int color = WHITE) const;
	void DrawSpriteRect(const RectAngle& rectangle, const ImageData& image, unsigned int color = WHITE) const;
	void DrawQuad(const Quad& quad, const ImageData& image, unsigned int color = WHITE) const;

#ifdef _DEBUG
	void debugMousePosition();
private:
	Vec2 dCurMousePosition;
	Vec2 dPreMousePosition;
#endif // _DEBUG
};

