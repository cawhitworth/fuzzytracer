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

	// IPositionable
	
	const Matrix& GetObjectMatrix();
	void SetObjectMatrix(const Matrix& position);

	// IIntersectable

	Vector Intersect(const Vector& rayOrigin, const Vector& rayDirection);
	Vector Normal(const Vector& intersectPoint);

private:
	std::shared_ptr<Matrix> m_objectMatrix;
	std::shared_ptr<Matrix> m_objectMatrixInverse;
};

