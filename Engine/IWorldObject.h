#pragma once

#include "IIntersectable.h"
#include "Matrix.h"

class IWorldObject
{
	virtual const Matrix& GetObjectMatrix() const = 0;
	virtual void SetObjectMatrix(const Matrix&) = 0;
};