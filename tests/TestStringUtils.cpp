/*	TestStringUtils.cpp
	Copyright 2014-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/StringUtils.h>
#include <iostream>

using Catch::Matchers::Equals;
using namespace molecular;

TEST_CASE("TestScanF")
{
	float a = 0.0f, b = 0.0f;
	int c = 0;
	StringUtils::ScanF("1.23 bla 2.34 laber 345", "%f bla %f laber %d", &a, &b, &c);

	CHECK(a == Approx(1.23));
	CHECK(b == Approx(2.34));
	CHECK(345 == c);
}

TEST_CASE("TestEndsWith")
{
	CHECK(StringUtils::EndsWith("blablalaber", "aber") == true);
	CHECK(StringUtils::EndsWith("blablalaber", "123") == false);
	CHECK(StringUtils::EndsWith("bla", "laber") == false);
}
/*
TEST_CASE("TestBeginsWith")
{
	CHECK(StringUtils::BeginsWith("blablalaber", "blab") == true);
	CHECK(StringUtils::BeginsWith("blablalaber", "123") == false);
	CHECK(StringUtils::BeginsWith("bla", "laber") == false);
}

TEST_CASE("TestFileName")
{
	CHECK("blalbla.xyz" == StringUtils::FileName("asd/asd/blalbla.xyz"));
	CHECK("blalbla.xyz" == StringUtils::FileName("asd/asd\\blalbla.xyz"));
	CHECK("" == StringUtils::FileName("/asd/asd/"));
}

TEST_CASE("TestFilenameWithoutExtension")
{
	auto filename = StringUtils::FileNameWithoutExtension("/asd/asd.asd/abcdef.x.xyu");
	CHECK("abcdef" == filename);
}

TEST_CASE("TestSnPrintF")
{
	char buffer[128];
	const char test[] = "test";
	StringUtils::SnPrintF(buffer, 128, "%s @%s", test, test);
	CHECK_THAT(buffer, Equals("test @test"));
}

TEST_CASE("TestExplode")
{
	auto result = StringUtils::Explode("bla,laber,,lall,", ',');
	CHECK(5 == result.size());
	CHECK("bla" == result.at(0));
	CHECK("laber" == result.at(1));
	CHECK("" == result.at(2));
	CHECK("lall" == result.at(3));
	CHECK("" == result.at(4));

	result = StringUtils::Explode("bla;laber;\nlall\r\n", ";\r\n");
	CHECK(6 == result.size());
	CHECK("bla" == result.at(0));
	CHECK("laber" == result.at(1));
	CHECK("" == result.at(2));
	CHECK("lall" == result.at(3));
	CHECK("" == result.at(4));
	CHECK("" == result.at(5));
}

TEST_CASE("TestWrapLines")
{
	const char* expected = "Hallo bla bla\nbla0123456789\nbla\nlorem ipsum\ndolor";

	char text[] = {"Hallo bla bla bla0123456789 bla\nlorem ipsum dolor"};
	char out[sizeof(text)];

	StringUtils::SimpleWordWrap(text, out, 10);
	CHECK_THAT(out, Equals(expected));

	StringUtils::SimpleWordWrap(text, 10);
	CHECK_THAT(out, Equals(expected));
}
*/
