#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(void)
{
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
}


Sphere::~Sphere(void)
{
	m_objectMatrix.reset();
}

const Matrix& Sphere::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void Sphere::SetObjectMatrix( const Matrix& position )
{
	m_objectMatrix.reset(new Matrix(position));
}

bool Sphere::Intersect( const Vector& rayOrigin, const Vector& rayDirection, decimal& t ) const
{
	// compute a,b,c
	decimal a = rayDirection.DotProduct(rayDirection);
	decimal b = 2 * rayDirection.DotProduct(rayOrigin);
	decimal c = rayOrigin.DotProduct(rayOrigin) - (m_radius * m_radius);

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

Vector Sphere::Normal( const Vector& intersectPoint ) const
{
	return Vector();
}
