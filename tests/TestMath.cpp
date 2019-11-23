/*	TestMath.cpp

MIT License

Copyright (c) 2019 Fabian Herb

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

#include <catch.hpp>
#include <molecular/util/Math.h>

using namespace molecular::util;

TEST_CASE("TestPositiveQuadraticPolynomialRoot")
{
	CHECK(Math::PositiveQuadraticPolynomialRoot(1.0, -1.0, -2.0) == Approx(2.0));
}

TEST_CASE("TestPositiveCubicPolynomialRoot")
{
	CHECK(Math::PositiveCubicPolynomialRoot(0.0, -15.0, -4.0) == Approx(4.0));
	CHECK(Math::PositiveCubicPolynomialRoot(0.0, -7.0, -6.0) == Approx(3.0));
	CHECK(Math::PositiveCubicPolynomialRoot(0.0, -5.0, -2.0) == Approx(2.41421));
}

TEST_CASE("TestBarycentric")
{
	float deg120 = Math::kPi_f * 2.0f / 3.0f;
	Vector3 t0(std::cos(deg120), std::sin(deg120), 0);
	Vector3 t1(1, 0, 0);
	Vector3 t2(std::cos(2.0f * deg120), std::sin(2.0f * deg120), 0);
	Vector3 p(0, 0, 0);
	Vector3 bary = Math::Barycentric(t0, t1, t2, p);
	CHECK(bary[0] == Approx(0.333333));
	CHECK(bary[1] == Approx(0.3333333));
	CHECK(bary[2] == Approx(0.3333333));
}
