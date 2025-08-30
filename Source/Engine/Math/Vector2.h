#pragma once
#include "../EnginePCH.h"
#include "Math.h"
#include <cassert>
#include <iostream>

namespace viper {
	template<typename T>
	struct Vector2 {
		union {
			struct { T x, y; };
			struct { T u, v; };
		};


		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		T operator [] (unsigned int index) const { assert(index < 2);  return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2);  return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		// square root ((x * x) + ( y * y))

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return viper::math::sqrtf(LengthSqr()); }

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the direction of the original vector with a length of 1.</returns>
		Vector2 Normalized() const { return *this / Length(); }

		float Angle() const { return math::atan2f(y, x); };

		/// <summary>
		/// Returns a new vector that is the result of rotating this vector by the specified angle in radians.
		/// </summary>
		/// <param name="radians">The angle to rotate the vector, in radians.</param>
		/// <returns>A new Vector2 representing the rotated vector.</returns>
		Vector2 Rotate(float radians) const {
			Vector2 v;

			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}


		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		static float Dot(const Vector2& a, const Vector2& b) {
			return a.x * b.x + a.y * b.y;
		}

		/// <summary>
		/// Calculates the angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The angle in radians between vector 'a' and vector 'b'.</returns>
		static float AngleBetween(const Vector2& a, const Vector2& b) {
			return math::acosf(Dot(a, b));
		}

		/// <summary>
		/// Computes the 2D cross product (determinant) of two vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The scalar value representing the cross product of the two vectors.</returns>
		static float Cross(const Vector2& a, const Vector2& b) {
			return a.x * b.y - a.y * b.x;
		}

		/// <summary>
		/// Calculates the signed angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The signed angle in radians between vector 'a' and vector 'b'. The sign indicates the direction from 'a' to 'b'.</returns>
		static float SignedAngleBetween(const Vector2& a, const Vector2& b) {
			Vector2 v{ Dot(a,b), Cross(a,b) };
			return v.Angle();
		}
	};

	template<typename T>
	std::ostream& operator <<(std::ostream& stream, const Vector2<T>& v) {
		stream << "{" << v.x << ", " << v.y << "}";
		return stream;
	}

	template<typename T>
	std::istream& operator >>(std::istream& stream, Vector2<T>& v) {
		char ch = '\0';
		// {
		if (!(stream >> std::ws >> ch) || ch != '{') {
			stream.setstate(std::ios::failbit);
			return stream;
		}
		// x
		if (!(stream >> std::ws >> v.x)) {
			stream.setstate(std::ios::failbit);
			return stream;
		}
		// ,
		if (!(stream >> std::ws >> ch) || ch != ',') {
			stream.setstate(std::ios::failbit);
			return stream;
		}
		// y
		if (!(stream >> std::ws >> v.y)) {
			stream.setstate(std::ios::failbit);
			return stream;
		}
		// }
		if (!(stream >> std::ws >> ch) || ch != '}') {
			stream.setstate(std::ios::failbit);
			return stream;
		}

		return stream;
	}

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;

}