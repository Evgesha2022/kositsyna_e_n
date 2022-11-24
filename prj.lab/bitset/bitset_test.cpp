#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <bitset/bitset.h>
#include <iostream>
#include <sstream>
TEST_CASE("[rational] - Rational ctor")
{
    CHECK(Bitset() == Bitset(0));
    CHECK(Bitset() != Bitset(1));
    CHECK_THROWS(Bitset(-3));
    CHECK(Bitset(10) == Bitset(10, 0));
    CHECK((Bitset(0) &= Bitset(1)) == Bitset(0));
    CHECK_THROWS(Bitset() |= Bitset(1));
    CHECK_THROWS(Bitset() ^= Bitset(1));
    CHECK_THROWS(Bitset(3)[-1]);
    CHECK_THROWS(Bitset(3)[3]);
    Bitset c(13, 0);
    CHECK(c == Bitset(0000000000000));
    /*Bitset d(12, 0);
    CHECK(~d == Bitset(111111111111));*/
    Bitset d(5, 0);
    CHECK(~d == Bitset(11111));
    Bitset a(10, 1);
    std::stringstream sstream("");
    sstream << a;
    CHECK(sstream.str() == std::string("1111111111"));
}