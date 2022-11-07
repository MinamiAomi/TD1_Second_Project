#pragma once
#include "Vector2Math.h"
#include <math.h>

class Matrix33 {

private:
	float m[3][3];

public:
	Matrix33(
		float _11 = 1.0f, float _12 = 0.0f, float _13 = 0.0f,
		float _21 = 0.0f, float _22 = 1.0f, float _23 = 0.0f,
		float _31 = 0.0f, float _32 = 0.0f, float _33 = 1.0f) {
		m[0][0] = _11, m[0][1] = _12, m[0][2] = _13;
		m[1][0] = _21, m[1][1] = _22, m[1][2] = _23;
		m[2][0] = _31, m[2][1] = _32, m[2][2] = _33;
	}

	float Determinant() const {
		float det = m[0][0] * m[1][1] * m[2][2];
		det += m[1][0] * m[2][1] * m[0][2];
		det += m[2][0] * m[0][1] * m[1][2];
		det -= m[2][0] * m[1][1] * m[0][2];
		det -= m[1][0] * m[0][1] * m[2][2];
		det -= m[0][0] * m[1][1] * m[1][2];
		return det;
	}

	friend inline Matrix33 operator*(const Matrix33& mat1, const Matrix33& mat2) {
		return {
			mat1.m[0][0] * mat2.m[0][0] + mat1.m[0][1] * mat2.m[1][0] + mat1.m[0][2] * mat2.m[2][0],
			mat1.m[0][0] * mat2.m[0][1] + mat1.m[0][1] * mat2.m[1][1] + mat1.m[0][2] * mat2.m[2][1],
			mat1.m[0][0] * mat2.m[0][2] + mat1.m[0][1] * mat2.m[1][2] + mat1.m[0][2] * mat2.m[2][2],

			mat1.m[1][0] * mat2.m[0][0] + mat1.m[1][1] * mat2.m[1][0] + mat1.m[1][2] * mat2.m[2][0],
			mat1.m[1][0] * mat2.m[0][1] + mat1.m[1][1] * mat2.m[1][1] + mat1.m[1][2] * mat2.m[2][1],
			mat1.m[1][0] * mat2.m[0][2] + mat1.m[1][1] * mat2.m[1][2] + mat1.m[1][2] * mat2.m[2][2],

			mat1.m[2][0] * mat2.m[0][0] + mat1.m[2][1] * mat2.m[1][0] + mat1.m[2][2] * mat2.m[2][0],
			mat1.m[2][0] * mat2.m[0][1] + mat1.m[2][1] * mat2.m[1][1] + mat1.m[2][2] * mat2.m[2][1],
			mat1.m[2][0] * mat2.m[0][2] + mat1.m[2][1] * mat2.m[1][2] + mat1.m[2][2] * mat2.m[2][2]
		};
	}

	inline Matrix33& operator*=(const Matrix33& mat) {
		*this = *this * mat;
		return *this;
	}

	friend inline Vec2 operator*(const Vec2& vec, const Matrix33& mat) {
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + 1.0f * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + 1.0f * mat.m[2][1]
		};
	}

	static inline Vec2 MultiplyVector2(const Vec2& vec, const Matrix33& mat) {
		return vec * mat;
	}

	// ’PˆÊs—ñ
	static inline Matrix33 MakeIdentity() {
		return {
			1,		0,		0,
			0,		1,		0,
			0,		0,		1
		};
	}
// MakeŠÖ”
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(float scaleX, float scaleY) {
		return {
			scaleX, 0,		0,
			0,		scaleY,	0,
			0,		0,		1
		};
	}
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(float scale) {
		return MakeScaling(scale, scale);
	}
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(const Vec2& scale) {
		return MakeScaling(scale.x, scale.y);
	}
	// ‰ñ“]s—ñ
	static inline Matrix33 MakeRotation(float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return {
			c,		s,		0,
			-s,		c,		0,
			0,		0,		1
		};
	}
	// •½sˆÚ“®s—ñ
	static inline Matrix33 MakeTranslation(float vecX, float vecY) {
		return {
			1,		0,		0,
			0,		1,		0,
			vecX,	vecY,	1
		};
	}
	// •½sˆÚ“®s—ñ
	static inline Matrix33 MakeTranslation(const Vec2& vector) {
		return MakeTranslation(vector.x, vector.y);
	}
	// ƒAƒtƒBƒ“•ÏŠ·s—ñ
	static inline Matrix33 MakeAffine(float scaleX, float scaleY, float theta, float vecX, float vecY) {
		float s = sinf(theta);
		float c = cosf(theta);
		return {
			scaleX * c,		scaleX * s,		0,
			scaleY * -s,	scaleY * c,		0,
			vecX,			vecY,			1
		};
	}
	// ƒAƒtƒBƒ“•ÏŠ·s—ñ
	static inline Matrix33 MakeAffine(float scale, float theta, const Vec2& vec) {
		return MakeAffine(scale, scale, theta, vec.x, vec.y);
	}
	// ƒAƒtƒBƒ“•ÏŠ·s—ñ
	static inline Matrix33 MakeAffine(const Vec2& scale, float theta, const Vec2& vec) {
		return MakeAffine(scale.x, scale.y, theta, vec.x, vec.y);
	}

	static inline Matrix33 MakeInverse(const Matrix33& matrix) {
		Matrix33 mat = matrix;
		Matrix33 inv;
		float buf = 0;
		for (int i = 0; i < 3; i++) {
			buf = 1 / mat.m[i][i];
			for (int j = 0; j < 3; j++) {
				mat.m[i][j] *= buf;
				inv.m[i][j] *= buf;
			}
			for (int j = 0; j < 3; j++) {
				if (i != j) {
					buf = mat.m[j][i];
					for (int k = 0; k < 3; k++) {
						mat.m[j][k] -= mat.m[i][k] * buf;
						inv.m[j][k] -= inv.m[i][k] * buf;
					}
				}
			}
		}
		return inv;
	}

