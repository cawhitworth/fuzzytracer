#pragma once

#include "Vector.h"
#include "Matrix.h"

#define TOLERANCE 0.001

bool WithinTolerance(decimal d1, decimal d2);

bool WithinTolerance(const Vector& v1, const Vector& v2);

bool WithinTolerance(const Matrix& m1, const Matrix& m2);