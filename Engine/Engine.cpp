#include "stdafx.h"
#include "Engine.h"
#include <math.h>
#include <iostream>

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
			std::cout << (i ? "*" : ".");
		}
		std::cout << std::endl;
	}
}

void Engine::AddObject(std::shared_ptr<const IIntersectable> object)
{
	m_objects.push_back(object);
}

bool Engine::TraceRay( const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point)
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