#pragma once

#include <vector>
#include <memory>
#include "Vector.h"
#include "IIntersectable.h"

class Engine
{
public:

	void AddObject(std::shared_ptr<const IIntersectable> object);
	bool TraceRay(const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point);

private:
	std::vector< std::shared_ptr<const IIntersectable> > m_objects;
};