#pragma once

#include <vector>
#include "Utilities.h"

#define CLAMP(x) ( (x < 0) ? 0 : ( (x > 1) ? 1 : x ) )

template<typename T>
class Col
{
public:
	const T r,g,b;

	Col<T>() : r(0), g(0), b(0) {}
	Col<T>(T r, T g, T b) : r(r), g(g), b(b) {}
	Col<T>(const Col<T>& rhs) : r(rhs.r), g(rhs.g), b(rhs.b) {}

	const Col<T> Multiply(T scale) const
	{
		return Col<T>(r * scale, g * scale, b * scale);
	}

	const Col<T> Clamp() const
	{
		return Col<T>(CLAMP(r), CLAMP(g), CLAMP(b));
	}

	const T Luminance() const
	{
		return (r + g + b) / 3.0;
	}

	static const Col<T> Average(std::vector<const Col<T> > cols);

};

template<typename T>
const Col<T> Col<T>::Average(std::vector<const Col<T> > cols)
{
	if (cols.size() == 1)
		return cols[0];

	int i = 0;
	T r = 0,g = 0,b = 0;
	for(auto c : cols)
	{
		i++;
		r += c.r;
		g += c.g;
		b += c.b;
	}

	if (i == 0)
		return Col<T>();

	return Col<T>(r / i, g / i, b / i);
}

typedef Col<decimal> Colour;