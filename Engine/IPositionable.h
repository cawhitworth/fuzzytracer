#pragma once

#include "Matrix.h"

class IPositionable
{
public:
	virtual const Matrix& GetObjectMatrix() = 0;
	virtual void SetObjectMatrix(const Matrix&) = 0;
};