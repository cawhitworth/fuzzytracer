#include "stdafx.h"
#include "AreaLight.h"

AreaLight::AreaLight( unsigned int w, unsigned int h, decimal fuzz) : m_w(w), m_h(h), m_fuzz(fuzz)
{
	m_colour.reset(new Colour(1,1,1));
	m_objectMatrix.reset(new Matrix(Matrix::Identity()));
}

AreaLight::~AreaLight( void )
{
	m_objectMatrix.reset();
	m_colour.reset();
}


const Matrix& AreaLight::GetObjectMatrix() const
{
	return *m_objectMatrix;
}

void AreaLight::SetObjectMatrix( const Matrix& m )
{
	m_objectMatrix.reset(new Matrix(m));
}

std::vector<Vector> AreaLight::Samples() const
{
	std::vector<Vector> points;
	for(decimal x = 0 ; x < m_w; x++)
	{
		for(decimal y= 0; y< m_h; y++)
		{
			decimal xOff = -0.5 + decimal(rand()) / RAND_MAX;
			decimal yOff = -0.5 + decimal(rand()) / RAND_MAX;
			decimal xBase = x - (m_w - 1) / 2;
			decimal yBase = y - (m_h - 1) / 2;

			Vector point( xBase + (m_fuzz*xOff), 0, yBase + (m_fuzz * yOff));

			points.push_back( m_objectMatrix->Multiply(point));
		}
	}

	return points;
}
