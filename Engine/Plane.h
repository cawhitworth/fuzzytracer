#pragma once

#include <memory>
#include "IIntersectable.h"
#include "IWorldObject.h"

class Plane :
	public IIntersectable,
	public IWorldObject
{
public:
	Plane(void);
	~Plane(void);

	void SetColour(const Colour& col);

	bool Intersect(const Vector& rayOrigin, const Vector& rayDirection, decimal& t) const;
	const Vector Normal(const Vector& intersectPoint) const;
	const Colour ColourAt(const Vector& intersectPoint) const;

	const Matrix& GetObjectMatrix() const;
	void SetObjectMatrix(const Matrix&);

private:
	std::shared_ptr<const Matrix> m_objectMatrix;
	std::shared_ptr<const Matrix> m_objectMatrixInverse;
	std::shared_ptr<const Vector> m_normalVector;
	std::shared_ptr<const Colour> m_colour;
};

