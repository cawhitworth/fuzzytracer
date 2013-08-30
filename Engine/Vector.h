#pragma once

#include <math.h>
#include "Utilities.h"

template<typename T>
class Vec4
{
public:
	Vec4(T x, T y, T z, T w = 1) : x(x), y(y), z(z), w(w) {}
	Vec4(void) : x(0), y(0), z(0), w(1) {}

	const T x, y, z, w;

	T DotProduct(const Vec4<T>& rhs) const
	{
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
	}

	Vec4<T> CrossProduct(const Vec4<T>& rhs) const
	{
		Vec4<T> r(
			(y * rhs.z) - (z * rhs.y),
			(z * rhs.x) - (x * rhs.z),
			(x * rhs.y) - (y * rhs.x),
			0.0);
		return r;
	}

	const T Magnitude() const
	{
		return sqrt(DotProduct(*this));
	}

	Vec4<T> Normalised() const
	{
		T l = Magnitude();
		Vec4<T> r(x / l, y / l, z / l, 0.0);
		return r;
	}

	Vec4<T> Direction(const Vec4<T>& to) const
	{
		Vec4<T> r(
			to.x - x,
			to.y - y,
			to.z - z,
			0.0
			);
		return r;
	}

	bool operator==(const Vec4<T> &rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}
};

typedef Vec4<decimal> Vector;
