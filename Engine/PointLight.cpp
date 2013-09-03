#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight(void)
{
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
	m_point.reset(new Vector(0,0,0));
}

PointLight::~PointLight(void)
{
	m_objectMatrix.reset();
	m_point.reset();
}

const Matrix& PointLight::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void PointLight::SetObjectMatrix( const Matrix& m)
{
	m_objectMatrix.reset(new Matrix(m));
	Vector p = m.Multiply( Vector(0,0,0) );
	m_point.reset( new Vector(p) );
}

std::vector<const Vector> PointLight::Samples() const
{
	std::vector<const Vector> v;
	v.push_back(*m_point);
	return v;
}
