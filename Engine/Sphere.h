#pragma once
#include "IWorldObject.h"
#include "IIntersectable.h"
#include <memory>

class Sphere :
	public IWorldObject,
	public IIntersectable
{
public:
	Sphere(void);
	virtual ~Sphere(void);

	// Sphere
	const decimal GetRadius() const { return m_radius; }
	void SetRadius(const decimal r) { m_radius = r; }

	// IPositionable
	
	const Matrix& GetObjectMatrix() const;
	void SetObjectMatrix(const Matrix& position);

	// IIntersectable

	bool Intersect(const Vector& rayOrigin, const Vector& rayDirection, decimal& t) const;
	Vector Normal(const Vector& intersectPoint) const;

private:
	decimal m_radius;
	std::shared_ptr<Matrix> m_objectMatrix;
};

