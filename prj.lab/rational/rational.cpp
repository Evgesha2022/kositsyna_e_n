#include <iostream>
#include <sstream>
#include <cctype>
#include <rational/rational.h>

Rational::Rational(const int numerator, const int denominator) : num(numerator*minus(denominator)), den(denominator* minus(denominator))
{
	Generalization();
	return;
}
Rational Rational:: operator-()const { return Rational(-num, den); }

Rational Rational:: operator+()const { return *this; }

Rational& Rational:: operator++()
{
	num += den;
	Generalization();
	return *this;
}
Rational& Rational:: operator--()
{
	num -= den;
	Generalization();
	return *this;
}
Rational Rational:: operator++(int )
{
	Rational copy{ *this };
	operator++();
	return copy;
}
Rational Rational:: operator--(int)
{
	Rational copy{ *this };
	operator--();
	return copy;
}

Rational& Rational::operator+=(const Rational& rhs)
{
	num = (num * rhs.den + rhs.num * den);
	den = rhs.den * den;
	Generalization();
	return ( * this);
}
Rational& Rational::operator-=(const Rational& rhs)
{
	return *this += -rhs;
}
Rational& Rational::operator*=(const Rational& rhs)
{
	num *=rhs.num;
	den *= rhs.den;
	Generalization();
	return *this;
}
Rational& Rational::operator/=(const Rational& rhs)
{
	Rational copy_rhs(rhs.den, rhs.num);
	return *this *= copy_rhs;
}


Rational Rational:: operator+(const Rational& rhs) const
{
	Rational comp(*this);
	return comp += rhs;
}
Rational Rational::operator-(const Rational& rhs) const
{
	Rational comp(*this);
	return comp -= rhs;
}
Rational Rational:: operator*(const Rational& rhs) const
{
	Rational copy{ *this };
	return copy*=rhs;
}
Rational Rational :: operator/(const Rational& rhs)const
{
	Rational comp(*this);
	return comp/=rhs;
}


void Rational::Setform(int numerator, int denumerator)
{
	num = numerator;
	den = denumerator;
	Generalization();
	return;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
	ostrm << num << slash << den;
	return ostrm;
}
std::istream& Rational::readFrom(std::istream& istrm)
{
	int numerator(0);
	int denominator(0);
	char separator(0);
	istrm >> numerator;
	istrm.get(separator);
	if (!std::isdigit(istrm.peek()))
	{
		istrm >> denominator;
		istrm.setstate(std::ios_base::failbit);
	}
	else
	{
		istrm >> denominator;
	}
	if(!istrm.bad())
	{
		if (separator == slash)
		{
			Setform(numerator, denominator);

		}
		else 
	{
		istrm.setstate(std::ios_base::failbit);
	}
	}
	
	return istrm;
}