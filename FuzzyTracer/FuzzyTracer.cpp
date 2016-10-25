// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <ctime>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"
#include "Plane.h"
#include "AreaLight.h"
#include "PointLight.h"
#include "lodepng.h"

int _tmain(int argc, _TCHAR* argv[])
 {
	Engine e;
	auto view = Matrix::Look( Vector(-6.3, 8.3, -8.7), Vector(0, 0, 0, 0));
	e.SetViewMatrix(view);
	decimal r = 0, g = 0, b = 0;
	for(decimal z = -4; z <= 4; z+=2)
	{
		for(decimal y = -4; y <= 4; y+=2)
		{
			for(decimal x = -4; x <= 4; x+=2)
			{
				r += 0.2;
				std::shared_ptr<Sphere> sphere(new Sphere());
				sphere->SetObjectMatrix( Matrix::Translate(Vector(x, y, z)).Multiply(Matrix::Scale(Vector(0.75, 0.75, 0.75))));
				sphere->SetColour(Colour(r,g,b));
				e.AddObject(sphere);
			}
			r = 0; g += 0.2;
		}
		g = 0; b += 0.2;
	}

    auto plane = std::make_shared<Plane>();
	
    plane->SetObjectMatrix( Matrix::Translate(Vector(0, -5, 0)));
	plane->SetColour(Colour(1,1,1));
	e.AddObject(plane);

    auto light = std::make_shared<AreaLight>(16, 16);
	light->SetObjectMatrix(
		Matrix::Translate(Vector(-100, 400, 10)).Multiply(
		Matrix::Scale(Vector(8, 0, 8)))
		);
	light->SetColour(Colour(1.0, 1.0,  0.97));
	e.AddLight(light);

	e.Width = 640;
	e.Height = 480;
	e.HFov = DEG2RAD(60);
	e.Oversample = 16;
	e.Threads = 4;

	auto t = clock();

	auto output = e.TraceScene([](decimal p) { std::cout << p << "%" << std::endl; } );

	t = clock() - t;
	
	std::cout << "Finished in " << (decimal(t) / CLOCKS_PER_SEC) << " seconds" << std::endl;

    auto err = lodepng::encode("output.png", output, e.Width, e.Height, LCT_RGB);
    
    std::cout << "Written: " << err << std::endl;

	return 0;
}

