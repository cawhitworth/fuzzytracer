#include "stdafx.h"

#include "SphereTests.h"
#include "TestHelpers.h"

#include "Sphere.h"

void IntersectTestUntransformed()
{
	auto s = Sphere();

	decimal t;
	assert(s.Intersect( Vector(0, 0, -20, 1.0), Vector(0,0,1, 0.0), t));
	assert (WithinTolerance(t,19));
}

void IntersectTestTransformed()
{
	auto s = Sphere();

	auto m =
				  Matrix::Translate	(Vector(0, 5, 0))
		.Multiply(Matrix::Scale		(Vector(5, 5, 5)));

	s.SetObjectMatrix(m);

	decimal t;
	assert( s.Intersect( Vector(0, 5, -20, 1.0), Vector(0,0,1, 0.0), t) );
	assert( WithinTolerance(t,15));
}

void NormalTestUntransformed()
{
	auto s = Sphere();

	auto n = s.Normal(Vector(0, 1, 0));
	assert(n == Vector(0, 1, 0, 0));
}

void SphereTests()
{
	IntersectTestUntransformed();
	NormalTestUntransformed();

	IntersectTestTransformed();
}