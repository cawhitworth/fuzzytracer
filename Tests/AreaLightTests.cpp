#include "stdafx.h"
#include "AreaLight.h"
#include "AreaLightTests.h"
#include "TestHelpers.h"

void CheckSamplesAreCorrect()
{
	AreaLight l(3,3,0);

	auto v = l.Samples();

	assert(v.size() == 9);

	assert(WithinTolerance(v[0], Vector(-1, 0, -1)));
	assert(WithinTolerance(v[1], Vector(-1, 0, 0)));
}

void AreaLightTests()
{
	CheckSamplesAreCorrect();

}