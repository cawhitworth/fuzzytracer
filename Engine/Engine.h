#pragma once

#include <vector>
#include <memory>
#include "Vector.h"
#include "Matrix.h"
#include "IIntersectable.h"
#include "ILight.h"
#include "Colour.h"

class Engine
{
public:
	unsigned int Width, Height;
	decimal hFov;

	void SetViewMatrix(const Matrix&);
	void TraceScene();

	void AddObject(std::shared_ptr<const IIntersectable> object);
	void AddLight(std::shared_ptr<const ILight> light);

	bool TraceRay(const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point) const;
	const Colour Illuminate(const IIntersectable& hitObject, const Vector& point) const;


private:
	std::shared_ptr<const Matrix> m_Projection;
	std::shared_ptr<const Matrix> m_View;
	std::vector< std::shared_ptr<const IIntersectable> > m_objects;
	std::vector< std::shared_ptr<const ILight> > m_lights;

};