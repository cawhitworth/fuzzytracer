#pragma once

#include <memory>

#include "ILight.h"
#include "IWorldObject.h"

#include "Matrix.h"

class PointLight :
	public ILight, IWorldObject
{
public:
	PointLight(void);
	virtual ~PointLight(void);

	virtual const Matrix& GetObjectMatrix() const;
	virtual void SetObjectMatrix(const Matrix&);

	virtual std::vector<const Vector> Samples() const;

private:
	std::shared_ptr<const Matrix> m_objectMatrix;
	std::shared_ptr<const Vector> m_point;

};

