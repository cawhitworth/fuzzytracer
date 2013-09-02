#pragma once

#include <vector>
#include <memory>
#include "Vector.h"
#include "Matrix.h"
#include "IIntersectable.h"

class Engine
{
public:
	unsigned int Width, Height;
	decimal hFov;

	void SetViewMatrix(const Matrix&);
	void TraceScene();

	void AddObject(std::shared_ptr<const IIntersectable> object);
	bool TraceRay(const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point);

private:
	std::shared_ptr<const Matrix> m_Projection;
	std::shared_ptr<const Matrix> m_View;
	std::vector< std::shared_ptr<const IIntersectable> > m_objects;
};