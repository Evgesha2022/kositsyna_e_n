// authoring
#pragma once
#ifndef COMPLEX_COMPLEX_H_20220309
#define COMPLEX_COMPLEX_H_20220309
#include <iostream>
#include <sstream>



struct Complex
{
	Complex(const Complex& en) = default;
	~Complex() = default;
	static constexpr double eps_2{ 2.0 * std::numeric_limits<double>::epsilon() };
	Complex(double real=0.0, double imaginary=0.0);
	bool operator== (const Complex& rhs) const { return (abs(re - rhs.re) < eps_2) && (abs(im - rhs.im) <  eps_2); }
	bool operator!= (const Complex& rhs) const { return !operator==(rhs); }
	Complex& operator= (const Complex& rhs)= default;
	Complex& operator= (const double rhs) { re = rhs; im = 0.0; return *this; };
	Complex operator-() const { return Complex(-re, -im); }
	Complex operator+() const { return Complex(re, im); }
	Complex& operator+= (const Complex& rhs);
	Complex& operator-= (const Complex& rhs);
	Complex& operator*= (const Complex& rhs);
	Complex& operator/= (const Complex& rhs);
	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

	double re{ 0.0 };
	double im{ 0.0 };
	static const char leftBrace{ '{' };
	static const char separator{ ',' };
	static const char rightBrace{ '}' };
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs)
{
	return rhs.writeTo(ostrm);
}

inline std::istream& operator >> (std::istream& istrm, Complex& rhs)
{
	return rhs.readFrom(istrm);
}
#endif
