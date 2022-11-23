#pragma once
#include "MyMath.h"
#include "Shape.h"
class Collision 
{

private:
	Collision() = default;
	~Collision() = default;
	Collision(const Collision&) = delete;
	const Collision& operator=(const Collision&) = delete;

public:
	static bool PointCircle(const Vec2& p, const Circle& c) {
		return (p - c.position).LengthSquare() <= c.radius * c.radius;
	}
	static bool CircleCircle(const Circle& a, const Circle& b) {
		float rad = (a.radius + b.radius);
		return (a.position - b.position).LengthSquare() <= rad * rad;
	}
	static bool RectRect(const Rect& a, const Rect& b) {
		bool A = a.Left() < b.Right();
		bool B = b.Left() < a.Right();
		bool C = a.Top() > b.Bottom();
		bool D = b.Top() > a.Bottom();

		return a.Left() < b.Right() && b.Left() < a.Right() &&
			a.Top() > b.Bottom() && b.Top() > a.Bottom();
	}
	/*static bool RectCircle(const Rect& a, const Circle& b) {
		float bottom = a.Bottom();
		float right = a.Right();
		
		bool
			A = a.Top() + b.radius >= b.position.y,
			B = b.position.y >= bottom - b.radius,
			C = right >= b.position.x,
			D = b.position.x >= a.Left(),

			E = a.Top() >= b.position.y,
			F = b.position.y >= bottom,
			G = right + b.radius >= b.position.x,
			H = b.position.x >= a.Left() - b.radius,

	}*/
};