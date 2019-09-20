/*	Matchers.h
	Copyright 2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#ifndef MOLECULAR_MATCHERS_H
#define MOLECULAR_MATCHERS_H

#include <molecular/util/Vector3.h>
#include <molecular/util/Quaternion.h>
#include <molecular/util/Matrix.h>
#include <catch.hpp>

using namespace molecular;

class EqualsVector2 : public Catch::MatcherBase<Vector2>
{
public:
	EqualsVector2(const Vector2& v, double epsilon, double margin) : mV(v), mEpsilon(epsilon), mMargin(margin)
	{}

	/// Performs the test for this matcher
	bool match(const Vector2& v) const override;

	std::string describe() const override;

private:
	Vector2 mV;
	double mEpsilon;
	double mMargin;
};

// The builder function
inline EqualsVector2 EqualsApprox(const Vector2& v, double epsilon = 0.00001, double margin = 0.0)
{
	return EqualsVector2(v, epsilon, margin);
}

class EqualsVector3 : public Catch::MatcherBase<Vector3>
{
public:
	EqualsVector3(const Vector3& v, double epsilon, double margin) : mV(v), mEpsilon(epsilon), mMargin(margin)
	{}

	/// Performs the test for this matcher
	bool match(const Vector3& v) const override;

	std::string describe() const override;

private:
	Vector3 mV;
	double mEpsilon;
	double mMargin;
};

// The builder function
inline EqualsVector3 EqualsApprox(const Vector3& v, double epsilon = 0.00001, double margin = 0.0)
{
	return EqualsVector3(v, epsilon, margin);
}

class EqualsQuaternion : public Catch::MatcherBase<Quaternion>
{
public:
	EqualsQuaternion(const Quaternion& q, double epsilon, double margin) : mQ(q), mEpsilon(epsilon), mMargin(margin)
	{}

	/// Performs the test for this matcher
	bool match(const Quaternion& q) const override;

	std::string describe() const override;

private:
	Quaternion mQ;
	double mEpsilon;
	double mMargin;
};

// The builder function
inline EqualsQuaternion EqualsApprox(const Quaternion& q, double epsilon = 0.00001, double margin = 0.0)
{
	return EqualsQuaternion(q, epsilon, margin);
}

template<int rows, int cols, typename T>
class EqualsMatrix : public Catch::MatcherBase<Matrix<rows, cols, T>>
{
public:
	EqualsMatrix(const Matrix<rows, cols, T>& m, double epsilon) : mM(m), mEpsilon(epsilon)
	{}

	/// Performs the test for this matcher
	bool match(const Matrix<rows, cols, T>& m) const override
	{
		for(int i = 0; i < rows; ++i)
			for(int j = 0; j < cols; ++j)
				if(m(i, j) != Approx(mM(i, j)).epsilon(mEpsilon))
					return false;
		return true;
	}

	std::string describe() const override
	{
		std::ostringstream ss;
		ss << "equals approximately " << mM;
		return ss.str();
	}

private:
	Matrix<rows, cols, T> mM;
	double mEpsilon;
};

// The builder function
template<int rows, int cols, typename T>
inline EqualsMatrix<rows, cols, T> EqualsApprox(const Matrix<rows, cols, T>& m, double epsilon = 0.00001)
{
	return EqualsMatrix<rows, cols, T>(m, epsilon);
}

#endif // MATCHERS_H
