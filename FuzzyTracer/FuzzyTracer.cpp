// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Engine e;
	Matrix view = Matrix::Look( Vector(0, 5, -10), Vector(0, 0, 1, 0));
	e.SetViewMatrix(view);

	std::shared_ptr<Sphere> sphere(new Sphere());
	sphere->SetObjectMatrix( 
		Matrix::Translate(Vector(0, 5, 0)).Multiply(
		Matrix::Scale(Vector(5,5,5)))
		
	);
	e.AddObject(sphere);

	e.Height = 80;
	e.Width = 80;
	e.hFov = DEG2RAD(90);
	e.TraceScene();

	return 0;
}

