#pragma once

#include <vector>
#include "Vector.h"
#include "Colour.h"

class ILight
{
public:
	virtual const Colour& GetColour() const = 0; 
	virtual std::vector<Vector> Samples() const = 0;
};