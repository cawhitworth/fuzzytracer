#include "stdafx.h"

#include "Engine.h"
#include "Sphere.h"
#include "TestHelpers.h"
#include "EngineTests.h"
#include "PointLight.h"

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

	bool i = e.TraceRay(Vector(0,5,-10), Vector(0,0,1,0), hit, v);

	assert(i);

	assert(hit == sphere);

	assert(WithinTolerance(*v, Vector(0,5,-5)));
}

void CanIlluminate()
{
	Engine e;
	std::shared_ptr<Sphere> sphere(new Sphere());
	sphere->SetColour(Colour(1.0, 1.0, 1.0));

	e.AddObject(sphere);

	std::shared_ptr<PointLight> light(new PointLight());
	light->SetObjectMatrix(
		Matrix::Translate(Vector(0, 10, -11))
		);

	e.AddLight(light);

	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	bool i = e.TraceRay(Vector(0,0,-10), Vector(0,0,1,0), hit, v);

	assert(i);

	auto c = e.Illuminate(*hit, *v);

	assert(WithinTolerance(c.Luminance(), 0.3 + (0.7 * sqrt(2.0)/2)));

};

void EngineTests()
{
	EmptySceneHasNoHit();
	CanHitASphere();
	CanHitTransformedSphere();
	CanIlluminate();
}