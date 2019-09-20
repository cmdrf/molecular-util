/*	TestVector.cpp

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
