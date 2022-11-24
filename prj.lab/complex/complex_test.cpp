#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <complex/complex.h>

TEST_CASE("[complex] - Complex ctor")
{
	CHECK(Complex() == Complex(0, 0));
	CHECK(Complex(1.5) == Complex(1.5, 0));
}
TEST_CASE("[complex] - ariphmetic")
{
	CHECK(((Complex(3, 6) + Complex(-5, 8)) == Complex(3-5, 6+8)));
	CHECK(((Complex(3, 6) - Complex(-5, 8)) == Complex(8, -2)));
	CHECK(((Complex(3, 6) * Complex(-5, 8)) == Complex(-63, -6)));
	CHECK(((Complex(5.3, 7) / Complex(7.8)) ==Complex(0.6794871794871795, 0.8974358974358975)));
	CHECK(((Complex(7.8) * Complex(-5, 8)) == Complex(-39, 62.4)));
	CHECK(((Complex(2, 3) / Complex(5, 6)) == Complex(0.459016393442623, 0.0491803278688525)));
}

TEST_CASE("[complex] - enter ")
{
	std::stringstream stream("{2.5,4} {-3,7.9} {3,-7} {6,-1.9} {3,4}");
	Complex test;
	stream >> test;
	CHECK((test == Complex(2.5, 4)));
	stream >> test;
	CHECK((test == Complex(-3, 7.9)));
	stream >> test;
	CHECK((test == Complex(3, -7)));
	stream >> test;
	CHECK((test == Complex(6, -1.9)));
	stream >> test;
	CHECK((test == Complex(3, 4)));
}

TEST_CASE("FAIL - operator>>(std::istream&, Complex&)") {
	std::stringstream stream;
	std::vector<std::string> strs = {
		"{1.1;2.2}",
		"1.1,2.2",
		"[1.1,2.2]",
		"2.0",
		"abc",
	};
	for (const auto& str : strs) {
		CAPTURE(str);
		stream << str;
		Complex z;
		stream >> z;
		REQUIRE(stream.fail());
		REQUIRE(z.re == 0.0);
		REQUIRE(z.im == 0.0);
		stream.clear();
	}
}

TEST_CASE("[complex] - exit")
{
	std::stringstream stream_2("");
	Complex test = Complex(7,8);
	stream_2 << test;
	CHECK((stream_2.str() == "{7,8}"));
}


/*int main()
{
	Complex z, y;
	
	Complex a(3,6);
	Complex b(-5,8);
	Complex c(7.8);
	Complex res0 = a + b;
	Complex res1 = a - b;
	Complex res2 = a * b;
	Complex res3 = a / b;
	Complex res4 = a * c;
	Complex res5 = a / c;
	if(res0==Complex(-2,14))
		std::cout <<a<< " + " <<b<< "  is right"<< '\n';
	else std::cout << a << " + " << b << "  is false"<<'\n';
	if (res1 == Complex(8, -2))
		std::cout << a << " - " << b << "  is right"<< '\n';
	else std::cout << a << " - " << b << "  is false"<< '\n';
	if (res2 == Complex(-63, -6))
		std::cout << a << " * " << b << "  is right"<< '\n';
	else std::cout << a << " * " << b << "  is false"<< '\n';
	if (res3 == Complex(0.370786516, -0.606741573))
		std::cout << a << " / " << b << "  is right"<< '\n';
	else std::cout << a << " / " << b << "  is false"<< '\n';
	if(res4==Complex(23.4,46.8))
		std::cout << a << " * " << c << "  is right" << '\n';
	else std::cout << a << " * " << c << "  is false" << '\n';
	return 0;
}*/
//CHECK(((Complex(2, 3) / Complex(5, 6)) == Complex(0.459016393442623, 0.0491803278688525)));