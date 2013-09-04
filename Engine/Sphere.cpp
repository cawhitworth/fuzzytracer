#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(void)
{
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
	m_objectMatrixInverse.reset(new Matrix(Matrix::Identity()));
	m_colour.reset(new Colour());
}


Sphere::~Sphere(void)
{
	m_objectMatrix.reset();
	m_objectMatrixInverse.reset();
}

void Sphere::SetColour(const Colour& colour)
{
	m_colour.reset(new Colour(colour));
}

const Matrix& Sphere::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void Sphere::SetObjectMatrix( const Matrix& position )
{
	m_objectMatrix.reset(new Matrix(position));
	m_objectMatrixInverse.reset(new Matrix(position.Inverse()));
}

bool Sphere::Intersect( const Vector& rayOrigin, const Vector& rayDirection, decimal& t ) const
{
	auto transformedOrigin = m_objectMatrixInverse->Multiply(rayOrigin);
	auto transformedDirection = m_objectMatrixInverse->Multiply(rayDirection);

	// compute a,b,c
	decimal a = transformedDirection.DotProduct(transformedDirection);
	decimal b = 2 * transformedDirection.DotProduct(transformedOrigin);
	decimal c = transformedOrigin.DotProduct(transformedOrigin) - 1.0;

	// b^2 - 4ac
	decimal discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return false;
	decimal sqrtDisc = sqrt(discriminant);

	decimal t0 = ( -b - sqrtDisc ) / (2 * a);
	decimal t1 = ( -b + sqrtDisc ) / (2 * a);

	if (t1 < t0)
	{
		decimal temp = t1;
		t1 = t0;
		t0 = temp;
	}

	// If t1 < 0, the sphere is in the ray's negative direction
	if (t1 < 0)
		return false;

	// if t0 < 0, the intersection is at t1 (and we're inside the sphere)
	if (t0 < 0)
	{
		t = t1;
		return true;
	}

	t = t0;
	return true;
}

const Vector Sphere::Normal( const Vector& intersectPoint ) const
{
	auto v = m_objectMatrixInverse->Multiply(intersectPoint);
	return Vector(v.x, v.y, v.z, 0).Normalised();
}

const Colour Sphere::ColourAt(const Vector& intersectPoint) const
{
	return *m_colour;
}