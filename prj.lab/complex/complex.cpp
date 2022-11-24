
#include <iostream>
#include <sstream>
#include <complex/complex.h>
#include <cctype>

Complex operator+(const Complex &lhs, const Complex &rhs)
{
	Complex lhs_en = lhs;
	return lhs_en+=rhs;
}
Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex lhs_en = lhs;
	return lhs_en -= rhs;
}
Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex lhs_en = lhs;
	return lhs_en *= rhs;
}
Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex lhs_en = lhs;
	return lhs_en /= rhs;
}

Complex:: Complex(const double real, const double imaginary): re(real), im(imaginary) {}

Complex& Complex::operator*=(const Complex& rhs)
{
	Complex lhs= *this;
	re = lhs.re * rhs.re - lhs.im * rhs.im;
	im = lhs.re * rhs.im + lhs.im * rhs.re;
	return ( * this);
}
Complex& Complex::operator/=(const Complex& rhs)
{
	if (rhs == Complex{0.0, 0.0}) throw std::invalid_argument("Nol v znamenatele");
	Complex lhs = *this;
	re = (lhs.re * rhs.re + lhs.im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	im = (lhs.im * rhs.re - lhs.re * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
	return ( * this);
}
Complex& Complex::operator+=(const Complex& rhs)
{
	re += rhs.re;
	im += rhs.im;
	return ( * this);
}
Complex& Complex::operator-=(const Complex& rhs)
{
	return *this += - rhs;
}
std::ostream& Complex::writeTo(std::ostream & ostrm) const
{
	ostrm << leftBrace << re << separator << im << rightBrace;
	return ostrm;
}
std::istream& Complex::readFrom(std::istream & istrm)
{
	char leftBrace(0);
	double real(0.0);
	char comma(0);
	double imaginary(0.0);
	char rightBrace(0);
	istrm >> leftBrace >> real >> comma >> imaginary >> rightBrace;
	if (istrm.good())
	{
		if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) && (Complex::rightBrace == rightBrace))
		{
			re = real;
			im = imaginary;
		}
		else
		{
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}
bool testParse(const std::string& str)
{
	using namespace std;
	istringstream istrm(str);
	Complex z;
	istrm >> z;
	if (istrm.good())
	{
		cout << "Read success" << str << "->" << z << endl;
	}
	else
	{
		cout << "Read error" << str << "->" << z << endl;
	}
	return istrm.good();
}