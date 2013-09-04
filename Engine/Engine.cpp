#include "stdafx.h"
#include "Engine.h"
#include <math.h>
#include <iostream>
#include <vector>

void Engine::SetViewMatrix(const Matrix& view)
{
	m_View.reset(new Matrix(view));
}

void Engine::TraceScene(std::ostream& output, std::function<void (decimal)> callback)
{
	decimal distance = 1.0 / (tan(HFov / 2.0));

	Vector origin(0, 0, -distance);
	Vector worldOrigin = m_View->Multiply(origin);

	std::vector<const Colour> cols;

	decimal yScale = decimal(2) / (Height - 1);
	decimal xScale = decimal(2) / (Width - 1);

	for(int pixelY = 0; pixelY < Height; pixelY++)
	{
		callback( decimal(pixelY * 100) / Height);

		decimal y = 1 - pixelY * yScale;

		for(int pixelX = 0; pixelX < Width; pixelX++)
		{
			decimal x = -1 + pixelX * xScale;
			if (Oversample > 0)
			{
				cols.clear();
				for(int i = 0; i < Oversample; i ++)
				{
					decimal xOff = (-0.5 + decimal(rand()) / RAND_MAX) * xScale;
					decimal yOff = (-0.5 + decimal(rand()) / RAND_MAX) * yScale;

					auto c = TraceAndIlluminate(worldOrigin, origin, Vector(x + xOff, y + yOff, 0));
					cols.push_back(c);
				}

				auto c = Colour::Average(cols);
				output << (char)(c.r * 255);
				output << (char)(c.g * 255);
				output << (char)(c.b * 255);
			}
			else
			{
				auto c = TraceAndIlluminate(worldOrigin, origin, Vector(x, y, 0));
				output << (char)(c.r * 255);
				output << (char)(c.g * 255);
				output << (char)(c.b * 255);
			}

		}
	}
}

Colour Engine::TraceAndIlluminate(const Vector& worldOrigin, const Vector& origin, const Vector& target)
{
	static std::shared_ptr<const IIntersectable> hit;
	static std::shared_ptr<const Vector> v;

	Vector direction = origin.Direction(target);

	Vector worldDirection = m_View->Multiply(direction);

	bool intersected = TraceRay(worldOrigin, worldDirection, hit, v);

	if (intersected)
	{
		return (Illuminate(*hit, *v).Clamp());
	}
	else
	{
		return (Colour(0,0,0));
	}
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
	for(std::shared_ptr<const IIntersectable> o : m_objects)
	{
		decimal t;
		if (o->Intersect(origin, direction,t))
		{
			if (t < minT || minObj.get() == NULL)
			{
				minT = t;
				minObj = o;
			}
		}
	}

	if (minObj != NULL)
	{
		hit = minObj;
		const Vector* v = new Vector(origin + (direction * minT));

		point.reset(v);

		return true;
	}
	return false;
}

const Colour Engine::Illuminate(const IIntersectable& hitObject, const Vector& point) const
{

	decimal diffuse = 0.7, ambient = 0.3;

	std::shared_ptr<const IIntersectable> shadowObject;
	std::shared_ptr<const Vector> shadowPoint;

	auto pointColour = hitObject.ColourAt(point);

	auto ambientColour = Colour(ambient, ambient, ambient).Multiply(pointColour);
	std::shared_ptr<const Colour> diffuseColour(new Colour(0,0,0));

	for(auto l : m_lights)
	{
		std::vector<const Colour> diffuseColours;
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

				auto diffuseColour = l->GetColour().Multiply(power);

				auto c = pointColour.Multiply(diffuseColour).Clamp();

				diffuseColours.push_back(c);
			}
			else
				diffuseColours.push_back(Colour(0,0,0));
		}
		diffuseColour.reset(new Colour(*diffuseColour + Colour::Average(diffuseColours)));
	}

	return *diffuseColour + ambientColour;
}