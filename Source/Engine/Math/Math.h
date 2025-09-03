#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace viper {
namespace math {

constexpr float pi = 3.1415926535897932384626433832795;
constexpr float twoPi = 2 * pi;
constexpr float halfPi = pi * 0.5f;

constexpr float radToDeg(float rad) { return rad * (180/pi); }
constexpr float degToRad(float deg) { return deg * (pi/180); }

/// <summary>
/// Wraps an integer value within a specified range [min, max), cycling values that fall outside the range back into it.
/// </summary>
/// <param name="value">The integer value to wrap within the range.</param>
/// <param name="min">The inclusive lower bound of the range.</param>
/// <param name="max">The exclusive upper bound of the range.</param>
/// <returns>The wrapped integer value within the range [min, max).</returns>
constexpr int wrap(int value, int min, int max) {
	int range = max - min;
	int result = (value - min) % range;
	if (result < 0) result += range;

	return min + result;
}

/// <summary>
/// Wraps a floating-point value into the range [min, max), cycling around if necessary.
/// </summary>
/// <param name="value">The value to wrap within the specified range.</param>
/// <param name="min">The lower bound of the range (inclusive).</param>
/// <param name="max">The upper bound of the range (exclusive).</param>
/// <returns>The wrapped value, guaranteed to be within [min, max).</returns>
inline float wrap(float value, float min, float max) {
	float range = max - min;
	float result = std::fmodf(value - min, range);
	if (result < 0) result += range;

	return min + result;
}


/// <summary>
/// Determines the sign of a number.
/// </summary>
/// <typeparam name="T">The type of the value to check.</typeparam>
/// <param name="v">The value whose sign is to be determined.</param>
/// <returns>Returns -1 if the value is negative, 1 if positive, and 0 if zero.</returns>
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
//template <typename T>
//T min(T a, T b) {
//	return (a < b) ? a : b; //This is the ternary way for the code below
//	/*
//	if (a < b) return a;
//	else return b;
//	*/
//}
