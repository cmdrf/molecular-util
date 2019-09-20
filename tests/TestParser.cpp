/*	TestParser.cpp

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
#include <molecular/util/Parser.h>

using namespace molecular::Parser;

TEST_CASE("TestParser")
{
	const char* test1 = "12312";

	void* nullActor = nullptr;

	const char* begin = test1;
	const char* end = test1 + 5;
	CHECK(Integer::Parse(begin, end, nullActor));
	CHECK(begin == end);

	const char* test2 = "12t12";

	begin = test2;
	end = test2 + 5;
	CHECK(Integer::Parse(begin, end, nullActor));
	CHECK(begin != end);

	const char* test3 = "-45.239e10";
	begin = test3;
	end = test3 + 10;
	CHECK(Real::Parse(begin, end, nullActor));
	CHECK(begin == end);
}

struct ParserTest
{
	ParserTest()
	{
		mIntegerCalled = 0;
		mRealCalled = 0;
	}

	void ParserAction(int action, const char* begin, const char* end)
	{
		if(action == kInteger)
		{
			CHECK(4 == end - begin);
			CHECK(std::equal(begin, begin + 4, "1234"));
			mIntegerCalled++;
		}
		else if(action == kReal)
		{
			CHECK(6 == end - begin);
			CHECK(std::equal(begin, begin + 6, "123.34"));
			mRealCalled++;
		}
		else
			CHECK(false);
	}

	enum
	{
		kInteger,
		kReal
	};

	int mIntegerCalled;
	int mRealCalled;
};

TEST_CASE_METHOD(ParserTest, "ParserTest1")
{
	const char text[] =
			"i=1234;"
			"r=123.34;"
			"i=1234;";
	const char* begin = text;
	const char* end = text + sizeof(text);

	typedef Concatenation<Char<'i'>, Char<'='>, Action<Integer, kInteger>, Char<';'> > IntExpression;
	typedef Concatenation<Char<'r'>, Char<'='>, Action<Real, kReal>, Char<';'> > RealExpression;
	typedef Concatenation<Repetition<Alternation<IntExpression, RealExpression> >, Char<0> >File;

	CHECK(File::Parse(begin, end, this));
	CHECK(begin == end);

	CHECK(2 == mIntegerCalled);
	CHECK(1 == mRealCalled);
}
