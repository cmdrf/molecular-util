/*	SphericalHarmonics.cpp

MIT License

Copyright (c) 2018-2019 Fabian Herb

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "SphericalHarmonics.h"
#include <molecular/util/Matrix3.h>
#include <cassert>
#include <random>

namespace molecular
{
namespace util
{
namespace SphericalHarmonics
{

/** https://en.wikipedia.org/wiki/Associated_Legendre_polynomials */
double AssociatedLegendrePolynomial(int l, int m, double x)
{
	assert(l <= 3);
	assert(m <= 3);
	assert(m >= -3);

	if(l == 0 && m == 0)
	{
		return 1.0;
	}
	else if(l == 1)
	{
		if(m == -1)
			return -0.5 * AssociatedLegendrePolynomial(1, 1, x);
		else if(m == 0)
			return x;
		else if(m == 1)
			return -std::sqrt(1 - x * x);
	}
	else if(l == 2)
	{
		if(m == -2)
			return 0.04166666666666667 * AssociatedLegendrePolynomial(2, 2, x);
		else if(m == -1)
			return 0.16666666666666667 * AssociatedLegendrePolynomial(2, 1, x);
		else if(m == 0)
			return 0.5 * (3 * x * x - 1);
		else if(m == 1)
			return -3 * x * std::sqrt(1 - x * x);
		else if(m == 2)
			return 3 * (1 - x * x);
	}
	else if(l == 3)
	{
		if(m == -3)
			return -0.00138888888888888889 * AssociatedLegendrePolynomial(3, 3, x);
		else if(m == -2)
			return 0.00833333333333333333 * AssociatedLegendrePolynomial(3, 2, x);
		else if(m == -1)
			return -0.0833333333333333333 * AssociatedLegendrePolynomial(3, 1, x);
		else if(m == 0)
			return 0.5 * (5 * x * x * x - 3.0 * x);
		else if(m == 1)
			return -1.5 * (5 * x * x - 1.0) * std::sqrt(1 - x * x);
		else if(m == 2)
			return 15 * x * (1 - x * x);
		else if(m == 3)
			return 15 * x * x * std::sqrt(1 - x * x) - 15 * std::sqrt(1 - x * x);
	}

	assert(false);
	return 0.0;
}

double Factorial(int x)
{
	static const double table[] = {
		/*0*/	1.0,
		/*1*/	1.0,
		/*2*/	2.0,
		/*3*/	6,
		/*4*/	24,
		/*5*/	120,
		/*6*/	720,
		/*7*/	5040,
		/*8*/	40320,
		/*9*/	362880,
		/*10*/	3628800,
		/*11*/	39916800,
		/*12*/	479001600,
		/*13*/	6227020800,
		/*14*/	87178291200,
		/*15*/	1307674368000,
		/*16*/	20922789888000,
		/*17*/	355687428096000,
		/*18*/	6402373705728000,
		/*19*/	121645100408832000,
		/*20*/	2432902008176640000,
		/*21*/	51090942171709440000.0,
		/*22*/	1124000727777607680000.0,
		/*23*/	25852016738884976640000.0,
		/*24*/	6.2044840173323943936e23,
		/*25*/	1.5511210043330985984e25,
		/*26*/	4.03291461126605635584e26,
		/*27*/	1.0888869450418352160768e28,
		/*28*/	3.04888344611713860501504e29,
		/*29*/	8.841761993739701954543616e30,
		/*30*/	2.6525285981219105863630848e32,
		/*31*/	8.22283865417792281772556288e33,
		/*32*/	2.6313083693369353016721801216e35,
		/*33*/	8.68331761881188649551819440128e36,
		/*34*/	2.9523279903960414084761860964352e38,
		/*35*/	1.03331479663861449296666513375232e40
	};
	assert(x >= 0 && x < static_cast<int>(sizeof(table)));
	return table[x];
}

double ShRenormalisation(int l, int m)
{
	return std::sqrt((Factorial(l - m) * (2.0 * l + 1.0)) / (Factorial(l + m) * 4.0 * Math::kPi_d));
}

