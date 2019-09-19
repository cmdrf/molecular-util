/*	AxisAlignedBox.h

MIT License

Copyright (c) 2018 Fabian Herb

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

#ifndef MOLECULAR_AXISALIGNEDBOX_H
#define MOLECULAR_AXISALIGNEDBOX_H

#undef min
#undef max

#include "Vector3.h"
#include <cassert>
#include <limits>
#include <algorithm>
#include <stdexcept>

namespace molecular
{
namespace util
{

/// Axis aligned (bounding) box (AABB)
class AxisAlignedBox
{
public:
	struct LineIntersectionResult
	{
		/// Fraction of the line between start and end where the box is hit
		/** A negative value means no hit. */
		float fraction;
		int hitAxis;

		/// -1 if the box was hit on the minimum of hitAxis, 1 otherwise
		int hitDirection;
	};

	inline AxisAlignedBox();
	inline AxisAlignedBox(const Vector3& min, const Vector3& max);
	inline AxisAlignedBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

	inline bool Contains(const Vector3& point) const;

	/// Calculates volume of this box
	inline double Volume() const {return (mMax[0] - mMin[0]) * (mMax[1] - mMin[1]) * (mMax[2] - mMin[2]);}

	/// Returns true if the second box is fully contained inside this box
	inline bool Encloses(const AxisAlignedBox& box) const;

	/// Returns true if the two boxes intersect
	inline bool Overlaps(const AxisAlignedBox& box) const;

	/// Calculates the volume of the intersection of the two boxes
	inline double Overlap(const AxisAlignedBox& box) const;
	inline Vector3 Center() const {return (mMax - mMin) * 0.5 + mMin;}

	/// Extends this box so it encloses the other
	inline void Stretch(const AxisAlignedBox& box);

	inline void Stretch(const Vector3& vec);

	inline bool IsNull() const {return (mMax[0] < mMin[0] || mMax[1] < mMin[1] || mMax[2] < mMin[2]);}

	const Vector3& GetMin() const {return mMin;}
	const Vector3& GetMax() const {return mMax;}
	float GetMin(int i) const {return mMin[i];}
	float GetMax(int i) const {return mMax[i];}
	float GetSize(int i) const {return mMax[i] - mMin[i];}
	Vector3 GetSize() const {return mMax - mMin;}
	Vector3 GetCenter() const {return mMin + (mMax - mMin) * 0.5;}

	LineIntersectionResult LineIntersection(const Vector3& lineStart, const Vector3& lineEnd);

	static const AxisAlignedBox kDefault;

private:
	Vector3 mMin, mMax;
};

std::ostream& operator<<(std::ostream& o, const AxisAlignedBox& box);

inline AxisAlignedBox::AxisAlignedBox() :
	mMin(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()),
	mMax(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())
{

}

inline AxisAlignedBox::AxisAlignedBox(const Vector3& min, const Vector3& max) :
	mMin(min),
	mMax(max)
{
	if(min[0] > max[0] || min[1] > max[1] || min[2] > max[2])
		throw std::runtime_error("AxisAlignedBox: max must be greater than min");
}

inline AxisAlignedBox::AxisAlignedBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) :
	mMin(minX, minY, minZ),
	mMax(maxX, maxY, maxZ)
{
	if(minX > maxX || minY > maxY || minZ > maxZ)
		throw std::runtime_error("AxisAlignedBox: max must be greater than min");
}


inline bool AxisAlignedBox::Contains(const Vector3& point) const
{
	if(point[0] < mMin[0] || point[1] < mMin[1] || point[2] < mMin[2] ||
		point[0] > mMax[0] || point[1] > mMax[1] || point[2] > mMax[2])
		return false;
	return true;
}


inline bool AxisAlignedBox::Encloses(const AxisAlignedBox& box) const
{
	if(box.mMax[0] > mMax[0] || box.mMax[1] > mMax[1] || box.mMax[2] > mMax[2] ||
		box.mMin[0] < mMin[0] || box.mMin[1] < mMin[1] || box.mMin[2] < mMin[2])
		return false;
	return true;
}

inline bool AxisAlignedBox::Overlaps(const AxisAlignedBox& box) const
{
	if(box.mMin[0] > mMax[0] || box.mMax[0] < mMin[0] ||
		box.mMin[1] > mMax[1] || box.mMax[1] < mMin[1] ||
		box.mMin[2] > mMax[2] || box.mMax[2] < mMin[2])
		return false;
	return true;
}

inline double AxisAlignedBox::Overlap(const AxisAlignedBox& box) const
{
	if(!Overlaps(box))
		return 0.0;
	double d0 = std::min(box.GetMax(0), mMax[0]) - std::max(box.GetMin(0), mMin[0]);
	double d1 = std::min(box.GetMax(1), mMax[1]) - std::max(box.GetMin(1), mMin[1]);
	double d2 = std::min(box.GetMax(2), mMax[2]) - std::max(box.GetMin(2), mMin[2]);
	return d0 * d1 * d2;
}

inline void AxisAlignedBox::Stretch(const AxisAlignedBox& box)
{
	for(int i = 0; i < 3; ++i)
	{
		if(box.GetMin(i) < mMin[i])
			mMin[i] = box.GetMin(i);

		if(box.GetMax(i) > mMax[i])
			mMax[i] = box.GetMax(i);
	}
}

inline void AxisAlignedBox::Stretch(const Vector3& vec)
{
	for(int i = 0; i < 3; ++i)
	{
		if(vec[i] < mMin[i])
			mMin[i] = vec[i];

		if(vec[i] > mMax[i])
			mMax[i] = vec[i];
	}
}

}
} // namespace molecular

#endif // MOLECULAR_AXISALIGNEDBOX_H
