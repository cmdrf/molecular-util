/*	TestHash.cpp
	Copyright 2012-2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/Hash.h>

using namespace molecular;

TEST_CASE("TestMakeHashOverloads")
{
	std::string test("blaschwafel");
	Hash hash1 = HashUtils::MakeHash(test);
	Hash hash2 = HashUtils::MakeHash(test.c_str());
	Hash hash3 = HashUtils::MakeHash(test.data(), test.length());
	Hash hash4 = HashUtils::H("blaschwafel");

	CHECK(hash1 == hash2);
	CHECK(hash1 == hash3);
	CHECK(hash2 == hash3);
	CHECK(hash1 == hash4);
	CHECK(hash2 == hash4);
	CHECK(hash3 == hash4);
}

TEST_CASE("TestMurmurHash")
{
	CHECK(0x8e89e90c == Murmur::Hash("laber", 5));
	CHECK(0xe8901e6a == Murmur::Hash("dorfTrottel", 11));
	CHECK(0xdf6eb4e7 == Murmur::Hash("vier", 4));
	CHECK("vertexPositionAttr"_H == 0xe7dccea2);
	CHECK("vertexNormalAttr"_H == 0x11c36e42);
	CHECK("vertexUv0Attr"_H == 0x7dd0ace6);
	CHECK("vertexPrt0Attr"_H == 0xc03b4aec);
	CHECK("vertexPrt1Attr"_H == 0xa2739294);
	CHECK("vertexPrt2Attr"_H == 0x9d2051c8);
	CHECK("vertexSkinWeightsAttr"_H == 0xfc228c1f);
	CHECK("vertexSkinJointsAttr"_H == 0xe2cf8e75);
}
