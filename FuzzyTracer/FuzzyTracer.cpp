// FuzzyTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <fstream>
#include <iostream>
#include "Utilities.h"
#include "Engine.h"
#include "Sphere.h"
#include "Plane.h"
#include "AreaLight.h"
#include "PointLight.h"

int _tmain(int argc, _TCHAR* argv[])
 {
	Engine e;
	Matrix view = Matrix::Look( Vector(-5, 8, -8), Vector(0, 1, 0, 0));
	e.SetViewMatrix(view);

	for(decimal z = -4; z <= 4; z+=2)
	{
		for(decimal y = -4; y <= 4; y+=2)
		{
			for(decimal x = -4; x <= 4; x+=2)
			{
				std::shared_ptr<Sphere> sphere(new Sphere());
				sphere->SetObjectMatrix( Matrix::Translate(Vector(x, y, z)).Multiply(Matrix::Scale(Vector(0.5, 0.5, 0.5))));
				sphere->SetColour(Colour(1, 1, 1));
				e.AddObject(sphere);
			}
		}
	}

	/*
	std::shared_ptr<Sphere> sphere(new Sphere());
	sphere->SetObjectMatrix( Matrix::Translate(Vector(0, 0, 0)));
	sphere->SetColour(Colour(1, 1, 1));
	e.AddObject(sphere);*/


	std::shared_ptr<Plane> plane(new Plane());
	plane->SetObjectMatrix( Matrix::Translate(Vector(0, -5, 0)));
	plane->SetColour(Colour(1,1,1));
	e.AddObject(plane);

//	std::shared_ptr<PointLight> light(new PointLight()); 

	std::shared_ptr<AreaLight> light(new AreaLight(3,3));
	light->SetObjectMatrix(
		Matrix::Translate(Vector(-50, 0, 0)).Multiply(
		Matrix::Scale(Vector(3, 0, 3)))
		);
	light->SetColour(Colour(1.0, 0.0, 0.0));
	e.AddLight(light);

	std::shared_ptr<AreaLight> light2(new AreaLight(3,3));

	light2->SetObjectMatrix(
		Matrix::Translate(Vector(0, 50, 0)).Multiply(
		Matrix::Scale(Vector(3, 0, 3)))
		);
	light2->SetColour(Colour(0.0, 1.0, 0.0));
	e.AddLight(light2);

	std::shared_ptr<AreaLight> light3(new AreaLight(3,3));

	light3->SetObjectMatrix(
		Matrix::Translate(Vector(0, 0, -50)).Multiply(
		Matrix::Scale(Vector(3, 0, 3)))
		);
	light3->SetColour(Colour(0.0, 0.0, 1.0));
	e.AddLight(light3);

	e.Width = 640;
	e.Height = 480;
	e.HFov = DEG2RAD(60);
	e.Oversample = 0;

	std::ofstream output("output.raw", std::ios_base::binary);
	e.TraceScene(output, [](decimal p) { std::cout << p << "%" << std::endl; } );

	return 0;
}

