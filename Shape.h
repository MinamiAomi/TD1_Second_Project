#pragma once
#include "Vector2Math.h"
#include "Lerp.h"
#include "MyMath.h"
#include <Novice.h>
enum ShapeType {
	kShapeTypeCircle,
	kShapeTypeRect,
	kShapeTypeRectAngle,
	kShapeTypeTriangle,
	kShapeTypeQuad,
	kShapeTypeSegment,

	kShapeTypeNum
};

class Shape {

public:
	virtual ~Shape() {}

	virtual ShapeType getType() const = 0;
};

class Circle : public Shape {

public:
	Vec2 position;
	float radius;

public:
	Circle() : radius(0.0f) {}
	Circle(const Vec2& pos, float rad) : position(pos), radius(rad) {}
	~Circle() {}

	ShapeType getType() const { return kShapeTypeCircle; }
};

class Rect : public Shape {

public:
	Vec2 leftTop;
	float width;
	float height;

public:
	Rect() : width(0.0f), height(0.0f) {}
	Rect(const Vec2& lft, float wid, float hei) 
		: leftTop(lft), width(wid), height(hei) {}
	virtual ~Rect() {}

	float Left() const { return leftTop.x; }
	float Right() const { return leftTop.x + width; }
	float Top() const { return leftTop.y; }
	float Bottom() const { return leftTop.y - height; }

	const Vec2& LeftTop() const { return leftTop; }
	Vec2 RightTop() const { return { Right(), Top() }; }
	Vec2 LeftBottom() const { return { Left(), Bottom() }; }
	Vec2 RightBottom() const { return { Right(), Bottom() }; }

	bool isInsidePoint(const Vec2& point) const {
		return Left() <= point.x && point.x <= Right() &&
			Bottom() <= point.y && point.y <= Top();
	}

	Rect Translation(const Vec2& vec) const {
		return { leftTop + vec, width,height };
	}

	static Rect CreateCenter(float sizex, float sizey) {
		return { {-sizex / 2.0f,sizey / 2.0f},sizex,sizey };
	}
	static Rect CreateCenter(float size) {
		return CreateCenter(size, size);
	}
	static Rect CreateCenter(const Vec2& size) {
		return CreateCenter(size.x, size.y);
	}


	ShapeType getType() const { return kShapeTypeRect; }
};

class RectAngle : public Rect {

public:
	float theta;

public:
	RectAngle() : theta(0.0f) {}
	RectAngle(const Vec2& lft, float wid, float hei, float the) 
		: Rect(lft, wid, hei), theta(the) {}
	RectAngle(const Rect& rect, float the) : Rect(rect), theta(the) {}
	~RectAngle() {}

	ShapeType getType() const { return kShapeTypeRectAngle; }
	Rect getRect() const { return{ leftTop,width,height }; }
};

class Triangle : public Shape {

public:
	Vec2 vertex_1, vertex_2, vertex_3;

public:
	Triangle() {}
	Triangle(const Vec2& v1, const Vec2& v2, const Vec2& v3) 
		: vertex_1(v1), vertex_2(v2), vertex_3(v3) {}
	~Triangle() {}

	ShapeType getType() const { return kShapeTypeTriangle; }
};

class Quad : public Shape {

public:
	Vec2 leftTop, rightTop, leftBottom, rightBottom;

public:
	Quad() {}
	Quad(const Vec2& lt, const Vec2& rt, const Vec2& lb, const Vec2& rb) 
		: leftTop(lt), rightTop(rt), leftBottom(lb), rightBottom(rb) {}
	~Quad() {}

	Quad SideFlip() const {
		return { rightTop,leftTop,rightBottom,leftBottom };
	}
	Quad VerticalFlip() const {
		return { leftBottom,rightBottom,leftTop,rightTop };
	}
	Quad TransForm(const Matrix33& mat) const {
		return { leftTop * mat,rightTop * mat, leftBottom * mat, rightBottom * mat };
	}
	Quad TransForm(const Vec2& vec) const {
		return { leftTop + vec,rightTop + vec, leftBottom + vec, rightBottom + vec };
	}
	Quad TransForm(const Vec2& vec, float angle) const {
		Matrix33 mat = Matrix33::MakeRotation(angle) * Matrix33::MakeTranslation(vec);
		return { leftTop * mat,rightTop * mat, leftBottom * mat, rightBottom * mat };
	}
	ShapeType getType() const { return kShapeTypeQuad; }
};

class Segment : public Shape {

public:
	Vec2 startPosition, endPosition;

public:
	Segment() {}
	Segment(const Vec2& sta, const Vec2& end) : startPosition(sta), endPosition(end) {}
	~Segment() {}

	Vec2 getVector() const { return endPosition - startPosition; }

	//
	bool Intersect(const Segment& uther) const {
		auto f = [](const Vec2& p1, const Vec2& p2, const Vec2& p3) {
			return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
		};

		float t1 = f(this->startPosition, this->endPosition, uther.startPosition);
		float t2 = f(this->startPosition, this->endPosition, uther.endPosition);
		float t3 = f(uther.startPosition, uther.endPosition, this->startPosition);
		float t4 = f(uther.startPosition, uther.endPosition, this->endPosition);

		return  t1 * t2 <= 0.0f && t3 * t4 <= 0.0f;
	}

	Vec2 Intersection(const Segment& uther) const {
		float det = (this->startPosition.x - this->endPosition.x) * (uther.endPosition.y - uther.startPosition.y) - (uther.endPosition.x - uther.startPosition.x) * (this->startPosition.y - this->endPosition.y);
		float t = ((uther.endPosition.y - uther.startPosition.y) * (uther.endPosition.x - this->endPosition.x) + (uther.startPosition.x - uther.endPosition.x) * (uther.endPosition.y - this->endPosition.y)) / det;
		return	Lerp<Vec2>::Calc(t, this->startPosition, this->endPosition);
	}

	ShapeType getType() const { return kShapeTypeSegment; }
};

// Rect ‚©‚ç Quad
inline Quad ToQuad(const Rect& rect) {
	return {
		rect.LeftTop(),
		rect.RightTop(),
		rect.LeftBottom(),
		rect.RightBottom()
	};
}
// RectAngle ‚©‚ç Quad
inline Quad ToQuad(const RectAngle& rect) {
	Matrix33 mat;
	mat.MultiplyRotation(rect.theta);
	mat.MultiplyTranslation(rect.leftTop);
	return {
		Matrix33::MultiplyVector2({}, mat),
		Matrix33::MultiplyVector2({ rect.width, 0.0f }, mat),
		Matrix33::MultiplyVector2({ 0.0f, -rect.height }, mat),
		Matrix33::MultiplyVector2({ rect.width, -rect.height }, mat)
	};
}