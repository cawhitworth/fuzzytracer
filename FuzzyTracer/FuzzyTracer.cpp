// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"
#include "AreaLight.h"
#include "PointLight.h"

int _tmain(int argc, _TCHAR* argv[])
 {
	Engine e;
	Matrix view = Matrix::Look( Vector(0, 0, -2.5), Vector(0, 0, 1, 0));
	e.SetViewMatrix(view);
	for(decimal y = -4; y <= 4; y+=2)
	{
		for(decimal x = -4; x <= 4; x+=2)
		{
			std::shared_ptr<Sphere> sphere(new Sphere());
			sphere->SetObjectMatrix( Matrix::Translate(Vector(x, y, 0)));
			sphere->SetColour(Colour(1, 1, 1));
			e.AddObject(sphere);
		}
	}

	/*std::shared_ptr<PointLight> light(new PointLight()); */

	std::shared_ptr<AreaLight> light(new AreaLight(3,3));
	light->SetObjectMatrix(
		Matrix::Translate(Vector(-20, 200, -20)).Multiply(
		Matrix::Scale(Vector(5, 0, 5)))
		);
	e.AddLight(light);


	e.Width = 640;
	e.Height = 480;
	e.HFov = DEG2RAD(90);
	e.Oversample = 4;

	std::ofstream output("output.data", std::ios_base::binary);
	e.TraceScene(output);

	return 0;
}

