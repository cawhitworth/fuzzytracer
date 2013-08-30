#include "stdafx.h"

#include "SphereTests.h"

#include "Sphere.h"

void IntersectTest()
{
	auto s = Sphere();
	s.SetRadius(10);

	decimal t;
	assert(s.Intersect( Vector(0, 0, -20, 1.0), Vector(0,0,1, 0.0), t));
	assert (t==10.0);
}

void NormalTest()
{
	auto s = Sphere();
	s.SetRadius(10);

	auto n = s.Normal(Vector(0, 10, 0));
	assert(n == Vector(0, 1, 0));
}

void SphereTests()
{
	IntersectTest();
	NormalTest();
}