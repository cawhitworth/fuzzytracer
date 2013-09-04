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

void IntersectNormalTestTransformed()
{
	auto s = Sphere();
	auto m = Matrix::Translate(Vector(0, -1, 0));
	s.SetObjectMatrix(m);

	decimal t;
	Vector o(0, -1, -10);
	Vector d(0, 0, 1);
	s.Intersect(o, d, t);

	auto i = o + (d * t);

	auto n = s.Normal(i);

	assert(WithinTolerance(n, Vector(0, 0, -1, 0)));
}

void SphereTests()
{
	IntersectTestUntransformed();
	NormalTestUntransformed();

	IntersectTestTransformed();
	IntersectNormalTestTransformed();
}