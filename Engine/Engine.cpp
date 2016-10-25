#include "stdafx.h"
#include "Engine.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <thread>

void Engine::SetViewMatrix(const Matrix& view)
{
	m_View.reset(new Matrix(view));
}

void Engine::TraceScene(std::ostream& output, std::function<void (decimal)> callback)
{
	decimal distance = 1.0 / (tan(HFov / 2.0));

	const Vector origin(0, 0, -distance);
	const auto worldOrigin = m_View->Multiply(origin);

    std::vector<unsigned char> image(Width * Height * 3);

	std::vector<std::thread> workers;

	for(int pixelY = 0; pixelY < Height; pixelY+=Threads)
	{
		callback( decimal(pixelY * 100) / Height);

		for(int t = 0; t < Threads; t++)
		{
			if (pixelY + t < Height)
				workers.push_back( std::thread( &Engine::RenderLine, this, pixelY+t, std::ref(worldOrigin), std::ref(origin), image) );
		}

		for(auto& t : workers)
			t.join();

		workers.clear();
	}

	for(auto i : image)
	{
		output << image[i];
	}
}

Colour Engine::TraceAndIlluminate(const Vector& worldOrigin, const Vector& origin, const Vector& target) const
{
	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	auto worldTarget = m_View->Multiply(target);

	auto worldDirection = worldOrigin.Direction(worldTarget).Normalised();

	auto intersected = TraceRay(worldOrigin, worldDirection, hit, v);

	if (intersected)
	{
		return Illuminate(*hit, *v).Clamp();
	}

    return Colour(0, 0, 0);
}

void Engine::AddObject(std::shared_ptr<const IIntersectable> object)
{
	m_objects.push_back(object);
}

void Engine::AddLight(std::shared_ptr<const ILight> light)
{
	m_lights.push_back(light);
}

bool Engine::TraceRay( const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point) const
{
	std::shared_ptr<const IIntersectable> minObj;
	decimal minT = 0;
	for(auto o : m_objects)
	{
		decimal t;
		if (o->Intersect(origin, direction,t))
		{
			if (t < minT || minObj.get() == nullptr)
			{
				minT = t;
				minObj = o;
			}
		}
	}

	if (minObj != nullptr)
	{
		hit = minObj;
		const Vector* v = new Vector(origin + (direction * minT));

		point.reset(v);

		return true;
	}
	return false;
}

Colour Engine::Illuminate(const IIntersectable& hitObject, const Vector& point) const
{

	decimal diffuse = 0.85, ambient = 0.15;

	std::shared_ptr<const IIntersectable> shadowObject;
	std::shared_ptr<const Vector> shadowPoint;

	auto pointColour = hitObject.ColourAt(point);

	auto ambientColour = Colour(ambient, ambient, ambient).Multiply(pointColour);
	
    auto diffuseColour = std::make_shared<const Colour>(0, 0, 0);

	for(auto l : m_lights)
	{
		std::vector<Colour> diffuseColours;
		for(auto s : l->Samples())
		{
			auto direction = s.Direction(point).Normalised();
			auto shadow = TraceRay(s, direction, shadowObject, shadowPoint);

			if (!shadow || (shadow && shadowObject.get() == &hitObject))
			{
				auto normal = hitObject.Normal(point);
				auto flippedDirection = direction * -1.0;

				auto cosTheta = flippedDirection.DotProduct(normal);

				auto power = CLAMP(cosTheta * diffuse);

				auto diffuseLightColour = l->GetColour().Multiply(power);

				auto c = pointColour.Multiply(diffuseLightColour).Clamp();

				diffuseColours.push_back(c);
			}
			else
				diffuseColours.push_back(Colour(0,0,0));
		}
		diffuseColour.reset(new Colour(*diffuseColour + Colour::Average(diffuseColours)));
	}

	return *diffuseColour + ambientColour;
}

void Engine::RenderLine( int pixelY, const Vector& worldOrigin, const Vector& origin, std::vector<unsigned char> image ) const
{
	std::vector<Colour> cols;
	decimal yScale = decimal(2) / (Height - 1);
	decimal xScale = decimal(2) / (Width - 1);
	decimal y = 1 - pixelY * yScale;


	for(auto pixelX = 0; pixelX < Width; pixelX++)
	{
		decimal x = -1 + pixelX * xScale;
		if (Oversample > 0)
		{
			cols.clear();
			for(auto i = 0; i < Oversample; i ++)
			{
				decimal xOff = (-0.5 + decimal(rand()) / RAND_MAX) * xScale;
				decimal yOff = (-0.5 + decimal(rand()) / RAND_MAX) * yScale;

				auto c = TraceAndIlluminate(worldOrigin, origin, Vector(x + xOff, y + yOff, 0));
				cols.push_back(c);
			}

			auto c = Colour::Average(cols);
			image[(pixelX + pixelY*Width) * 3] = c.r * 255;
			image[(pixelX + pixelY*Width) * 3 + 1] = c.g * 255;
			image[(pixelX + pixelY*Width) * 3 + 2] = c.b * 255;

		}
		else
		{
			auto c = TraceAndIlluminate(worldOrigin, origin, Vector(x, y, 0));
			image[(pixelX + pixelY*Width) * 3] = c.r * 255;
			image[(pixelX + pixelY*Width) * 3 + 1] = c.g * 255;
			image[(pixelX + pixelY*Width) * 3 + 2] = c.b * 255;
		}

	}
}