double SphericalHarmonic(int l, int m, double theta, double phi)
{
	if(m > 0)
		return std::sqrt(2.0) * ShRenormalisation(l, m) * std::cos(m * phi) * AssociatedLegendrePolynomial(l, m, std::cos(theta));
	else if(m == 0)
		return ShRenormalisation(l, 0) * AssociatedLegendrePolynomial(l, m, std::cos(theta));
	else // m < 0
		return std::sqrt(2.0) * ShRenormalisation(l, -m) * std::sin(-m * phi) * AssociatedLegendrePolynomial(l, -m, std::cos(theta));
}

Vector3d UnitVectorFromSphericalCoords(double theta, double phi)
{
	return Vector3d(std::sin(theta) * std::cos(phi), std::sin(theta) * std::sin(phi), std::cos(theta));
}

template<int numBands>
std::vector<Sample<numBands>> SetupSphericalSamples(unsigned int samplesCount)
{
	std::vector<Sample<numBands>> samples;
	samples.reserve(samplesCount * samplesCount);
	std::mt19937 randomEngine;
	std::uniform_real_distribution<double> randomDist(0, 1);

	const double samplesCountInv = 1.0 / samplesCount;
	for(unsigned int i = 0; i < samplesCount; i++)
	{
		for(unsigned int j = 0; j < samplesCount; j++)
		{
			Sample<numBands> sample;
			const double u = i + randomDist(randomEngine);
			const double v = j + randomDist(randomEngine);
			sample.theta = 2.0 * std::acos(sqrt(1.0 - u * samplesCountInv));
			sample.phi = 2.0 * Math::kPi_d * v * samplesCountInv;
			sample.vec = UnitVectorFromSphericalCoords(sample.theta, sample.phi);

			for(int l = 0; l < numBands; ++l)
			{
				for(int m = -l; m <= l; ++m)
					sample.coeff[l * (1 + l) + m] = SphericalHarmonic(l, m, sample.theta, sample.phi);
			}
			samples.push_back(sample);
		}
	}
	return samples;
}

template std::vector<Sample<3>> SetupSphericalSamples<3>(unsigned int samplesCount);
template std::vector<Sample<4>> SetupSphericalSamples<4>(unsigned int samplesCount);

// 9 multiplies
template<typename T>
void OptRotateBand1(T dst[3], const T src[3],
	T m00, T m01, T m02,
	T m10, T m11, T m12,
	T m20, T m21, T m22)
{
	dst[0] =  m11 * src[0] + -m12 * src[1] +  m10 * src[2];
	dst[1] = -m21 * src[0] +  m22 * src[1] + -m20 * src[2];
	dst[2] =  m01 * src[0] + -m02 * src[1] +  m00 * src[2];
}


