#include "stdafx.h"
#include "Engine.h"

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