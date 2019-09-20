/*	TestHash.cpp

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
