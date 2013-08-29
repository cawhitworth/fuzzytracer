#pragma once

#include "Vector.h"

class IIntersectable
{
public:
	virtual Vector Intersect(const Vector& rayOrigin, const Vector& rayDirection) = 0;
	virtual Vector Normal(const Vector& intersectPoint) = 0;
};