#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.h>
#include <iostream>
#include<sstream>
TEST_CASE("[rational] - Rational ctor")
{
    CHECK((Rational() == Rational(0, 1)));
    CHECK((Rational(3) == Rational(3, 1)));
    CHECK((Rational(3, 9) == Rational(1, 3)));
    CHECK((Rational(-2,6) == Rational(-1, 3)));
    CHECK((Rational(2, -6) == Rational(-1, 3)));
    CHECK((Rational(-4,2) == Rational(-2,1)));
    CHECK((Rational(4, -2) == Rational(-2,1)));
    CHECK((Rational(0,10) == Rational(0, 1)));
}

TEST_CASE("[rational] - enter ")
{
    std::stringstream stream("4/5 -7/6 9/1 8/-7");
    Rational test;
    stream >> test;
    CHECK((test == Rational(4, 5)));
    stream >> test;
    CHECK((test == Rational(-7, 6)));
    stream >> test;
    CHECK((test == Rational(9, 1)));
    stream >> test;
    CHECK((test == Rational(8, -7)));
}

TEST_CASE("[rational] - exit")
{
    std::stringstream stream("");
    Rational test;
    test = Rational(7, 8);
    stream << test;
    CHECK((stream.str() == "7/8"));
}


TEST_CASE("[rational] - Rational denum is zero")
{
    CHECK_THROWS((Rational(1, 0)));
    CHECK_THROWS(Rational(1, 3) / Rational(0, 8));
}

TEST_CASE("FAIL - operator>>(std::istream&, Complex&)") {
    std::stringstream stream;
    std::vector<std::string> strs = {
        "{1.1/2.2}",
        "1.1,2.2",
        "[1.1,2.2]",
        "2.0",
        "abc",
    };
    for (const auto& str : strs) {
        CAPTURE(str);
        stream << str;
        Rational z;
        stream >> z;
        REQUIRE(stream.fail());
        REQUIRE(z.num == 0.0);
        stream.clear();
    }
}

TEST_CASE("[rational] - Rational bool value")
{
    CHECK(!(Rational(1,5)== Rational(1, 10)));
    CHECK((Rational(1, 5) == Rational(1, 5)));

    CHECK((!(Rational(1, 5) != Rational(1, 5))));
    CHECK((Rational(1, 5) != Rational(1, 10)));

    CHECK((!(Rational(1, 5) < Rational(1, 10))));
    CHECK((Rational(1, 10) < Rational(1, 5)));
    CHECK((!(Rational(1, 5) < Rational(1, 5))));

    CHECK((Rational(1, 5) <= Rational(1, 5)));
    CHECK((!(Rational(1, 5) <= Rational(1, 10))));
    CHECK((Rational(1, 10) <= Rational(1, 5)));

    CHECK((Rational(1, 5) > Rational(1, 10)));
    CHECK((!(Rational(1, 10) > Rational(1, 10))));
    CHECK((!(Rational(1, 10) > Rational(1, 5))));

    CHECK((Rational(1, 5) >= Rational(1, 10)));
    CHECK((Rational(1, 10) >= Rational(1, 10)));
    CHECK((!(Rational(1, 10) >= Rational(1, 5))));
}

TEST_CASE("[rational] - ariphmetic") //25 тестов 5 на каждую операцию
{
    CHECK(((Rational(1, 2) + Rational(1, 4)) == Rational(3, 4)));
    CHECK(((Rational(-1, 2) += Rational(1, 4)) == Rational(-1, 4)));
    CHECK(((Rational(1, -2) += Rational(1, 4)) == Rational(-1, 4)));
    CHECK(((Rational(1, 2) += Rational(-1, 4)) == Rational(1, 4)));
    CHECK(((Rational(-1, 2) += Rational(-1, 4)) == Rational(-3, 4)));

    CHECK(((Rational(1, 2) -= Rational(1, 4)) == Rational(1, 4)));
    CHECK(((Rational(1, 2) -= Rational(-1, 4)) == Rational(3, 4)));
    CHECK(((Rational(-1, 2) -= Rational(1, 4)) == Rational(-3, 4)));
    CHECK(((Rational(1, -2) -= Rational(1, 4)) == Rational(-3, 4)));
    CHECK(((Rational(-1, 2) -= Rational(-1, 4)) == Rational(-1, 4)));

    CHECK(((Rational(1, 2) *= Rational(1, 4)) == Rational(1, 8)));
    CHECK(((Rational(-1, 2) *= Rational(1, 4)) == Rational(-1, 8)));
    CHECK(((Rational(1, -2) *= Rational(1, 4)) == Rational(-1, 8)));
    CHECK(((Rational(1, 2) *= Rational(-1, 4)) == Rational(-1, 8)));
    CHECK(((Rational(-1, 2) *= Rational(-1, 4)) == Rational(1, 8)));

    CHECK(((Rational(1, 2) / Rational(1, 4)) == Rational(2,1)));
    CHECK(((Rational(-1, 2) /= Rational(1, 4)) == Rational(-2,1)));
    CHECK(((Rational(1, -2) /= Rational(1, 4)) == Rational(-2,1)));
    CHECK(((Rational(1, 2) /= Rational(-1, 4)) == Rational(-2,1)));
    CHECK(((Rational(-1, 2) /= Rational(-1, 4)) == Rational(2,1)));

    CHECK(((Rational(1, 4) /= Rational(1, 2)) == Rational(1, 2)));
    CHECK(((Rational(1, 4) /= Rational(1, 2)) == Rational(1, 2)));
    CHECK(((Rational(-1, 4) /= Rational(1, 2)) == Rational(-1, 2)));
    CHECK(((Rational(1, -4) /= Rational(1, 2)) == Rational(-1, 2)));
    CHECK(((Rational(1, 4) /= Rational(-1, 2)) == Rational(-1, 2)));
    CHECK(((Rational(-1, 4) /= Rational(-1, 2)) == Rational(1, 2)));

    CHECK(((Rational(-1) /= Rational(-1, 2)) == Rational(2, 1)));
    CHECK(((Rational(0) /= Rational(-1, 2)) == Rational(0, 1)));
    CHECK(((Rational(2) /= Rational(-1, 2)) == Rational(-4)));
    CHECK(((Rational(2, 4) /= Rational(-1)) == Rational(-1,2)));


}