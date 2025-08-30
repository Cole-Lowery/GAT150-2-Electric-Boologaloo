#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace viper {
	namespace math {

		constexpr float pi = 3.1415926535897932384626433832795;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi * 0.5f;

		constexpr float radToDeg(float rad) { return rad * (180 / pi); }
		constexpr float degToRad(float deg) { return deg * (pi / 180); }

		constexpr int wrap(int value, int min, int max) {
			int range = max - min;
			int result = (value - min) % range;
			if (result < 0) result += range;

			return min + result;
		}

		inline float wrap(float value, float min, float max) {
			float range = max - min;
			float result = std::fmodf(value - min, range);
			if (result < 0) result += range;

			return min + result;
		}


		template<typename T>
		inline T sign(T v) {
			return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
		}

		using std::min;
		using std::max;
		using std::clamp;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::sinf;
		using std::cos;
		using std::cosf;
		using std::atan2;
		using std::atan2f;
		using std::acosf;
		using std::acos;
	}

}