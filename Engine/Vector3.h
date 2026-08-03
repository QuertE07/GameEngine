#pragma once

#include <cmath>
#include <cassert>

namespace gl
{
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}

		float operator [] (unsigned int i) const { assert(i < 2); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 2); return (&x)[i]; }

		bool operator == (const Vector3& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator != (const Vector3& v) const { return (this->x != v.x || this->y != v.y || this->z != v.z); }

		Vector3 operator + (const Vector3& v) const { return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ this->x / v.x, this->y / v.y, this->z / v.z }; }

		Vector3 operator + (float s) const { return Vector3{ this->x + s, this->y + s, this->z + s }; }
		Vector3 operator - (float s) const { return Vector3{ this->x - s, this->y - s, this->z - s }; }
		Vector3 operator * (float s) const { return Vector3{ this->x * s, this->y * s, this->z * s }; }
		Vector3 operator / (float s) const { return Vector3{ this->x / s, this->y / s, this->z / s }; }

		Vector3 operator += (const Vector3& v) { return Vector3{ this->x += v.x, this->y += v.y, this->z += v.z }; return *this; }
		Vector3 operator -= (const Vector3& v) { return Vector3{ this->x -= v.x, this->y -= v.y, this->z -= v.z }; return *this; }
		Vector3 operator *= (const Vector3& v) { return Vector3{ this->x *= v.x, this->y *= v.y, this->z *= v.z }; return *this; }
		Vector3 operator /= (const Vector3& v) { return Vector3{ this->x /= v.x, this->y /= v.y, this->z /= v.z }; return *this; }

		Vector3 operator += (float s) { return Vector3{ this->x += s, this->y += s, this->z += s }; return *this; }
		Vector3 operator -= (float s) { return Vector3{ this->x -= s, this->y -= s, this->z -= s }; return *this; }
		Vector3 operator *= (float s) { return Vector3{ this->x *= s, this->y *= s, this->z *= s }; return *this; }
		Vector3 operator /= (float s) { return Vector3{ this->x /= s, this->y /= s, this->z /= s }; return *this; }

		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float Length() const { return std::sqrt(LengthSqr()); }
		Vector3 Normalized() const { return (*this) / Length(); }
		float Dot(const Vector3& v) const { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
		//float Angle() const { return std::atan2(this->y, this->x); }
		//float AngleBetween(const Vector2& v) const { return std::acos(Dot(v)); }
		//Vector2 Rotate(float radians)
		//{
		//	Vector2 v;

		//	v.x = this->x * std::cos(radians) - this->y * std::sin(radians);
		//	v.y = this->y * std::sin(radians) + this->x * std::cos(radians);

		//	return v;
		//}
	};

	using Color = Vector3;
}