
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <BitsetT/bitsetT.h>
#include <iostream>
#include <sstream>

TEST_CASE_TEMPLATE("[rational] - Bitset ctor", type, uint8_t, uint16_t, uint32_t, uint64_t)
{
    CHECK(BitsetT<type>() == BitsetT<type>(0));
    CHECK(BitsetT<type>() != BitsetT<type>(1));
    CHECK_THROWS(BitsetT<type>(-3));
    CHECK(BitsetT<type>(10) == BitsetT<type>(10, 0));
    CHECK_THROWS(BitsetT<type>() &= BitsetT<type>(1));
    CHECK_THROWS(BitsetT<type>() |= BitsetT<type>(1));
    CHECK_THROWS(BitsetT<type>() ^= BitsetT<type>(1));
    CHECK_THROWS(BitsetT<type>(3)[-1]);
    CHECK_THROWS(BitsetT<type>(3)[3]);
}