// 48 multiplies
template<typename T>
void OptRotateBand2(T dst[5], const T x[5],
								  T m00, T m01, T m02,
								  T m10, T m11, T m12,
								  T m20, T m21, T m22)
{
	const static T s_c3 = T(0.94617469575); // (3*sqrt(5))/(4*sqrt(pi))
	const static T s_c4 = T(-0.31539156525);// (-sqrt(5))/(4*sqrt(pi))
	const static T s_c5 = T(0.54627421529); // (sqrt(15))/(4*sqrt(pi))

	const static T s_c_scale = T(1.0/0.91529123286551084);
	const static T s_c_scale_inv = T(0.91529123286551084);

	const static T s_rc2 = T(1.5853309190550713) * s_c_scale;
	const static T s_c4_div_c3 = s_c4/s_c3;
	const static T s_c4_div_c3_x2 = (s_c4/s_c3)*2.0;

	const static T s_scale_dst2 = s_c3 * s_c_scale_inv;
	const static T s_scale_dst4 = s_c5 * s_c_scale_inv;

	// Sparse matrix multiply
	T sh0 =  x[3] + x[4] + x[4] - x[1];
	T sh1 =  x[0] + s_rc2*x[2] +  x[3] + x[4];
	T sh2 =  x[0];
	T sh3 = -x[3];
	T sh4 = -x[1];

	// Rotations.  R0 and R1 just use the raw matrix columns
	T r2x = m00 + m01;
	T r2y = m10 + m11;
	T r2z = m20 + m21;

	T r3x = m00 + m02;
	T r3y = m10 + m12;
	T r3z = m20 + m22;

	T r4x = m01 + m02;
	T r4y = m11 + m12;
	T r4z = m21 + m22;

	// dense matrix multiplication one column at a time

	// column 0
	T sh0_x = sh0 * m00;
	T sh0_y = sh0 * m10;
	T d0 = sh0_x * m10;
	T d1 = sh0_y * m20;
	T d2 = sh0 * (m20 * m20 + s_c4_div_c3);
	T d3 = sh0_x * m20;
	T d4 = sh0_x * m00 - sh0_y * m10;

	// column 1
	T sh1_x = sh1 * m02;
	T sh1_y = sh1 * m12;
	d0 += sh1_x * m12;
	d1 += sh1_y * m22;
	d2 += sh1 * (m22 * m22 + s_c4_div_c3);
	d3 += sh1_x * m22;
	d4 += sh1_x * m02 - sh1_y * m12;

	// column 2
	T sh2_x = sh2 * r2x;
	T sh2_y = sh2 * r2y;
	d0 += sh2_x * r2y;
	d1 += sh2_y * r2z;
	d2 += sh2 * (r2z * r2z + s_c4_div_c3_x2);
	d3 += sh2_x * r2z;
	d4 += sh2_x * r2x - sh2_y * r2y;

	// column 3
	T sh3_x = sh3 * r3x;
	T sh3_y = sh3 * r3y;
	d0 += sh3_x * r3y;
	d1 += sh3_y * r3z;
	d2 += sh3 * (r3z * r3z + s_c4_div_c3_x2);
	d3 += sh3_x * r3z;
	d4 += sh3_x * r3x - sh3_y * r3y;

	// column 4
	T sh4_x = sh4 * r4x;
	T sh4_y = sh4 * r4y;
	d0 += sh4_x * r4y;
	d1 += sh4_y * r4z;
	d2 += sh4 * (r4z * r4z + s_c4_div_c3_x2);
	d3 += sh4_x * r4z;
	d4 += sh4_x * r4x - sh4_y * r4y;

	// extra multipliers
	dst[0] = d0;
	dst[1] = -d1;
	dst[2] = d2 * s_scale_dst2;
	dst[3] = -d3;
	dst[4] = d4 * s_scale_dst4;
}

template<typename T>
void RotateOrder3(T dst[9], const T src[9], const T mat[3][3])
{
	dst[0] = src[0]; // Band 0
	OptRotateBand1(&dst[1], &src[1],
			mat[0][0], mat[0][1], mat[0][2],
			mat[1][0], mat[1][1], mat[1][2],
			mat[2][0], mat[2][1], mat[2][2]);
	OptRotateBand2(&dst[4], &src[4],
			mat[0][0], mat[0][1], mat[0][2],
			mat[1][0], mat[1][1], mat[1][2],
			mat[2][0], mat[2][1], mat[2][2]);
}

template void RotateOrder3(double dst[9], const double src[9], const double mat[3][3]);
template void RotateOrder3(float dst[9], const float src[9], const float mat[3][3]);

void RotateOrder3(float dst[9], const float src[9], const Matrix3& mat)
{
	dst[0] = src[0]; // Band 0
	OptRotateBand1(&dst[1], &src[1],
			mat(0, 0), mat(0, 1), mat(0, 2),
			mat(1, 0), mat(1, 1), mat(1, 2),
			mat(2, 0), mat(2, 1), mat(2, 2));
	OptRotateBand2(&dst[4], &src[4],
			mat(0, 0), mat(0, 1), mat(0, 2),
			mat(1, 0), mat(1, 1), mat(1, 2),
			mat(2, 0), mat(2, 1), mat(2, 2));
}

}
}
}
