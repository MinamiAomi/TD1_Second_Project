#pragma once
#include <math.h>

namespace Easing {
	constexpr float Pi = 3.14159265359f;

	// イージングの関数ポインタ
	typedef float (*easinc_func)(float);

	float EaseInSine(float x) {
		return 1.0f - cosf((x * Pi) / 2.0f);
	}

	float EaseOutSine(float x) {
		return sinf((x * Pi) / 2.0f);
	}

	float EaseInOutSine(float x) {
		return -(cosf(Pi * x) - 1.0f) / 2.0f;
	}

	float EaseInQuad(float x) {
		return x * x;
	}

	float EaseOutQuad(float x) {
		return 1.0f - (1.0f - x) * (1.0f - x);
	}

	float EaseInOutQuad(float x) {
		return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2.0f) / 2.0f;
	}

	float EaseInCubic(float x) {
		return x * x * x;
	}

	float EaseOutCubic(float x) {
		return 1.0f - powf(1.0f - x, 3.0f);
	}

	float EaseInOutCubic(float x) {
		return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f;
	}

	float EaseInQuart(float x) {
		return x * x * x * x;
	}

	float EaseOutQuart(float x) {
		return 1.0f - powf(1.0f - x, 4.0f);
	}

	float EaseInOutQuart(float x) {
		return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f;
	}

	float EaseInQuint(float x) {
		return x * x * x * x * x;
	}

	float EaseOutQuint(float x) {
		return 1.0f - powf(1.0f - x, 5.0f);
	}

	float EaseInOutQuint(float x) {
		return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f;
	}

	float EaseInExpo(float x) {
		return x = 0.0f ? 0.0f : powf(2.0f, 10.0f * x - 10.0f);
	}

	float EaseOutExpo(float x) {
		return x = 1.0f ? 1.0f : 1.0f - powf(2.0f, -10.0f * x);
	}

	float EaseInCirc(float x) {
		return 1.0f - sqrtf(1.0f - powf(x, 2.0f));
	}

	float EaseOutCirc(float x) {
		return sqrtf(1.0f - powf(x - 1.0f, 2.0f));
	}

	float EaseInOutCirc(float x) {
		return x < 0.5f
			? (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f
			: (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}

	float EaseInBack(float x) {
		constexpr float c1 = 1.70158f;
		constexpr float c3 = c1 + 1.0f;

		return c3 * x * x * x - c1 * x * x;
	}

	float EaseOutBack(float x) {
		constexpr float c1 = 1.70158f;
		constexpr float c3 = c1 + 1.0f;

		return 1.0f + c3 * powf(x - 1.0f, 3.0f) + c1 * powf(x - 1.0f, 2.0f);
	}

	float EaseInOutBack(float x) {
		const float c1 = 1.70158f;
		const float c2 = c1 * 1.525f;

		return x < 0.5f
			? (powf(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f
			: (powf(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
	}

	float EaseInElastic(float x) {
		constexpr float c4 = (2.0f * Pi) / 3.0f;

		return x == 0.0f
			? 0.0f
			: x == 1.0f
			? 1.0f
			: -powf(2.0f, 10.0f * x - 10.0f) * sinf((x * 10.0f - 10.75f) * c4);
	}

	float EaseOutElastic(float x) {
		constexpr float c4 = (2.0f * Pi) / 3.0f;

		return x == 0.0f
			? 0.0f
			: x == 1.0f
			? 1.0f
			: powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
	}

	float EaseInOutElastic(float x) {
		constexpr float c5 = (2.0f * Pi) / 4.5f;

		return x == 0.0f ? 0.0f : x == 1.0f ? 1.0f : x < 0.5f
			? -(powf(2.0f, 20.0f * x - 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f
			: (powf(2.0f, -20.0f * x + 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
	}
	
	float EaseOutBounce(float x) {
		constexpr float n1 = 7.5625f;
		constexpr float d1 = 2.75f;

		if (x < 1.0f / d1) {
			return n1 * x * x;
		}
		else if (x < 2.0f / d1) {
			return n1 * (x -= 1.5f / d1) * x + 0.75f;
		}
		else if (x < 2.5f / d1) {
			return n1 * (x -= 2.25f / d1) * x + 0.9375f;
		}
		else {
			return n1 * (x -= 2.625f / d1) * x + 0.984375f;
		}
	}

	float EaseInBounce(float x) {
		return 1.0f - EaseOutBounce(1.0f - x);
	}

	float EaseInOutBounce(float x) {
		return x < 0.5f
			? (1.0f - EaseOutBounce(1.0f - 2.0f * x)) / 2.0f
			: (1.0f + EaseOutBounce(2.0f * x - 1.0f)) / 2.0f;
	}

}
