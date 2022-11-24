#pragma once
#ifndef RATIONAL_RATIONAL_H_20220309
#define RATIONAL_RATIONAL_H_20220309
#include <iostream>
#include <sstream>
#include <cctype>
class Rational
{
public:
	Rational(const Rational& copy) = default;
	~Rational() = default;
	Rational(int numerator= 0,  int denominator=1);
	Rational& operator= (const Rational& rhs) = default;
bool operator== (const Rational& rhs) const {  return (num == rhs.num && den == rhs.den); }
bool operator!= (const Rational& rhs) { return(!operator==(rhs)); }
bool operator< (const Rational& rhs) 
{ 
	return (num == rhs.num && den > rhs.den); 
}
bool Rational::operator<=(const Rational& rhs)
{
	return (num == rhs.num && den >= rhs.den);
}
bool Rational::operator>(const Rational& rhs)
{
	return (num == rhs.num && den < rhs.den);
}
bool Rational::operator>=(const Rational& rhs)
{
	return (num == rhs.num && den <= rhs.den);
}
Rational operator-()const;
Rational operator+()const;

Rational& operator++ ();
	Rational& operator-- ();

Rational operator++ (int );
	Rational operator-- (int );

	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);
	
	int num = { 0 };
	int den = { 1 };
	int GeneralDenom(int x, int y)
	{
		while(x)
		{ 
		int c = y % x;
		y = x;
		x = c;
		}
		return y;
	}
	void Generalization()
	{
		if (den == 0) {
			throw std::invalid_argument("Nol v znamenatele");
		}
		if (num != 0)
		{
			int a = GeneralDenom(num, den);
			num /= a;
			den /= a;
		}
		else den = 1;
		if (den < 0) {
			num *= -1;
			den *= -1;
		}
	}

	int minus(int z )
	{
		if (z < 0)
		{
			return -1;
		}
		return 1;
	}
	Rational operator+ (const Rational& rhs)const;
	Rational operator- (const Rational& rhs)const;
	Rational operator* (const Rational& rhs)const;
	Rational operator/ (const Rational& rhs)const;

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

	void Setform(int numerator, int denumerator);
private:
	static const char slash{'/'};
};
inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
	return rhs.writeTo(ostrm);
}

inline std::istream& operator >> (std::istream& istrm, Rational& rhs)
{
	return rhs.readFrom(istrm);
}
#endif