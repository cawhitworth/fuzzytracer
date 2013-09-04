#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight(void)
{
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
	m_point.push_back(Vector(0,0,0));
	m_colour.reset(new Colour(1,1,1));
}

PointLight::~PointLight(void)
{
	m_colour.reset();
	m_objectMatrix.reset();
}

const Matrix& PointLight::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void PointLight::SetObjectMatrix( const Matrix& m)
{
	m_objectMatrix.reset(new Matrix(m));
	Vector p = m.Multiply( Vector(0,0,0) );
	m_point.clear();
	m_point.push_back(p);
}

std::vector<const Vector> PointLight::Samples() const
{
	return m_point;
}
