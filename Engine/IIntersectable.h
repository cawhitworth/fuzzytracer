#pragma once

#include "Utilities.h"
#include "Vector.h"
#include "Colour.h"

class IIntersectable
{
public:
    virtual ~IIntersectable() {}

    virtual bool Intersect(const Vector& rayOrigin, const Vector& rayDirection, decimal& t) const = 0;
    virtual Vector Normal(const Vector& intersectPoint) const = 0;
    virtual Colour ColourAt(const Vector& intersectPoint) const = 0;
};