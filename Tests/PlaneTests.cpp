#include "stdafx.h"
#include "Plane.h"
#include "Tolerance.h"

void UntransformedIntersectAtOrigin()
{
	auto p = Plane();
	auto o = Vector(0, 10, 0);
	auto d = Vector(0, -1, 0);

	decimal t;
	bool i = p.Intersect(o, d, t);
	auto intersectPoint = o + d * t;
	assert(WithinTolerance(intersectPoint, Vector(0,0,0)));
}

void UntransformedIntersect()
{
	auto p = Plane();
	auto o = Vector(5, 10, 0);
	auto d = Vector(1, -1, -1).Normalised();

	decimal t;
	bool i = p.Intersect(o, d, t);
	auto intersectPoint = o + d * t;
	assert(WithinTolerance(intersectPoint, Vector(15,0,-10)));
}

void UntransformedNormalAtOrigin()
{
	auto p = Plane();

	auto n = p.Normal(Vector(0,0,0));

	assert(WithinTolerance(n, Vector(0,1,0)));
}

void UntransformedNormal()
{
	auto p = Plane();

	auto n = p.Normal(Vector(15,0,-10));

	assert(WithinTolerance(n, Vector(0,1,0)));
}

void TransformedIntersect()
{
	auto p = Plane();
	auto m =            Matrix::Translate(Vector(0, 5, 0))
             .Multiply( Matrix::RotationX(DEG2RAD(90)));
	p.SetObjectMatrix(m);

	auto o = Vector(5, 5, -10);
	auto d = Vector(0, 0, 1);

	decimal t;
	bool i = p.Intersect(o, d, t);

	auto intersectPoint = o + d * t;
	assert(WithinTolerance(intersectPoint, Vector(5, 5, 0)));
}

void TransformedNormal()
{
	auto p = Plane();

	auto m =            Matrix::Translate(Vector(0, 5, 0))
             .Multiply( Matrix::RotationX(DEG2RAD(-45)));
	p.SetObjectMatrix(m);

	auto o = Vector(5, 5, -10);
	auto d = Vector(0, 0, 1);
	decimal t;
	bool i = p.Intersect(o, d, t);

	auto intersectPoint = o + d * t;

	auto n = p.Normal(intersectPoint);

 	assert(WithinTolerance(n, Vector(0, sqrt(2.0)/2.0, -sqrt(2.0)/2.0, 0)));
}

void PlaneTests()
{
	UntransformedIntersectAtOrigin();
	UntransformedIntersect();
	UntransformedNormalAtOrigin();
	UntransformedNormal();
	TransformedIntersect();
	TransformedNormal();
}