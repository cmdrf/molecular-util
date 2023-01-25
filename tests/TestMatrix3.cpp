/*	TestMatrix3.cpp

MIT License

Copyright (c) 2019-2023 Fabian Herb

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

#include <catch2/catch_test_macros.hpp>
#include <molecular/testbed/Matchers.h>
#include <molecular/util/Matrix3.h>

using namespace Catch;
using namespace molecular;
using namespace molecular::util;
using namespace molecular::testbed;

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
