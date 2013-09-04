#include "stdafx.h"
#include "AreaLight.h"
#include <math.h>

AreaLight::~AreaLight( void )
{
	m_objectMatrix.reset();
}

AreaLight::AreaLight( unsigned int w, unsigned int h, decimal fuzz ) : m_w(w), m_h(h), m_fuzz(fuzz)
{
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
}

const Matrix& AreaLight::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void AreaLight::SetObjectMatrix( const Matrix& m )
{
	m_objectMatrix.reset(new Matrix(m));
}

std::vector<const Vector> AreaLight::Samples() const
{
	std::vector<const Vector> points;
	for(decimal x = 0 ; x < m_w; x++)
	{
		for(decimal y= 0; y< m_h; y++)
		{
			decimal xOff = -0.5 + decimal(rand()) / RAND_MAX;
			decimal yOff = -0.5 + decimal(rand()) / RAND_MAX;
			decimal xBase = x - (m_w - 1) / 2;
			decimal yBase = y - (m_h - 1) / 2;

			Vector point( xBase + xOff, 0, yBase + yOff);

			points.push_back( m_objectMatrix->Multiply(point));
		}
	}

	return points;
}
