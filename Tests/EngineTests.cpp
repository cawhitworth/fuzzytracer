#include "stdafx.h"

#include "Engine.h"
#include "Sphere.h"
#include "TestHelpers.h"
#include "EngineTests.h"

void EmptySceneHasNoHit()
{
	Engine e;
	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	assert(!e.TraceRay(Vector(0,0,0), Vector(0,0,1), hit, v));
}

void CanHitASphere()
{
	Engine e;
	std::shared_ptr<Sphere> sphere(new Sphere());

	e.AddObject(sphere);

	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	assert(e.TraceRay(Vector(0,0,-10), Vector(0,0,1,0), hit, v));

	assert(hit == sphere);

	assert(WithinTolerance(*v, Vector(0,0,-1)));
}

void CanHitTransformedSphere()
{
	Engine e;

	std::shared_ptr<Sphere> sphere(new Sphere());
	Matrix m = Matrix::Translate(Vector(0,5,0))
		.Multiply(Matrix::Scale(Vector(5,5,5)));
	sphere->SetObjectMatrix(m);
	
	e.AddObject(sphere);

	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	assert(e.TraceRay(Vector(0,5,-10), Vector(0,0,1,0), hit, v));

	assert(hit == sphere);

	assert(WithinTolerance(*v, Vector(0,5,-5)));
}

void EngineTests()
{
	EmptySceneHasNoHit();
	CanHitASphere();
	CanHitTransformedSphere();
}