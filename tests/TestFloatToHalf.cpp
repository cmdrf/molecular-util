/*	TestFloatToHalf.cpp

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
#include <molecular/util/FloatToHalf.h>
#include <limits>

TEST_CASE("TestFloatToHalf")
{
	molecular::util::FloatToHalf fth;

	CHECK(0b0'01111'0000000000 == fth.Convert(1.0f));
	CHECK(0b0'01111'0000000001 == fth.Convert(1.0009765625f)); // (next smallest float after 1)
	CHECK(0b1'10000'0000000000 == fth.Convert(-2.0f));
	CHECK(0b0'11110'1111111111 == fth.Convert(65504.0f)); // (max half precision)

	CHECK(0b0'00001'0000000000 == fth.Convert(6.10352e-5f)); // (minimum positive normal)
	CHECK(0b0'00000'1111111111 == fth.Convert(6.09756e-5f)); // (maximum subnormal)
//	CHECK(0b0'00000'0000000001 == fth.Convert(5.96046e-8f)); // (minimum positive subnormal)

	CHECK(0b0'00000'0000000000 == fth.Convert(0.0f));
	CHECK(0b1'00000'0000000000 == fth.Convert(-0.0f));

	CHECK(0b0'11111'0000000000 == fth.Convert(std::numeric_limits<float>::infinity()));
	CHECK(0b1'11111'0000000000 == fth.Convert(-std::numeric_limits<float>::infinity()));

	CHECK(0b0'01101'0101010101 == fth.Convert(0.333251953125f)); // 1/3
}
