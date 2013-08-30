#include "stdafx.h"

#include "Engine.h"
#include "Sphere.h"
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
	std::shared_ptr<IIntersectable> sphere(new Sphere());

	e.AddObject(sphere);

	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	assert(e.TraceRay(Vector(0,0,-10), Vector(0,0,1), hit, v));

	assert(hit == sphere);

	assert(v->operator==(Vector(0,0,-1)));
}

void EngineTests()
{
	EmptySceneHasNoHit();
	CanHitASphere();
}