/*	Quaternion.cpp

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

#include "Quaternion.h"

namespace molecular
{
namespace util
{

const Quaternion Quaternion::kIdentity = Quaternion(1,0,0,0);

// http://euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
Quaternion Quaternion::FromAngles(float heading, float attitude, float bank)
{
	const float c1 = std::cos(heading * 0.5f);
	const float s1 = std::sin(heading * 0.5f);
	const float c2 = std::cos(attitude * 0.5f);
	const float s2 = std::sin(attitude * 0.5f);
	const float c3 = std::cos(bank * 0.5f);
	const float s3 = std::sin(bank * 0.5f);
	const float c1c2 = c1 * c2;
	const float s1s2 = s1 * s2;
	const float w = c1c2 * c3 - s1s2 * s3;
	const float x = c1c2 * s3 + s1s2 * c3;
	const float y = s1 * c2 * c3 + c1 * s2 * s3;
	const float z = c1 * s2 * c3 - s1 * c2 * s3;
	return Quaternion(w, x, y, z);
}

Quaternion Quaternion::Slerp(const Quaternion& p, const Quaternion& q, float beta)
{
	const float cosHalfTheta = p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3];
	if(std::abs(cosHalfTheta) >= 1.0f)// If p == q or p == -q then theta = 0 and we can return p
		return p;
	const float theta = std::acos(cosHalfTheta);
	float sinTheta = std::sin(theta);
	float wp = std::sin((1.0f - beta) * theta) / sinTheta;
	float wq = std::sin(beta * theta) / sinTheta;
	return p * wp + q * wq;
}

}
}
