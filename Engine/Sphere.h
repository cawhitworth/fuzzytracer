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
	
	const Matrix& GetObjectMatrix() const;
	void SetObjectMatrix(const Matrix& position);

	// IIntersectable

	bool Intersect(const Vector& rayOrigin, const Vector& rayDirection, decimal& t) const;
	Vector Normal(const Vector& intersectPoint) const;

private:
	std::shared_ptr<Matrix> m_objectMatrix;
	std::shared_ptr<Matrix> m_objectMatrixInverse;
};

