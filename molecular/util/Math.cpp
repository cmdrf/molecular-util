/* Math.cpp
	Copyright 2016 Fabian Herb

	This file is part of Molecular Engine.
*/

#include "Math.h"
#include <cmath>
#include <array>

namespace Math
{

template<typename T>
T Sqr(T x)
{
	return x * x;
}

template<typename T>
inline T Newton1(const T a[3], T x)
{
	T y = a[2] + x;
	T y1 = 2 * y + x;
	y1 = x * y1 + a[1];
	y = (x * y + a[1]) * x + a[0];
	if (y1 != 0.0)
		x -= y / y1;
	return x;
}

inline int QuadraticPolynomialRoot(const double a[2], double x[], int i, int j)
{
	double p = -0.5 * a[1];
	double d = Sqr(p) - a[0];
	if (d >= 0.0)
	{
		d = std::sqrt(d);
		x[i] = p - d;
		x[j] = p + d;
		return 2;
	}
	return 0;
}

inline int QuadraticPolynomialRoot(const double a[2], const double o[3], double x[], int i, int j)
{
	double p = -0.5 * a[1];
	double d = Sqr(p) - a[0];
	if (d >= 0.0)
	{
		d = std::sqrt(d);
		if (p < 0.0)
		{
			x[i] = Newton1(o, p - d);
			x[j] = p + d;
		}
		else
		{
			x[i] = p - d;
			x[j] = Newton1(o, p + d);
		}
		return 2;
	}
	return 0;
}

int CubicPolynomialRoot(const double a[4], double x[3])
{
	if(a[3] == 0.0)
	{
		if (a[2] == 0.0)
		{
			if (a[1] == 0.0)
				return 0;
			else
			{
				x[0] = -a[0] / a[1];
				return 1;
			}
		}
		else
		{
			double w = 1.0 / a[2];
			double c[2] = {a[0] * w, a[1] * w};
			return QuadraticPolynomialRoot(c, x, 0, 1);
		}
	}

	const double w = 1.0 / a[3];
	double b[3] = {a[0] * w, a[1] * w, a[2] * w};

	if (b[0] == 0.0)
	{
		x[0] = 0.0;
		if (QuadraticPolynomialRoot(b + 1, x, 1, 2) == 0)
			return 1;
		else
		{
			if (x[2] < 0.0)
			{
				x[0] = x[1];
				x[1] = x[2];
				x[2] = 0.0;
			}
			else if (x[1] < 0.0)
			{
				x[0] = x[1];
				x[1] = 0.0;
			}
			return 3;
		}
	}

	double xh =-1.0 / 3.0 * b[2];
	double y = b[0] + xh * (b[1] + xh * (b[2] + xh));
	if(y == 0.0)
	{
		x[0] = x[1] = xh;
		double c[2];
		c[1] = xh + b[2]; // deflation
		c[0] = c[1] * xh + b[1];
		return 1 + QuadraticPolynomialRoot(c, x, 0, 2);
	}
	int i_loc = (y >= 0.0);
	double d = Sqr(b[2]) - 3 * b[1];
	if (d > 0)
		xh += ((i_loc) ? -2.0 / 3.0 : 2.0 / 3.0) * std::sqrt(d);
	else if (d == 0.0)
	{
		x[0] = xh - cbrt(y);
		return 1;
	}
	double dx;
	const double prec = 1.0e-6;
	do {
		y = b[2] + xh;
		double y1 = 2 * y + xh;
		double y2 = y1 + 3 * xh;
		y1 = xh * y1 + b[1];
		y = (xh * y + b[1]) * xh + b[0];
		dx = y * y1 / (Sqr(y1) - 0.5 * y * y2); xh -= dx;
	} while (std::abs(dx) > prec * std::abs(xh));

	x[0] = x[2] = xh;
	if (d > 0.0)
	{
		double c[2];
		c[1] = xh + b[2]; // deflation
		c[0] = c[1] * xh + b[1];
		return 1 + QuadraticPolynomialRoot(c, b, x, i_loc, i_loc + 1);
	}
	return 1;
}

template<typename T>
T PositiveCubicPolynomialRoot(T a, T b, T c)
{
	std::array<double, 4> as = {{c, b, a, 1.0}};
	std::array<double, 3> x;
	int results = CubicPolynomialRoot(as.data(), x.data());
	for(int i = 0; i < results; ++i)
		if(x[i] > 0.0)
			return x[i];
	return 0.0;
}

template double PositiveCubicPolynomialRoot(double, double, double);
template float PositiveCubicPolynomialRoot(float, float, float);

}
