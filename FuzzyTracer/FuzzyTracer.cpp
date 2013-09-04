// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include <iostream>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"
#include "AreaLight.h"
#include "PointLight.h"

int _tmain(int argc, _TCHAR* argv[])
 {
	Engine e;
	Matrix view = Matrix::Look( Vector(0, 0, -5), Vector(0, 0, 0, 0));
	e.SetViewMatrix(view);
	decimal r = 0;
	decimal g = 0;
	for(decimal y = -4; y <= 4; y+=2)
	{
		r = 0; g += 0.2;
		for(decimal x = -4; x <= 4; x+=2)
		{
			r += 0.2;
			std::shared_ptr<Sphere> sphere(new Sphere());
			sphere->SetObjectMatrix( Matrix::Translate(Vector(x, y, 0)));
			sphere->SetColour(Colour(r, g, 1));
			e.AddObject(sphere);
		}
	}

	/*std::shared_ptr<PointLight> light(new PointLight()); */

	std::shared_ptr<AreaLight> light(new AreaLight(3,3));
	light->SetObjectMatrix(
		Matrix::Translate(Vector(-20, 200, -20)).Multiply(
		Matrix::Scale(Vector(8, 0, 8)))
		);
	e.AddLight(light);


	e.Width = 640;
	e.Height = 480;
	e.HFov = DEG2RAD(90);
	e.Oversample = 0;

	std::ofstream output("output.data", std::ios_base::binary);
	e.TraceScene(output, [](decimal p) { std::cout << p << "%" << std::endl; } );

	return 0;
}

