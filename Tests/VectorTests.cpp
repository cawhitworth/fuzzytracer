#include "stdafx.h"
#include "Vector.h"

#define TOLERANCE 0.001

void CheckLength(decimal x, decimal y, decimal z, decimal length)
{
	Vector v(x, y, z);
	assert(abs(length - v.Magnitude()) < TOLERANCE);
}

void UnitVectorIsOfLengthOne()
{
	CheckLength(1.0, 0.0, 0.0, 1.0);
	CheckLength(0.0, 1.0, 0.0, 1.0);
	CheckLength(0.0, 0.0, 1.0, 1.0);
}

void TwoDLengths()
{
	CheckLength(1.0, 1.0, 0.0, sqrt(2.0));
	CheckLength(0.0, 1.0, 1.0, sqrt(2.0));
	CheckLength(1.0, 0.0, 1.0, sqrt(2.0));
}

void ThreeDLengths()
{
	CheckLength(1.0, 1.0, 1.0, sqrt(3.0));
	CheckLength(2.0, 2.0, 2.0, sqrt(12.0));
}

void RightAnglesDotProductIsZero()
{
	Vector v1(1.0, 0.0, 0.0);
	Vector v2(0.0, 1.0, 0.0);

	auto r = v1.DotProduct(v2);
	assert(r == 0.0);
}

void RightAngleCrossProductIsNormal()
{
	Vector v1(1.0, 0.0, 0.0);
	Vector v2(0.0, 1.0, 0.0);

	auto v3 = v1.CrossProduct(v2);

	assert(v3.x == 0.0 && v3.y == 0.0 && v3.z == 1.0);
}

void AWholeBunchOfStuff()
{
	Vector v1(2.0, 3.0, 0.0);
	Vector v2(-3.0, 2.0, 0.0);
	auto v3 = v1.CrossProduct(v2).Normalised();

	assert(v3.x == 0.0 && v3.y == 0.0 && v3.z == 1.0);
}

void VectorTests()
{
	UnitVectorIsOfLengthOne();
	TwoDLengths();
	ThreeDLengths();
	RightAnglesDotProductIsZero();
	RightAngleCrossProductIsNormal();
	AWholeBunchOfStuff();
}