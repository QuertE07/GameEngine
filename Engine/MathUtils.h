#pragma once

namespace gl
{
	constexpr float Pi = 3.1415926535897932384626433832795f;

	constexpr float RadToDeg = 180.0f / Pi;
	constexpr float DegToRad = Pi / 180.0f;


	template<typename T>
	T Min(T a, T b) { return (a < b) ? a : b; }

	template<typename T>
	T Max(T a, T b) { return (a > b) ? a : b; }

	template<typename T>
	T Wrap(T min, T max, T value)
	{
		if (value - max > 0) value -= max + min;
		if (value - min < 0) value += max - min;

		return value;
	}

	template<typename T>
	T Clamp(T min, T max, T value)
	{
		if (value > max) value = max;
		if (value < min) value = min;

		return value;
	}
}