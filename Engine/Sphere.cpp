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

const Matrix& Sphere::GetObjectMatrix()
{
	return *m_objectMatrix;
}

void Sphere::SetObjectMatrix( const Matrix& position )
{
	m_objectMatrix.reset(new Matrix(position));
}

Vector Sphere::Intersect( const Vector& rayOrigin, const Vector& rayDirection )
{
	return Vector();
}

Vector Sphere::Normal( const Vector& intersectPoint )
{
	return Vector();
}
