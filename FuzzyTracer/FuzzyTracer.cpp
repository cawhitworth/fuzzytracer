// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"
#include "PointLight.h"

int _tmain(int argc, _TCHAR* argv[])
 {
	Engine e;
	Matrix view = Matrix::Look( Vector(0, 0, -2.5), Vector(0, 0, 1, 0));
	e.SetViewMatrix(view);

	std::shared_ptr<Sphere> sphere(new Sphere());
	sphere->SetObjectMatrix( Matrix::Translate(Vector(0, -1, 0)));
	sphere->SetColour(Colour(1, 1, 1));
	e.AddObject(sphere);

	std::shared_ptr<PointLight> light(new PointLight());
	light->SetObjectMatrix(
		Matrix::Translate(Vector(0, -1, -200))
		);
	e.AddLight(light);

	e.Width = 640;
	e.Height = 480;
	e.hFov = DEG2RAD(90);

	std::ofstream output("output.data", std::ios_base::binary);
	e.TraceScene(output);

	return 0;
}

