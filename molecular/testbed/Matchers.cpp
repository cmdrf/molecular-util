/*	Matchers.cpp

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

#include "Matchers.h"

namespace molecular
{
namespace testbed
{

bool EqualsVector2::match(const Vector2& v) const
{
	return v[0] == Approx(mV[0]).epsilon(mEpsilon).margin(mMargin) && v[1] == Approx(mV[1]).epsilon(mEpsilon).margin(mMargin);
}

std::string EqualsVector2::describe() const
{
	std::ostringstream ss;
	ss << "equals approximately " << mV;
	return ss.str();
}

bool EqualsVector3::match(const Vector3& v) const
{
	return v[0] == Approx(mV[0]).epsilon(mEpsilon).margin(mMargin)
			&& v[1] == Approx(mV[1]).epsilon(mEpsilon).margin(mMargin)
			&& v[2] == Approx(mV[2]).epsilon(mEpsilon).margin(mMargin);
}

std::string EqualsVector3::describe() const
{
	std::ostringstream ss;
	ss << "equals approximately " << mV;
	return ss.str();
}

bool EqualsQuaternion::match(const util::Quaternion& q) const
{
	return q[0] == Approx(mQ[0]).epsilon(mEpsilon).margin(mMargin)
			&& q[1] == Approx(mQ[1]).epsilon(mEpsilon).margin(mMargin)
			&& q[2] == Approx(mQ[2]).epsilon(mEpsilon).margin(mMargin)
			&& q[3] == Approx(mQ[3]).epsilon(mEpsilon).margin(mMargin);
}

std::string EqualsQuaternion::describe() const
{
	std::ostringstream ss;
	ss << "equals approximately " << mQ;
	return ss.str();
}

}
}
