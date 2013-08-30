#include "stdafx.h"
#include "TestHelpers.h"

bool WithinTolerance( decimal d1, decimal d2 )
{
	return abs(d1-d2) < TOLERANCE;
}

bool WithinTolerance( const Vector& v1, const Vector& v2 )
{
	auto d = abs(v1.x - v2.x) + abs(v1.y - v2.y) + abs(v1.z - v2.z) + abs(v1.w - v2.w);

	return d < TOLERANCE;
}

bool WithinTolerance( const Matrix& m1, const Matrix& m2 )
{
	auto sum = 0.0;
	for(int i = 0; i<16; i++)
	{
		sum += abs(m1._d[i] - m2._d[i]);
	}
	return sum < TOLERANCE;
}

