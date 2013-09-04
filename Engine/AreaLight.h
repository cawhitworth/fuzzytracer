#pragma once

#include "ILight.h"
#include "IWorldObject.h"
#include <memory>

// An area light is a rectangular light of h*w unit squares
// positioned on the x-z plane centred on the origin.
class AreaLight :
	public ILight, public IWorldObject
{
public:
	AreaLight(unsigned int w = 3, unsigned int h = 3, decimal fuzz = 1);

	virtual ~AreaLight(void);

	virtual const Matrix& GetObjectMatrix() const;

	virtual void SetObjectMatrix(const Matrix& m);

	virtual std::vector<const Vector> Samples() const;

private:
	const decimal m_fuzz;
	const unsigned int m_w, m_h;
	std::shared_ptr<const Matrix> m_objectMatrix;
};

