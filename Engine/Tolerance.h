#pragma once

#include <cmath>

#include "Utilities.h"
#include "Vector.h"
#include "Matrix.h"


#define TOLERANCE 0.00001

inline bool WithinTolerance( decimal d1, decimal d2 )
{
    return abs(d1-d2) < TOLERANCE;
}

inline bool WithinTolerance( const Vector& v1, const Vector& v2 )
{
    if ( abs(v1.x - v2.x) > TOLERANCE) return false;
    if ( abs(v1.y - v2.y) > TOLERANCE) return false;
    if ( abs(v1.z - v2.z) > TOLERANCE) return false;
    if ( abs(v1.w - v2.w) > TOLERANCE) return false;

    return true;
}

inline bool WithinTolerance( const Matrix& m1, const Matrix& m2 )
{
    for(int i = 0; i<16; i++)
    {
        if( abs(m1._d[i] - m2._d[i]) > TOLERANCE) return false;
    }
    return true;
}

