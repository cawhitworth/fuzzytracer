#pragma once
#include "Vector.h"
#include <vector>

class ILight
{
public:
	virtual std::vector<const Vector> Samples() const = 0;
};