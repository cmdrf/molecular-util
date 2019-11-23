/*	Vector3.h

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

#ifndef MOLECULAR_VECTOR3_H
#define MOLECULAR_VECTOR3_H

#include "Vector.h"

namespace molecular
{
namespace util
{

/// Generic vector with 3 elements
template<typename T>
class Vector3T : public VectorTmpl<3, Vector3T<T>, T>
{
public:
	using Super = VectorTmpl<3, Vector3T<T>, T>;

	inline Vector3T() = default;
	inline Vector3T(const T x, const T y, const T z);
	inline Vector3T(const T inV[3]);
	inline Vector3T(const Vector2& xy, float z);
	
	inline T X() const { return this->v[0];}
	inline T Y() const { return this->v[1];}
	inline T Z() const { return this->v[2];}
	inline void Get(T* out) const {out[0] = this->v[0]; out[1] = this->v[1]; out[2] = this->v[2];}

	inline Vector2 Xy() const {return Vector2(this->v[0], this->v[1]);}
		
	inline Vector3T& operator-=(const Vector3T& inV);
	inline Vector3T& operator+=(const Vector3T& inV);

	using Super::operator *;

	Vector3T	CrossProduct(const Vector3T& inV) const;
	T DotProduct(const Vector3T& inV) const
	{
		return this->v[0]*inV[0] + this->v[1]*inV[1] + this->v[2]*inV[2];
	}

	inline void	SetLength(const T length);
	T Distance(const Vector3T& inV) const
	{
		return std::sqrt(sqr(this->v[0]-inV.v[0])+sqr(this->v[1]-inV.v[1])+sqr(this->v[2]-inV.v[2]));
	}

	T DistanceSquared(const Vector3T& inV) const
	{
		return sqr(this->v[0]-inV.v[0])+sqr(this->v[1]-inV.v[1])+sqr(this->v[2]-inV.v[2]);
	}

	inline bool	IsAlmostZero(void) const {return (std::abs(this->v[0]) < 0.0001 && std::abs(this->v[1]) < 0.0001 && std::abs(this->v[2]) < 0.0001);}

private:
	static inline T sqr(const T x) {return x*x;}
};

using Vector3 = Vector3T<float>;
using Vector3f = Vector3T<float>;
using Vector3d = Vector3T<double>;

/*****************************************************************************/

template<typename T>
inline Vector3T<T>::Vector3T(const T x, const T y, const T z)
{
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
}

template<typename T>
Vector3T<T>::Vector3T(const T inV[3])
{
	this->v[0] = inV[0];
	this->v[1] = inV[1];
	this->v[2] = inV[2];
}

template<typename T>
Vector3T<T>::Vector3T(const Vector2& xy, float z)
{
	this->v[0] = xy[0];
	this->v[1] = xy[1];
	this->v[2] = z;
}

template<typename T>
Vector3T<T>& Vector3T<T>::operator+=(const Vector3T& inV)
{
	this->v[0] += inV[0];
	this->v[1] += inV[1];
	this->v[2] += inV[2];
	return *this;
}

template<typename T>
Vector3T<T>& Vector3T<T>::operator-=(const Vector3T& inV)
{
	this->v[0] -= inV[0];
	this->v[1] -= inV[1];
	this->v[2] -= inV[2];
	return *this;
}

template<typename T>
Vector3T<T> Vector3T<T>::CrossProduct(const Vector3T& inV) const
{
	return Vector3(	this->v[1] * inV.v[2] - this->v[2] * inV.v[1],
					this->v[2] * inV.v[0] - this->v[0] * inV.v[2],
					this->v[0] * inV.v[1] - this->v[1] * inV.v[0]);
}

template<typename T>
void Vector3T<T>::SetLength(const T length)
{
	T factor = length / this->Length();
	this->v[0] *= factor;
	this->v[1] *= factor;
	this->v[2] *= factor;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vector3T<T>& vec)
{
	stream << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
	return stream;
}

}
} // namespace molecular

#endif

