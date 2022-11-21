#pragma once
#include "Vector2Math.h"
#include "Matrix33.h"
#include <math.h>
#include <limits>
#include "SinCosTable.h"


struct TransForm
{
	Vec2 pos;
	float angle = 0.0f;
	float scale = 1.0f;


	TransForm* parent = nullptr;

	Matrix33 GetMatrix() const {
		return Matrix33::MakeScaling(scale) * Matrix33::MakeRotation(angle) * Matrix33::MakeTranslation(pos);
	}
	Matrix33 GetParentMatrix() const {
		return parent->GetConnectMatrix();
	}
	Matrix33 GetConnectMatrix() const {
		if (parent == nullptr) {
			return GetMatrix();
		}
		return GetMatrix() * parent->GetConnectMatrix();
	}

};


namespace Math
{

	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 2.0f * Pi;
	constexpr float Inf = std::numeric_limits<float>::infinity();
	constexpr float NegInf = -std::numeric_limits<float>::infinity();


	/// <summary>
	/// �ʓx�@�ϊ�
	/// </summary>
	/// <param name="degrees">�x���@</param>
	/// <returns>�ʓx�@</returns>
	constexpr inline float ToRadians(float degrees) {
		return degrees * Pi / 180.0f;
	}
	/// <summary>
	/// �x���@�ϊ�
	/// </summary>
	/// <param name="radians">�ʓx�@</param>
	/// <returns>�x���@</returns>
	constexpr inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}
	/// <summary>
	/// �قڃ[��
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="epsilon">�덷</param>
	/// <returns>true : false</returns>
	inline bool NearZero(float value, float epsilon = 0.001f) {
		return fabs(value) <= epsilon;
	}
	/// <summary>
	/// �����𔻒f
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v">�l</param>
	/// <returns> 0��0 </returns>
	template <typename TYPE>
	int GetSign(TYPE v) {
		return (v > 0) - (v < 0);
	}
	/// <summary>
	/// �傫���ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Max(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v2 : v1;
	}
	/// <summary>
	/// �������ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Min(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v1 : v2;
	}
	/// <summary>
	/// �l�����߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="value">�l</param>
	/// <param name="lower">����</param>
	/// <param name="upper">���</param>
	/// <returns></returns>
	template <typename TYPE>
	TYPE Clamp(const TYPE& value, const TYPE& lower, const TYPE& upper) {
		return Min(upper, Max(lower, value));
	}
	/// <summary>
	/// �l�����[�v������
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="range">�͈�</param>
	/// <param name="min">�ŏ�</param>
	/// <returns></returns>
	inline float Loop(float value, float range, float min = 0.0f) {
		float a = fmodf(value, range);
		if (a == 0) return a;
		return a > 0 ? a + min : a + min + range;
	}
	/// <summary>
	/// ��Βl
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Abs(float value) {
		return fabsf(value);
	}
	/// <summary>
	///	�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Sin(float angle) {
		return sinf(angle);
	}
	/// <summary>
	/// �R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Cos(float angle) {
		return cosf(angle);
	}
	/// <summary>
	/// �^���W�F���g
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Tan(float angle) {
		return tanf(angle);
	}
	/// <summary>
	/// �A�[�N�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Asin(float angle) {
		return asinf(angle);
	}
	/// <summary>
	/// �A�[�N�R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Acos(float angle) {
		return acosf(angle);
	}
	/// <summary>
	/// �A�[�N�^���W�F���g
	/// </summary>
	/// <param name="y">y����</param>
	/// <param name="x">x����</param>
	/// <returns>���W�A��</returns>
	inline float Atan2(float y, float x) {
		return atan2f(y, x);
	}
	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="t">�ω���</param>
	/// <param name="start">�X�^�[�g</param>
	/// <param name="end">�G���h</param>
	/// <returns></returns>
	inline float Lerp(float t, float start, float end) {
		return start + t * (end - start);
	}
	/// <summary>
	/// ���ݔ͈͂���ʂ͈̔͂ɕϊ�
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="start1">���ݔ͈͂̍ŏ�</param>
	/// <param name="end1">���ݔ͈͂̍ő�</param>
	/// <param name="start2">�ϊ��͈͂̍ŏ�</param>
	/// <param name="end2">�ϊ��͈͂̍ő�</param>
	/// <returns></returns>
	inline float Map(float value, float start1, float end1, float start2, float end2) {
		return start2 + (end1 - start2) * ((value - start1) / (end2 - start1));
	}
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Sqrt(float value) {
		return sqrtf(value);
	}
	/// <summary>
	/// float��]���Z
	/// </summary>
	/// <param name="number">�����鐔</param>
	/// <param name="denom">���鐔</param>
	/// <returns>�]��</returns>
	inline float Fmod(float number, float denom) {
		return fmodf(number, denom);
	}
	/// <summary>
	/// �p��
	/// </summary>
	/// <param name="base">��</param>
	/// <param name="exponent">�w��</param>
	/// <returns></returns>
	inline float Pow(float base, float exponent) {
		return powf(base, exponent);
	}

}

