/*	TestMatrix.cpp

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
#include <molecular/testbed/Matchers.h>
#include <molecular/util/Matrix.h>

using namespace molecular;

TEST_CASE("TestMatrixConstructor")
{
	Matrix<2, 2> mat = {1, 2, 3, 4};
	CHECK(mat(0, 0) == Approx(1));
	CHECK(mat(0, 1) == Approx(2));
	CHECK(mat(1, 0) == Approx(3));
	CHECK(mat(1, 1) == Approx(4));
}

TEST_CASE("TestMatrixProduct")
{
	Matrix<2, 3> mat1 = {1, 2, 3,
						4, 5, 6};
	Matrix<3, 2> mat2 = {6, -1,
						3, 2,
						0, -3};;
	Matrix<2, 2> mat3 = mat1 * mat2;

	Matrix<2, 2> expected = {12, -6, 39, -12};
	CHECK_THAT(mat3, EqualsApprox(expected));
}

TEST_CASE("TestInverse")
{
	{
		// Condition number: 40
		const float data[] = {1, 2, 0,
						2, 3, 0,
						3, 4, 1};
		Matrix<3, 3> mat(data);
		Matrix<3, 3> mat2 = mat.Inverse();
		Matrix<3, 3> expected = {-3, 2, 0,
							2, -1, 0,
							1, -2, 1};
		CHECK_THAT(mat2, EqualsApprox(expected));
	}
	{
		// Condition number: 4.249
		Matrix<3, 3> mat = {0, 2.06597f, 2.74879f, 0, -2.1099f, -0.112644f, -2.31367f, -2.49692f, -0.853853f};
		Matrix<3, 3> mat2 = mat.Inverse();
		Matrix<3, 3> expected = {-0.118033f, 0.395919f, -0.432214f,
							-0.0202344f , -0.493769f , 0,
							0.379004f , 0.371113f , 0};
		CHECK_THAT(mat2, EqualsApprox(expected));
	}
}

TEST_CASE("TestMatrixTransposed")
{
	Matrix<2, 3> mat1 = {1, 8, -3,
						4, -2, 5};
	Matrix<3, 2> transposed = mat1.Transposed();
	Matrix<3, 2> expected = {1, 4,
							  8, -2,
							  -3, 5};
	CHECK_THAT(transposed, EqualsApprox(expected));
}

TEST_CASE("TestSubmatrix")
{
	Matrix<3, 3> mat = {1, 2, 0,
						2, 3, 0,
						3, 4, 1};
	Matrix<3, 2> subLeft = mat.SubMatrixLeft<2>();
	Matrix<3, 2> expectedLeft = {1, 2,
					   2, 3,
					   3, 4};
	CHECK_THAT(subLeft, EqualsApprox(expectedLeft));
	Matrix<3, 2> subRight = mat.SubMatrixRight<2>();
	Matrix<3, 2> expectedRight = {2, 0,
					   3, 0,
					   4, 1};
	CHECK_THAT(subRight, EqualsApprox(expectedRight));
}
