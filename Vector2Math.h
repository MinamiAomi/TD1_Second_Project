#pragma once
#include <math.h>
#include <assert.h>

enum Direction_2D {
	kDirectionNone		=   0, // 方向なし
	kDirectionLeft		= - 1, // 左
	kDirectionRight		=   1, // 右
	kDirectionUp		=  10, // 上
	kDirectionLeftUp	=   9, // 左上
	kDirectionRightUp	=  11, // 右上
	kDirectionDown		= -10, // 下
	kDirectionLeftDown	= -11, // 左下
	kDirectionRightDown	= - 9, // 右下
	
	kDirectionNum = 9
};


// Vector2
class Vec2 {


public:
	float x; // x成分
	float y; // y成分


	Vec2(float x = 0, float y = 0) : x(x), y(y) {}
	Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {}

#pragma region 演算子
	// 単項演算子オーバーロード
	Vec2 operator+() const { return { x,y }; }
	Vec2 operator-() const { return { -x,-y }; }

	// 代入演算子オーバーロード
	Vec2& operator+=(const Vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	Vec2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}
	friend inline Vec2 operator+(const Vec2& v1, const Vec2& v2) {
		return { v1.x + v2.x, v1.y + v2.y };
	}
	friend inline Vec2 operator-(const Vec2& v1, const Vec2& v2) {
		return { v1.x - v2.x, v1.y - v2.y };
	}
	friend inline Vec2 operator*(const Vec2& v1, float s) {
		return { v1.x * s, v1.y * s };
	}
	friend inline Vec2 operator/(const Vec2& v1, float s) {
		assert(s != 0.0f); // 0除算確認
		return { v1.x / s, v1.y / s };
	}
	friend inline Vec2 operator*(float s, const Vec2& v1) {
		return { s * v1.x, s * v1.y };
	}
	friend inline Vec2 operator*(const Vec2& v1, const Vec2& v2) {
		return { v1.x * v2.x, v1.y * v2.y };
	}
	friend inline bool operator==(const Vec2& v1, const Vec2& v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}
	friend inline bool operator!=(const Vec2& v1, const Vec2& v2) {
		return v1.x != v2.x && v1.y != v2.y;
	}
#pragma endregion

	inline Vec2 AddX(float x) const {
		return { this->x + x, this->y };
	}
	inline Vec2 AddY(float x) const {
		return { this->x , this->y + y };
	}
	inline Vec2 Add(float x,float y) const {
		return { this->x + x , this->y + y };
	}
	// ゼロにする
	inline void SetZero() {
		x = 0;
		y = 0;
	}
	// ゼロであるか
	inline bool IsZero() const  {
		return { x == 0.0f && y == 0.0f };
	}
	// 内積
	inline float Dot(const Vec2& v) const {
		return x * v.x + y * v.y;
	}
	// 外積
	inline float Cross(const Vec2& v) const {
		return x * v.y - y * v.x;
	}
	// 長さの二乗
	inline float LengthSquare() const {
		return Dot(*this);
	}
	// 長さ
	inline float Length() const {
		return sqrtf(LengthSquare());
	}
	// 他ベクトルとの距離
	inline float Distance(const Vec2& v) const {
		return (v - *this).Length();
	}
	// なす角
	inline float Angle() const {
		return atan2f(y, x);
	}
	// 正規化
	inline Vec2 Normalized() const {
		assert(!IsZero()); // 長さが0出ないか確認
		float len = Length();
		return *this / len; 
	}
	// ベクトルの90°側の側法線
	inline Vec2 Normal() const {
		return { -y, x };
	}
	// ベクトルの‐90°側の側法線
	inline Vec2 NegNormal() const {
		return { y, -x };
	}
	// 中点
	inline Vec2 Mid(const Vec2& v) const {
		return (*this + v) / 2.0f;
	}
	// 回転
	inline Vec2 Rotated(float theta) const {
		float s = sinf(theta);
		float c = cosf(theta);
		return { x * c + y * -s, x * s + y * c };
	}
	// 拡縮
	inline Vec2 Magnituded(float length) const {
		return Normalized() * length;
	}
	// 反射ベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vec2 Reflected(const Vec2& normal) const {
		return normal.Dot(-(*this)) * 2 * normal + *this;
	}
	// 壁ずりベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vec2 AlongWall(const Vec2& normal) const {
		return normal.Dot(-(*this))* normal + *this;
	}
	// 線形補間
	static inline Vec2 Lerp(float t, const Vec2& start, const Vec2& end) {
		return start + t * (end - start);
	}
	static inline Vec2 MakeDirection(float theta) {
		return Vec2( 1.0f, 0.0f ).Rotated(theta);
	}
	Direction_2D Direction() const {
		int signx = (x > 0) - (x < 0);
		int signy = (y > 0) - (y < 0);

		return static_cast<Direction_2D>(signy * 10 + signx);
	}
	// ベジェ
	/// <summary>
	/// 3次ベジェ曲線
	/// </summary>
	/// <param name="t">媒介変数</param>
	/// <param name="start">始点</param>
	/// <param name="control1">制御点１</param>
	/// <param name="control2">制御点２</param>
	/// <param name="end">終点</param>
	/// <returns></returns>
	static inline Vec2 CalcCubicBezierCurve(float t, const Vec2& start, const Vec2& control1, const Vec2& control2, const Vec2& end) {
		float s = 1.0f - t;
		return (powf(s, 3) * start) + (3 * powf(s, 2) * t * control1) + (3 * s * powf(t, 2) * control2) + powf(t, 3) * end;
	}

	/// <summary>
	/// 微分3次ベジェ曲線
	/// </summary>
	/// <param name="t"></param>
	/// <param name="start"></param>
	/// <param name="control1"></param>
	/// <param name="control2"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	static inline Vec2 DiffCubicBezierCurve(float t, const Vec2& start, const Vec2& control1, const Vec2& control2, const Vec2& end) {
		return 3 * (-start + 3 * control1 - 3 * control2 + end) * powf(t, 2.0f) + 6 * (start - 2 * control1 + control2) * t + 3 * (-start + control1);
	}

};

static const Vec2 kZeroVector2 = { 0.0f, 0.0f };