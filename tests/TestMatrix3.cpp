/*	TestMatrix3.cpp
	Copyright 2016-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include "Matchers.h"
#include <molecular/util/Matrix3.h>

using namespace molecular;

TEST_CASE("TestMatrix3FromQuaternion")
{
	Matrix3 mat = Matrix3(Quaternion(0.342997f, 0.171499f, -0.342997f, 0.857493f));
	Matrix3 t = {
		-0.705882f, -0.705882f, 0.0588235f,
		0.470588f, -0.529412f, -0.705882f,
		0.529412f, -0.470588f, 0.705882f
	};
	CHECK_THAT(mat, EqualsApprox(t, 0.0001));

}

TEST_CASE("TestMatrix3ToQuaternion")
{
	Matrix3 mat = Matrix3(
		-0.705882f, -0.705882f, 0.0588235f,
		0.470588f, -0.529412f, -0.705882f,
		0.529412f, -0.470588f, 0.705882f
	);
	Quaternion q = mat.ToQuaternion();
	CHECK_THAT(q, EqualsApprox(Quaternion(0.342997f, 0.171499f, -0.342997f, 0.857493f)));
}

TEST_CASE("TestMatrix3GetScale")
{
	Matrix3 rot(
		-0.705882f, -0.705882f, 0.0588235f,
		0.470588f, -0.529412f, -0.705882f,
		0.529412f, -0.470588f, 0.705882f);
	Matrix3 scaleMat = Matrix3::Scale(3.2f);
	Matrix3 m = rot * scaleMat;
	CHECK(m.GetScale() == Approx(3.2f));
}

TEST_CASE("TestDeterminant")
{
	Matrix3 m(
		0, 1, 2,
		3, 2, 1,
		1, 1, 0);
	CHECK(m.Determinant() == Approx(3));
}
