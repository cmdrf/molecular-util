/*	Matrix4.h

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

#ifndef MOLECULAR_MATRIX4_H
#define MOLECULAR_MATRIX4_H

#include "Matrix.h"
#include "Matrix3.h"
#include "Vector4.h"

namespace molecular
{
namespace util
{

/// A 4x4 matrix
class Matrix4 : public Matrix<4, 4>
{
public:
	Matrix4()
	{
		*this = Identity();
	}

	Matrix4(const float values[16]) : Matrix<4,4>(values) {}
	Matrix4(const Matrix<4, 4>& mat) : Matrix<4, 4>(mat) {}
	inline Matrix4(const Matrix<3, 4>& mat);
	inline Matrix4(const Matrix<3, 3>& mat);

	/** Column-major ordering. */
	inline Matrix4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33);

	inline Vector4 operator*(const Vector4& v) const;
	using Matrix<4,4>::operator*;

	inline Vector3 GetTranslation() const;
	inline Matrix3 GetUpperLeft3x3() const;
	Vector4 GetRow(int row) const {return Vector4(m[row]);}

	static inline Matrix4 ProjectionPerspective(float fieldOfView, float aspectRatio, float near, float far);
	static inline Matrix4 ProjectionOrthographic(float width, float height, float nearPlane, float farPlane);

	inline static Matrix4 RotationX(float a);
	inline static Matrix4 RotationY(float a);
	inline static Matrix4 RotationZ(float a);
	inline static Matrix4 Translation(float x, float y, float z);
	inline static Matrix4 Translation(const Vector3& xyz) {return Translation(xyz[0], xyz[1], xyz[2]);}
	static inline Matrix4 Scale(float x, float y, float z);
	static inline Matrix4 Scale(float xyz) {return Scale(xyz, xyz, xyz);}
};

inline Matrix4::Matrix4(const Matrix<3, 4>& mat)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 4; c++)
			m[r][c] = mat(r, c);
	}
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

inline Matrix4::Matrix4(const Matrix<3, 3>& mat)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
			m[r][c] = mat(r, c);
	}

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

inline Matrix4::Matrix4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33)
{
	m[0][0] = m00;
	m[1][0] = m10;
	m[2][0] = m20;
	m[3][0] = m30;
	m[0][1] = m01;
	m[1][1] = m11;
	m[2][1] = m21;
	m[3][1] = m31;
	m[0][2] = m02;
	m[1][2] = m12;
	m[2][2] = m22;
	m[3][2] = m32;
	m[0][3] = m03;
	m[1][3] = m13;
	m[2][3] = m23;
	m[3][3] = m33;
}

inline Vector4 Matrix4::operator*(const Vector4& v) const
{
	Matrix<4, 1> in(v);
	Matrix<4, 1> out = *this * in;
	return Vector4(out(0, 0), out(1, 0), out(2, 0), out(3, 0));
}

inline Vector3 Matrix4::GetTranslation() const
{
	return Vector3(m[0][3], m[1][3], m[2][3]);
}

inline Matrix3 Matrix4::GetUpperLeft3x3() const
{
	return Matrix3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}

inline Matrix4 Matrix4::ProjectionPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix4 outMatrix = Identity();
	float f = 1.0f / std::tan(fieldOfView / 2.0f);
	outMatrix(0, 0) = f / aspectRatio;
	outMatrix(1, 1) = f;
	outMatrix(2, 2) = (farPlane + nearPlane) / (nearPlane - farPlane);
	outMatrix(2, 3) = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
	outMatrix(3, 2) = -1.0f;
	outMatrix(3, 3) = 0.0f;
	return outMatrix;
}

inline Matrix4 Matrix4::ProjectionOrthographic(float width, float height, float nearPlane, float farPlane)
{
	Matrix4 outMatrix = Identity();
	outMatrix(0, 0) = 2.0f / width;
	outMatrix(1, 1) = 2.0f / height;
	outMatrix(2, 2) = -2.0f / (farPlane - nearPlane);
	return outMatrix;
}

inline Matrix4 Matrix4::RotationX(float a)
{
	Matrix4 m;
	m(0, 0) = 1.0f;
	m(0, 1) = 0.0f;
	m(0, 2) = 0.0f;
	m(0, 3) = 0.0f;
	m(1, 0) = 0.0f;
	m(1, 1) = std::cos(a);
	m(1, 2) = -std::sin(a);
	m(1, 3) = 0.0f;
	m(2, 0) = 0.0f;
	m(2, 1) = std::sin(a);
	m(2, 2) = std::cos(a);
	m(2, 3) = 0.0f;
	m(3, 0) = 0.0f;
	m(3, 1) = 0.0f;
	m(3, 2) = 0.0f;
	m(3, 3) = 1.0f;
	return m;
}

inline Matrix4 Matrix4::RotationY(float a)
{
	Matrix4 m;
	m(0, 0) = std::cos(a);
	m(0, 1) = 0.0f;
	m(0, 2) = std::sin(a);
	m(0, 3) = 0.0f;
	m(1, 0) = 0.0f;
	m(1, 1) = 1.0f;
	m(1, 2) = 0.0f;
	m(1, 3) = 0.0f;
	m(2, 0) = -std::sin(a);
	m(2, 1) = 0.0f;
	m(2, 2) = std::cos(a);
	m(2, 3) = 0.0f;
	m(3, 0) = 0.0f;
	m(3, 1) = 0.0f;
	m(3, 2) = 0.0f;
	m(3, 3) = 1.0f;
	return m;
}

inline Matrix4 Matrix4::RotationZ(float a)
{
	Matrix4 m;
	m(0, 0) = std::cos(a);
	m(0, 1) = -std::sin(a);
	m(0, 2) = 0.0f;
	m(0, 3) = 0.0f;
	m(1, 0) = std::sin(a);
	m(1, 1) = std::cos(a);
	m(1, 2) = 0.0f;
	m(1, 3) = 0.0f;
	m(2, 0) = 0.0f;
	m(2, 1) = 0.0f;
	m(2, 2) = 1.0f;
	m(2, 3) = 0.0f;
	m(3, 0) = 0.0f;
	m(3, 1) = 0.0f;
	m(3, 2) = 0.0f;
	m(3, 3) = 1.0f;
	return m;
}

inline Matrix4 Matrix4::Translation(float x, float y, float z)
{
	Matrix4 m;
	m(0, 0) = 1.0f; m(0, 1) = 0.0f; m(0, 2) = 0.0f; m(0, 3) = x;
	m(1, 0) = 0.0f; m(1, 1) = 1.0f; m(1, 2) = 0.0f; m(1, 3) = y;
	m(2, 0) = 0.0f; m(2, 1) = 0.0f; m(2, 2) = 1.0f; m(2, 3) = z;
	m(3, 0) = 0.0f; m(3, 1) = 0.0f; m(3, 2) = 0.0f; m(3, 3) = 1.0f;
	return m;
}

inline Matrix4 Matrix4::Scale(float x, float y, float z)
{
	Matrix4 out = Identity();
	out(0, 0) = x;
	out(1, 1) = y;
	out(2, 2) = z;
	return out;
}

} // namespace molecular
}

#endif // MOLECULAR_MATRIX4_H
