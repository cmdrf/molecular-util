/*	TestSphericalHarmonics.cpp
	Copyright 2016-2018 Fabian Herb

	This file is part of Molecular Engine.
*/

#include <catch.hpp>
#include <molecular/util/SphericalHarmonics.h>
#include <cmath>

using namespace molecular::SphericalHarmonics;
using namespace molecular;

TEST_CASE("TestAssociatedLegendrePolynomial")
{
	CHECK(AssociatedLegendrePolynomial(0, 0, 0.1234) == Approx(1));
	CHECK(AssociatedLegendrePolynomial(1, 0, 0.21234) == Approx(0.21234));
	CHECK(AssociatedLegendrePolynomial(1, 1, 0.21234) == Approx(-std::sqrt(1 - 0.21234 * 0.21234)));
	CHECK(AssociatedLegendrePolynomial(2, 0, 0.5) == Approx(0.5 * (3 * 0.25 - 1)));
	CHECK(AssociatedLegendrePolynomial(2, 1, 0.5) == Approx(-1.5 * std::sqrt(0.75)));
	CHECK(AssociatedLegendrePolynomial(2, 2, 0.5) == Approx(2.25));
}

constexpr double TestFactorial(int x)
{
	return x == 0 ? 1.0 : x * TestFactorial(x - 1);
}

TEST_CASE("TestFactorial")
{
	CHECK(Factorial(0) == Approx(TestFactorial(0)));
	CHECK(Factorial(1) == Approx(TestFactorial(1)));
	CHECK(Factorial(2) == Approx(TestFactorial(2)));
	CHECK(Factorial(3) == Approx(TestFactorial(3)));
	CHECK(Factorial(4) == Approx(TestFactorial(4)));
	CHECK(Factorial(5) == Approx(TestFactorial(5)));
	CHECK(Factorial(6) == Approx(TestFactorial(6)));
	CHECK(Factorial(7) == Approx(TestFactorial(7)));
	CHECK(Factorial(8) == Approx(TestFactorial(8)));
	CHECK(Factorial(9) == Approx(TestFactorial(9)));
	CHECK(Factorial(10) == Approx(TestFactorial(10)));
	CHECK(Factorial(11) == Approx(TestFactorial(11)));
	CHECK(Factorial(12) == Approx(TestFactorial(12)));
	CHECK(Factorial(13) == Approx(TestFactorial(13)));
	CHECK(Factorial(14) == Approx(TestFactorial(14)));
	CHECK(Factorial(15) == Approx(TestFactorial(15)));
	CHECK(Factorial(16) == Approx(TestFactorial(16)));
	CHECK(Factorial(17) == Approx(TestFactorial(17)));
	CHECK(Factorial(18) == Approx(TestFactorial(18)));
	CHECK(Factorial(19) == Approx(TestFactorial(19)));
}

TEST_CASE("TestSphericalHarmonics")
{
	// Function and values taken from Gritty Details paper
	auto light = [](double theta, double phi)
	{
		return std::max(0.0, 5.0 * std::cos(theta) - 4.0) + std::max(0.0, -4.0 * std::sin(theta - Math::kPi_d) * std::cos(phi - 2.5) - 3.0);
	};

	auto samples = SetupSphericalSamples<4>(100);
	Vector<16, double> coeffs = SphericalHarmonics::ProjectPolarFunction<4>(light, samples);
	CHECK(coeffs[0] == Approx(0.39925).margin(0.001));
	CHECK(coeffs[1] == Approx(-0.21075).margin(0.001));
	CHECK(coeffs[2] == Approx(0.28687).margin(0.001));
	CHECK(coeffs[3] == Approx(0.28277).margin(0.001));
	CHECK(coeffs[4] == Approx(-0.31530).margin(0.001));
	CHECK(coeffs[5] == Approx(-0.00040).margin(0.001));
	CHECK(coeffs[6] == Approx(0.13159).margin(0.001));
	CHECK(coeffs[7] == Approx(0.00098).margin(0.001));
	CHECK(coeffs[8] == Approx(0.09359).margin(0.001)); // Paper: -0.09359
//	CHECK(coeffs[9] == Approx(-0.00072));
//	CHECK(coeffs[10] == Approx(0.12290));
	CHECK(coeffs[12] == Approx(0.30458).margin(0.002));
	CHECK(coeffs[13] == Approx(-0.16427).margin(0.002));
	CHECK(coeffs[14] == Approx(-0.00062).margin(0.001));
	CHECK(coeffs[15] == Approx(-0.09126).margin(0.001));
}

TEST_CASE("TestSphericalHarmonics2")
{
	auto samples = SphericalHarmonics::SetupSphericalSamples<3>(180);
	Vector<9, double> coeffs;
	for(auto& sample: samples)
		coeffs += sample.coeff;
	coeffs *= 4.0 * Math::kPi_d / samples.size();
	CHECK(coeffs[0] == Approx(2.0 * std::sqrt(Math::kPi_d))); // Stupid SH Tricks
	CHECK(coeffs[1] == Approx(0).margin(0.0005));
	CHECK(coeffs[2] == Approx(0).margin(0.0005));
	CHECK(coeffs[3] == Approx(0).margin(0.0005));
	CHECK(coeffs[4] == Approx(0).margin(0.0005));
	CHECK(coeffs[5] == Approx(0).margin(0.0005));
	CHECK(coeffs[6] == Approx(0).margin(0.0005));
	CHECK(coeffs[7] == Approx(0).margin(0.0005));
	CHECK(coeffs[8] == Approx(0).margin(0.0005));
}
