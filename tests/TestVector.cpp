/*	TestVector.cpp
	Copyright 2013-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/Vector3.h>

using namespace molecular;

TEST_CASE("TestLength")
{
	Vector3 v(3, -4, 0);
	CHECK(v.Length() == Approx(5));

	Vector3 w(3, -2, 6);
	CHECK(w.Length() == Approx(7));
	CHECK(w.LengthSquared() == Approx(49));
}

TEST_CASE("TestDotProduct")
{
	Vector3 a(1, 2, 3);
	Vector3 b(-7, 8, 9);
	CHECK(a.Dot(b) == Approx(36));

	Vector3 a2(1, 3, -5);
	Vector3 b2(4, -2, -1);
	CHECK(a2.Dot(b2) == Approx(3));
}

TEST_CASE("TestCrossProduct")
{
	Vector3 a(1, 2, 3);
	Vector3 b(-7, 8, 9);
	Vector3 c = a.CrossProduct(b);
	CHECK(c[0] == Approx(-6));
	CHECK(c[1] == Approx(-30));
	CHECK(c[2] == Approx(22));
}
