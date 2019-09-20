/*	AxisAlignedBox.cpp

MIT License

Copyright (c) 2018-2019 Fabian Herb

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

#include "AxisAlignedBox.h"

namespace molecular
{
namespace util
{

const AxisAlignedBox AxisAlignedBox::kDefault = AxisAlignedBox();

AxisAlignedBox::LineIntersectionResult AxisAlignedBox::LineIntersection(const Vector3& lineStart, const Vector3& lineEnd)
{
	float fractionLow = 0.0f;
	float fractionHigh = 1.0f;
	LineIntersectionResult result = {-1, 0, 0};

	for(int d = 0; d < 3; ++d)
	{
		float currentFractionLow = (mMin[d] - lineStart[d]) / (lineEnd[d] - lineStart[d]);
		float currentFractionHigh = (mMax[d] - lineStart[d]) / (lineEnd[d] - lineStart[d]);

		if (currentFractionHigh < currentFractionLow)
			std::swap(currentFractionHigh, currentFractionLow);

		if (currentFractionHigh < fractionLow || currentFractionLow > fractionHigh)
			return result;

		if(fractionLow < currentFractionLow)
		{
			fractionLow = currentFractionLow;
			result.hitAxis = d;
			result.hitDirection = lineStart[d] < lineEnd[d] ? -1 : 1;
		}

		if(fractionHigh > currentFractionHigh)
		{
			fractionHigh = currentFractionHigh;
		}

		if(fractionLow > fractionHigh)
			return result;
	}

	result.fraction = fractionLow;
	return result;
}

}
} // molecular

std::ostream& operator<<(std::ostream& o, const molecular::util::AxisAlignedBox& box)
{
	o << '(' << box.GetMin() << ", " << box.GetMax() << ')';
	return o;
}
