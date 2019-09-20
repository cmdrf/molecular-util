/*	Matchers.cpp
	Copyright 2017 Fabian Herb

	This file is part of Molecular Engine.
*/

#include "Matchers.h"

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

bool EqualsQuaternion::match(const Quaternion& q) const
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




