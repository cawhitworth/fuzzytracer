#include "stdafx.h"
#include "Plane.h"
#include "Tolerance.h"

Plane::Plane(void)
{
	SetColour(Colour(1,1,1));
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
	m_objectMatrixInverse.reset(new Matrix(Matrix::Identity()));
	m_normalVector.reset(new Vector(0,1,0));
}

Plane::~Plane(void)
{
	m_objectMatrix.reset();
	m_objectMatrixInverse.reset();
}

void Plane::SetColour(const Colour& col)
{
	m_colour.reset(new Colour(col));
}

bool Plane::Intersect( const Vector& rayOrigin, const Vector& rayDirection, decimal& t ) const
{
	auto transformedOrigin = m_objectMatrixInverse->Multiply(rayOrigin);
	auto transformedDirection = m_objectMatrixInverse->Multiply(rayDirection);

	if (WithinTolerance(transformedDirection.y, 0))
		return false;

	t = -(transformedOrigin.y) / (transformedDirection.y);

	if (t < 0) return false;
	return true;
}

Vector Plane::Normal( const Vector& intersectPoint ) const
{
	return *m_normalVector;
}

Colour Plane::ColourAt( const Vector& intersectPoint ) const
{
	return *m_colour;
}

const Matrix& Plane::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void Plane::SetObjectMatrix( const Matrix& m)
{
	m_objectMatrix.reset(new Matrix(m));
	m_objectMatrixInverse.reset(new Matrix(m.Inverse()));
	m_normalVector.reset(new Vector(m.Multiply(Vector(0,1,0,0))));

}
