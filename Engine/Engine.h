#pragma once

#include <functional>
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
	unsigned int Oversample;
	unsigned int Width, Height;
	decimal HFov;

	Engine() : Oversample(4), Width(640), Height(480), HFov(90) {}

	void SetViewMatrix(const Matrix&);
	void TraceScene(std::ostream&, std::function<void (decimal)> callback);

	void AddObject(std::shared_ptr<const IIntersectable> object);
	void AddLight(std::shared_ptr<const ILight> light);

	Colour Engine::TraceAndIlluminate(const Vector& worldOrigin, const Vector& origin, const Vector& target);
	bool TraceRay(const Vector& origin, const Vector& direction, std::shared_ptr<const IIntersectable>& hit, std::shared_ptr<const Vector>& point) const;
	const Colour Illuminate(const IIntersectable& hitObject, const Vector& point) const;


private:
	std::shared_ptr<const Matrix> m_Projection;
	std::shared_ptr<const Matrix> m_View;
	std::vector< std::shared_ptr<const IIntersectable> > m_objects;
	std::vector< std::shared_ptr<const ILight> > m_lights;

};