// SetŠÖ”
	// ’PˆÊs—ñ‚É‚·‚é
	inline void SetIdentity() {
		*this = MakeIdentity();
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(float scaleX, float scaleY) {
		*this = MakeScaling(scaleX, scaleY);
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(float scale) {
		*this = MakeScaling(scale);
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(const Vec2& scale) {
		*this = MakeScaling(scale);
	}
	// ‰ñ“]s—ñ‚É‚·‚é
	inline void SetRotation(float theta) {
		*this = MakeRotation(theta);
	}
	// •½sˆÚ“®s—ñ‚É‚·‚é
	inline void SetTranslation(float vecX, float vecY) {
		*this = MakeTranslation(vecX, vecY);
	}
	// •½sˆÚ“®s—ñ‚É‚·‚é
	inline void SetTranslation(const Vec2& vector) {
		*this = MakeTranslation(vector);
	}
	// ƒAƒtƒBƒ“•ÏŠ·s—ñ‚É‚·‚é
	inline void SetAffine(float scale, float theta, const Vec2& vec) {
		*this = MakeAffine(scale, theta, vec);
	}
	// ƒAƒtƒBƒ“•ÏŠ·s—ñ‚É‚·‚é
	inline void SetAffine(const Vec2& scale, float theta, const Vec2& vec) {
		*this = MakeAffine(scale, theta, vec);
	}
// •ÏŠ·s—ñ‚Æ‚ÌŠ|‚¯Z(Œø—¦“I)
	// Šg‘åk¬s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyScaling(float scaleX, float scaleY) {
		// |  _00  _01  0  |   |  X  0  0  |   |  _00X  _01Y  0  |
		// |  _10  _11  0  | * |  0  Y  0  | = |  _10X  _11Y  0  |
		// |  _20  _21  1  |   |  0  0  1  |   |  _20   _21   1  |
		m[0][0] *= scaleX; m[0][1] *= scaleY;
		m[1][0] *= scaleX; m[1][1] *= scaleY;
	}
	// Šg‘åk¬s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyScaling(float scale) {
		MultiplyScaling(scale, scale);
	}
	// Šg‘åk¬s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyScaling(const Vec2& scale) {
		MultiplyScaling(scale.x, scale.y);
	}
	// ‰ñ“]s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyRotation(float theta) {
		// |  _00  _01  0  |   |   c  s  0  |   | _00c+_01(-s)  _00s+_01c  0  |
		// |  _10  _11  0  | * |  -s  c  0  | = | _10c+_11(-s)  _10s+_11c  0  |
		// |  _20  _21  1  |   |   0  0  1  |   |          _20        _21  1  |
		float s = sinf(theta);
		float c = cosf(theta);
		float tmp;
		tmp = m[0][0] * c + m[0][1] * -s;
		m[0][1] = m[0][0] * s + m[0][1] * c;
		m[0][0] = tmp;

		tmp = m[1][0] * c + m[1][1] * -s;
		m[1][1] = m[1][0] * s + m[1][1] * c;
		m[1][0] = tmp;
	}	
	// •½sˆÚ“®s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyTranslation(float vecX, float vecY) {
		// |  _00  _01  0  |   |  1  0  0  |   | _00    _01    0  |
		// |  _10  _11  0  | * |  0  1  0  | = | _10	_11    0  |
		// |  _20  _21  1  |   |  X  Y  1  |   | _20+X  _21+Y  1  |
		m[2][0] += vecX;
		m[2][1] += vecY;
	}
	// •½sˆÚ“®s—ñ‚Æ‚ÌŠ|‚¯Z
	void inline MultiplyTranslation(const Vec2& vector) {
		MultiplyTranslation(vector.x, vector.y);
	}
};