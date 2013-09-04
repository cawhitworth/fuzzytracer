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

	 const Matrix& GetObjectMatrix() const;
	 void SetObjectMatrix(const Matrix&);

	void SetColour(const Colour& col) { m_colour.reset(new Colour(col)); }
	const Colour& GetColour() const { return *m_colour; }
	std::vector<const Vector> Samples() const;

private:
	std::shared_ptr<const Matrix> m_objectMatrix;
	std::vector<const Vector> m_point;
	std::shared_ptr<const Colour> m_colour;
};

