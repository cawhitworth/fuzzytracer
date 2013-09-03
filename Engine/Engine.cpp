#include "stdafx.h"
#include "Engine.h"
#include <math.h>
#include <iostream>
#include <vector>

void Engine::SetViewMatrix(const Matrix& view)
{
	m_View.reset(new Matrix(view));
}

void Engine::TraceScene()
{
	decimal distance = 1.0 / (tan(hFov / 2.0));

	Vector origin(0, 0, -distance);
	Vector worldOrigin = m_View->Multiply(origin);

	std::shared_ptr<const IIntersectable> hit;
	std::shared_ptr<const Vector> v;

	for(int pixelY = 0; pixelY < Height; pixelY++)
	{
		decimal y = 1 - (decimal)(pixelY*2) / (Height-1);
		for(int pixelX = 0; pixelX < Width; pixelX++)
		{
			decimal x = -1 + (decimal)(pixelX*2) / (Width-1);

			Vector target(x, y, 0);
			Vector direction = origin.Direction(target);

			Vector worldDirection = m_View->Multiply(direction);

			bool i = TraceRay(worldOrigin, worldDirection, hit, v);

			if (i)
			{
				Colour c = Illuminate(*hit, *v);

				decimal l = c.Luminance();
				std::cout << ( (l < 0.25) ? "." : (l < 0.75) ? "O" : "*" );
			}
			else
			{
				std::cout << ".";
			}
		}
		std::cout << std::endl;
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
	std::vector<const Colour> colours;

	std::shared_ptr<const IIntersectable> shadowObject;
	std::shared_ptr<const Vector> shadowPoint;
	for(auto l : m_lights)
	{
		for(auto s : l->Samples())
		{
			Vector direction = point.Direction(s);
			if (!TraceRay(point, direction, shadowObject, shadowPoint))
			{
				Vector normal = hitObject.Normal(point);

				decimal cosTheta = direction.DotProduct(normal);

				auto c = hitObject.ColourAt(point).Multiply(cosTheta);

				colours.push_back(c);
			}
		}
	}

	return Colour::Average(colours);
}