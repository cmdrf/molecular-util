/*	TestFloatToHalf.cpp
	Copyright 2016-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/FloatToHalf.h>
#include <limits>

TEST_CASE("TestFloatToHalf")
{
	molecular::FloatToHalf fth;

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
