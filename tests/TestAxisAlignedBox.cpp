/*	TestAxisAlignedBox.cpp

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
#include <molecular/util/AxisAlignedBox.h>

using namespace molecular;
using namespace molecular::util;

TEST_CASE("TestOverlap")
{
	AxisAlignedBox box1(-1, -1, -1, 1, 1, 1);
	AxisAlignedBox box2(0, 0, 0, 2, 2, 2);
	AxisAlignedBox box3(-5, -5, -4, -4, -4, 1);
	AxisAlignedBox box4(-4, -4, -4, 5, 5, 5);

	CHECK(box1.Overlap(box2) == Approx(1.0));
	CHECK(box1.Overlap(box3) == Approx(0.0));
	CHECK(box1.Overlap(box4) == Approx(8.0));
}

TEST_CASE("TestEncloses")
{
	AxisAlignedBox box1(-1, -1, -1, 1, 1, 1);
	AxisAlignedBox box2(-2, -2, -2, 2, 2, 2);
	CHECK(!box1.Encloses(box2));
	CHECK(box2.Encloses(box1));
	CHECK(box1.Encloses(box1));
}

TEST_CASE("TestStretch")
{
	AxisAlignedBox box1(-1, -1, -1, 1, 1, 1);
	AxisAlignedBox box2(0, 0, 0, 2, 2, 2);
	box1.Stretch(box2);
	CHECK(box1.Encloses(box2));
}

TEST_CASE("TestLineIntersection")
{
	AxisAlignedBox box(-1, -1, -1, 1, 1, 1);
	AxisAlignedBox::LineIntersectionResult result;

	result = box.LineIntersection(Vector3(-2, 0, 0), Vector3(2, 0, 0));
	CHECK(0 == result.hitAxis);
	CHECK(-1 == result.hitDirection);
	CHECK(result.fraction == Approx(0.25));

	result = box.LineIntersection(Vector3(2, 0, 0), Vector3(-2, 0, 0));
	CHECK(0 == result.hitAxis);
	CHECK(1 == result.hitDirection);
	CHECK(result.fraction == Approx(0.25));

	result = box.LineIntersection(Vector3(0, -2, 0), Vector3(1.5, 0, 0));
	CHECK(1 == result.hitAxis);
	CHECK(-1 == result.hitDirection);

	result = box.LineIntersection(Vector3(2, 0, 0), Vector3(0, 3, 0));
	CHECK(result.fraction < 0);
}
