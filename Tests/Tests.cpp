// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VectorTests.h"
#include "MatrixTests.h"
#include "SphereTests.h"
#include "EngineTests.h"
#include "AreaLightTests.h"
#include "PlaneTests.h"

int _tmain(int argc, _TCHAR* argv[])
{
	VectorTests();
	MatrixTests();
	SphereTests();
	EngineTests();
	AreaLightTests();
	PlaneTests();
	return 0;
}

