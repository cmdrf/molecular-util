#ifndef MOLECULAR_MATH_H
#define MOLECULAR_MATH_H

#include <algorithm>
#include "Vector3.h"

namespace molecular
{
namespace Math
{

static constexpr double kPi_d = 3.1415926535897932384626433832795029;

template<typename T>
T Clamp(T a, T min, T max)
{
	return std::max(min, std::min(max, a));
}

/// solve cubic equation x^3 + a*x^2 + b*x + c
template<typename T>
T PositiveCubicPolynomialRoot(T a, T b, T c);

template<typename T>
T PositiveQuadraticPolynomialRoot(T a, T b, T c)
{
	T r = std::sqrt(b * b - 4 * a * c);
	T s = 2 * a;
	T x1 = (-b + r) / s;
	if(x1 >= 0)
		return x1;
	else
		return (-b - r) / s;
}

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
inline Vector3 Barycentric(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& p)
{
	Vector3 v0 = b - a, v1 = c - a, v2 = p - a;
	float d00 = v0.DotProduct(v0);
	float d01 = v0.DotProduct(v1);
	float d11 = v1.DotProduct(v1);
	float d20 = v2.DotProduct(v0);
	float d21 = v2.DotProduct(v1);
	float denom = d00 * d11 - d01 * d01;
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;
	return Vector3(u, v, w);
}

} // Math
} // molecular

#endif // MOLECULAR_MATH_H
