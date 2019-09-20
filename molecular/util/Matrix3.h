/*	Matrix3.h

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

#ifndef MOLECULAR_MATRIX3_H
#define MOLECULAR_MATRIX3_H

#include "Matrix.h"
#include "Quaternion.h"
#include <cmath>

namespace molecular
{

/// Rotation matrix
/** The following convention is used: Consecutive transformations
	(e.g. A, B, C) have to be multiplied from right to left (C * B * A).
	To transform a Vector3 (which is a column vector), multiply it right
	of the matrix (e.g. x' = A * x). */
class Matrix3 : public Matrix<3, 3>
{
public:
	using Super = Matrix<3, 3>;

	Matrix3()
	{
		SetIdentity();
	}


	Matrix3(ValueType m00, ValueType m01, ValueType m02, ValueType m10, ValueType m11, ValueType m12, ValueType m20, ValueType m21, ValueType m22)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}

	Matrix3(Super s) : Matrix3(s(0, 0), s(0, 1), s(0, 2), s(1, 0), s(1, 1), s(1, 2), s(2, 0), s(2, 1), s(2, 2))
	{}

	Matrix3(const ValueType values[9]) : Matrix<3, 3>(values){}

	Matrix3(const Matrix<3,4>& mat)
	{
		m[0][0] = mat(0, 0); m[0][1] = mat(0, 1); m[0][2] = mat(0, 2);
		m[1][0] = mat(1, 0); m[1][1] = mat(1, 1); m[1][2] = mat(1, 2);
		m[2][0] = mat(2, 0); m[2][1] = mat(2, 1); m[2][2] = mat(2, 2);
	}

	/// Construct a rotation matrix out of a quaternion
	Matrix3(const Quaternion& quaternion)
	{
		ValueType xx = quaternion.X() * quaternion.X();
		ValueType xy = quaternion.X() * quaternion.Y();
		ValueType xz = quaternion.X() * quaternion.Z();
		ValueType xw = quaternion.X() * quaternion.W();
		ValueType yy = quaternion.Y() * quaternion.Y();
		ValueType yz = quaternion.Y() * quaternion.Z();
		ValueType yw = quaternion.Y() * quaternion.W();
		ValueType zz = quaternion.Z() * quaternion.Z();
		ValueType zw = quaternion.Z() * quaternion.W();
		m[0][0] = 1 - 2 * ( yy + zz );
		m[0][1] =     2 * ( xy - zw );
		m[0][2] =     2 * ( xz + yw );
		m[1][0] =     2 * ( xy + zw );
		m[1][1] = 1 - 2 * ( xx + zz );
		m[1][2] =     2 * ( yz - xw );
		m[2][0] =     2 * ( xz - yw );
		m[2][1] =     2 * ( yz + xw );
		m[2][2] = 1 - 2 * ( xx + yy );
	}

	/// Construct matrix out of three basis vectors
	Matrix3(const Vector3& xBasis, const Vector3& yBasis, const Vector3& zBasis)
	{
		for(int i = 0; i < 3; ++i)
		{
			m[i][0] = xBasis[i];
			m[i][1] = yBasis[i];
			m[i][2] = zBasis[i];
		}
	}

	/// Matrix-vector multiplication
	inline Vector3 operator* (const Vector3& v) const
	{
		ValueType x = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
		ValueType y = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
		ValueType z = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];
		return Vector3(x, y, z);
	}

	using Super::operator*;

	/// Convert to Quaternion
	/** Only works if this matrix represents pure rotation. See
		http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
		*/
	Quaternion ToQuaternion() const
	{
		ValueType trace = m[0][0] + m[1][1] + m[2][2];
		ValueType w, x, y, z;
		if( trace > 0 )
		{
			float s = 0.5f / std::sqrt(trace + 1.0f);
			w = 0.25f / s;
			x = ( m[2][1] - m[1][2] ) * s;
			y = ( m[0][2] - m[2][0] ) * s;
			z = ( m[1][0] - m[0][1] ) * s;
		}
		else
		{
			if(m[0][0] > m[1][1] && m[0][0] > m[2][2])
			{
				float s = 2.0f * std::sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]);
				w = (m[2][1] - m[1][2] ) / s;
				x = 0.25f * s;
				y = (m[0][1] + m[1][0] ) / s;
				z = (m[0][2] + m[2][0] ) / s;
			}
			else if(m[1][1] > m[2][2])
			{
				float s = 2.0f * std::sqrt( 1.0f + m[1][1] - m[0][0] - m[2][2]);
				w = (m[0][2] - m[2][0] ) / s;
				x = (m[0][1] + m[1][0] ) / s;
				y = 0.25f * s;
				z = (m[1][2] + m[2][1] ) / s;
			}
			else
			{
				ValueType s = 2.0f * std::sqrt( 1.0f + m[2][2] - m[0][0] - m[1][1] );
				w = (m[1][0] - m[0][1] ) / s;
				x = (m[0][2] + m[2][0] ) / s;
				y = (m[1][2] + m[2][1] ) / s;
				z = 0.25f * s;
			}
		}
		return Quaternion(w, x, y, z);
	}

	/// Get rotation without scaling
	/** Works for uniform scaling only! */
	Matrix3 GetRotation() const
	{
		Vector3 col0(m[0][0], m[1][0], m[2][0]);
		Vector3 col1(m[0][1], m[1][1], m[2][1]);
		Vector3 col2(m[0][2], m[1][2], m[2][2]);
		col0.SetLength(1.0f);
		col1.SetLength(1.0f);
		col2.SetLength(1.0f);
		return Matrix3(col0, col1, col2);
	}

	ValueType GetScale() const
	{
		return (*this * GetRotation().Inverse()).Trace() / 3;
	}

	ValueType Determinant() const
	{
		return	m[0][0] * m[1][1] * m[2][2] +
				m[0][1] * m[1][2] * m[2][0] +
				m[0][2] * m[1][0] * m[2][1] -
				m[0][2] * m[1][1] * m[2][0] -
				m[0][1] * m[1][0] * m[2][2] -
				m[0][0] * m[1][2] * m[2][1];
	}

	static Matrix3 LookAtX(const Vector3& at, const Vector3& up = Vector3(0,1,0))
	{
		// Calculate vector that is perpendicular to "at" and "up":
		Vector3 right = at.CrossProduct(up);

		// Calculate vector that is perpendicular to "at" and "right":
		Vector3 correctedUp = right.CrossProduct(at);

		// Normalise:
		right.SetLength(1.0);
		correctedUp.SetLength(1.0);

		// Use as basis vectors:
		return Matrix3(at.Normalized(), correctedUp, right);
	}

	static Matrix3 LookAtZ(const Vector3& at, const Vector3& up = Vector3(0,1,0))
	{
		// Calculate vector that is perpendicular to "at" and "up":
		Vector3 right = up.CrossProduct(at);

		// Calculate vector that is perpendicular to "at" and "right":
		Vector3 correctedUp = at.CrossProduct(right);

		// Normalise:
		right.SetLength(1.0);
		correctedUp.SetLength(1.0);

		// Use as basis vectors:
		return Matrix3(right, correctedUp, at.Normalized());
	}


	static Matrix3 RotationX(float a)
	{
		return Matrix3(
			1, 0, 0,
			0, std::cos(a),  -std::sin(a),
			0, std::sin(a), std::cos(a));
	}

	static Matrix3 RotationY(float a)
	{
		return Matrix3(
			std::cos(a), 0, std::sin(a),
			0, 1, 0,
			-std::sin(a), 0, std::cos(a));
	}

	static Matrix3 RotationZ(float a)
	{
		return Matrix3(
			std::cos(a), -std::sin(a), 0,
			std::sin(a), std::cos(a), 0,
			0, 0, 1);
	}

	static Matrix3 Scale(ValueType s)
	{
		return Matrix3(s, 0, 0, 0, s, 0, 0, 0, s);
	}

	static Matrix3 Scale(ValueType sx, ValueType sy, ValueType sz)
	{
		return Matrix3(sx, 0, 0, 0, sy, 0, 0, 0, sz);
	}
};

}

#endif // MOLECULAR_MATRIX3_H
