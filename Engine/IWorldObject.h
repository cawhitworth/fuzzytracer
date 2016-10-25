#pragma once

#include "Matrix.h"

class IWorldObject
{
public:
    virtual ~IWorldObject() {}

private:
    virtual const Matrix& GetObjectMatrix() const = 0;
	virtual void SetObjectMatrix(const Matrix&) = 0;
};