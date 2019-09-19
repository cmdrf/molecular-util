/*	Quaternion.h
	Copyright 2008-2016 Fabian Herb

	This file is part of Molecular Engine.
*/

#ifndef QUATERNION_H
#define QUATERNION_H

#include <molecular/util/Types.h>
#include <molecular/util/Vector3.h>
#include <cmath>

using molecular::Vector3;

/// 4D quaternion class for storing rotation values
class Quaternion
{
public:
	using Real = float;

	/// Default constructor
	/** Does not initialize the quaternion to identity! */
	Quaternion() = default;

	constexpr Quaternion(const Real w, const Real x, const Real y, const Real z);
	constexpr Quaternion(const Real inQ[4]);

	/// Create a quaternion out of W and a vector
	inline Quaternion(float w, const Vector3& vec) {q[0] = w; q[1] = vec.X(); q[2] = vec.Y(); q[3] = vec.Z();}

//	inline Quaternion(const Vector3& vec, const Quaternion& qua);

//	inline Real	operator[](const short	n)	const		{ return q[n];	}
	inline operator Real*() {return q;} ///< Conversion operator
	inline operator const Real*() const {return q;} ///< Conversion operator
	inline Quaternion operator*(const Quaternion& inQ) const;
	inline Quaternion operator*(const Real r) const {return Quaternion(r*W(), r*X(), r*Y(), r*Z());}
	inline Quaternion operator/(const Real r) const {return Quaternion(q[0]/r, q[1]/r, q[2]/r, q[3]/r);}
	inline void operator*=(const Real r) {q[0] *= r; q[1] *= r; q[2] *= r; q[3] *= r;}
	inline Quaternion operator+(const Quaternion& inQ) const {return Quaternion(W()+inQ.W(), X()+inQ.X(), Y()+inQ.Y(), Z()+inQ.Z());}
	inline void operator+=(const Quaternion& inQ) {q[0] += inQ.q[0]; q[1] += inQ.q[1]; q[2] += inQ.q[2]; q[3] += inQ.q[3];}

	static inline Quaternion FromAngles(float x, float y);
	static Quaternion FromAngles(float heading, float attitude, float bank);
	static inline Quaternion FromAxisAndAngle(const Vector3& axis, float angle);
	static inline Quaternion RotationX(float angle);
	static inline Quaternion RotationY(float angle);
	static inline Quaternion RotationZ(float angle);

	/// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& p, const Quaternion& q, float beta);

	/// "Length" of the quaternion
	inline Real Norm() const {return std::sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);}

	/// Scale quaternion so that the norm is 1
	inline void Normalise() {float l = 1.0f / Norm(); q[0] *= l; q[1] *= l; q[2] *= l; q[3] *= l;}
	Quaternion Normalized() const {float l = 1.0f / Norm(); return Quaternion(q[0] * l, q[1] * l, q[2] * l, q[3] * l);}

	/// Conjugate of the quaternion
	/** For normalised quaternions (like most rotation quaternions), this is
		equal to the inverse, but calculation is faster.
		@see Inverse() */
	inline Quaternion Conjugate() const {return Quaternion(q[0], -q[1], -q[2], -q[3]);}

	/** The inverse of a quaternion represents the opposite rotation (like an
		inverse matrix). For quaternions known to be normalised consider using
		Conjugate() instead, since it yields the same results but calculation
		is faster.
		@see Conjugate() */
	inline Quaternion Inverse() const {return Conjugate() / Norm();}

	inline Real W() const {return q[0];}
	inline Real X() const {return q[1];}
	inline Real Y() const {return q[2];}
	inline Real Z() const {return q[3];}

	/// Identity constant
	static const Quaternion kIdentity;

	Real q[4]; ///< wxyz
};

inline Quaternion operator* (const Quaternion::Real r, const Quaternion& q)
{
	return Quaternion(r*q.W(), r*q.X(), r* q.Y(), r*q.Z());
}

constexpr Quaternion::Quaternion(const Real w, const Real x, const Real y, const Real z) :
	q{w, x, y, z}
{}

constexpr Quaternion::Quaternion(const Real inQ[4]) :
	q{inQ[0], inQ[1], inQ[2], inQ[3]}
{}

/*
inline Quaternion::Quaternion(const Vector3& vec, const Quaternion& qua)
{
	q[0] = 0.5 * (-vec.X()*qua.X() - vec.Y()*qua.Y() - vec.Z()*qua.Z());
	q[1] = 0.5 * ( vec.X()*qua.W() + vec.Y()*qua.Z() - vec.Z()*qua.Y());
	q[2] = 0.5 * (-vec.X()*qua.Z() + vec.Y()*qua.W() + vec.Z()*qua.X());
	q[3] = 0.5 * ( vec.X()*qua.Y() - vec.Y()*qua.X() + vec.Z()*qua.W());
}
*/

inline Quaternion Quaternion::operator*(const Quaternion& inQ) const
{
	float w = W() * inQ.W() - X() * inQ.X() - Y() * inQ.Y() - Z() * inQ.Z();
	float x = W() * inQ.X() + X() * inQ.W() + Y() * inQ.Z() - Z() * inQ.Y();
	float y = W() * inQ.Y() + Y() * inQ.W() + Z() * inQ.X() - X() * inQ.Z();
	float z = W() * inQ.Z() + Z() * inQ.W() + X() * inQ.Y() - Y() * inQ.X();
	return Quaternion(w, x, y, z);
}


inline Quaternion Quaternion::FromAngles(float x, float y)
{
	float sx = std::sin(x * 0.5f);
	float cx = std::cos(x * 0.5f);
	float sy = std::sin(y * 0.5f);
	float cy = std::cos(y * 0.5f);
	return Quaternion(
		cx * cy,
		sx * cy,
		cx * sy,
		-sx * sy);
}


inline Quaternion Quaternion::FromAxisAndAngle(const Vector3& axis, float angle)
{
	float fSin = std::sin(0.5f * angle);
	return Quaternion(
		std::cos(0.5f * angle),
	    fSin * axis.X(),
	    fSin * axis.Y(),
	    fSin * axis.Z());
}

inline Quaternion Quaternion::RotationX(float angle)
{
	return Quaternion(std::cos(0.5f * angle), std::sin(0.5f * angle), 0, 0);
}

inline Quaternion Quaternion::RotationY(float angle)
{
	return Quaternion(std::cos(0.5f * angle), 0, std::sin(0.5f * angle), 0);
}

inline Quaternion Quaternion::RotationZ(float angle)
{
	return Quaternion(std::cos(0.5f * angle), 0, 0, std::sin(0.5f * angle));
}

inline std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{
	stream << "(" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << ")";
	return stream;
}

#endif
