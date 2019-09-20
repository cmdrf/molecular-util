/*	TestMath.cpp
	Copyright 2016-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/Math.h>

using namespace molecular;

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
