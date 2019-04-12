// Copyright (C) 206 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <type_safe/integer.hpp>

#include <catch.hpp>

#include <sstream>

using namespace type_safe;

#ifndef TYPE_SAFE_TEST_NO_STATIC_ASSERT
static_assert(std::is_pod<integer<int>>::value, "");
// conversion checks
static_assert(sizeof(short) < sizeof(int), "");
static_assert(std::is_constructible<integer<short>, short>::value, "");
static_assert(!std::is_constructible<integer<short>, int>::value, "");
static_assert(!std::is_constructible<integer<short>, unsigned short>::value, "");
static_assert(!std::is_constructible<integer<unsigned short>, short>::value, "");

static_assert(std::is_assignable<integer<short>, short>::value, "");
static_assert(!std::is_assignable<integer<short>, int>::value, "");
static_assert(!std::is_assignable<integer<short>, unsigned short>::value, "");
static_assert(!std::is_assignable<integer<unsigned short>, short>::value, "");

static_assert(sizeof(int) < sizeof(long long), "");
static_assert(std::is_constructible<integer<int>, int>::value, "");
static_assert(std::is_constructible<integer<int>, short>::value, "");
static_assert(!std::is_constructible<integer<int>, long long>::value, "");
static_assert(!std::is_constructible<integer<int>, unsigned>::value, "");
static_assert(!std::is_constructible<integer<unsigned>, int>::value, "");

static_assert(std::is_assignable<integer<int>, int>::value, "");
static_assert(std::is_assignable<integer<int>, short>::value, "");
static_assert(!std::is_assignable<integer<int>, long long>::value, "");
static_assert(!std::is_assignable<integer<int>, unsigned>::value, "");
static_assert(!std::is_assignable<integer<unsigned>, int>::value, "");
#endif

TEST_CASE("integer")
{
    using int_t = integer<int>;

    SECTION("constructor")
    {
        int_t a(0);
        REQUIRE(static_cast<int>(a) == 0);
        int_t b(32);
        REQUIRE(static_cast<int>(b) == 32);
        int_t c(-25);
        REQUIRE(static_cast<int>(c) == -25);
    }
    SECTION("assignment")
    {
        int_t a(0);
        a = 32;
        REQUIRE(static_cast<int>(a) == 32);
        a = -25;
        REQUIRE(static_cast<int>(a) == -25);
    }
    SECTION("unary")
    {
        int_t a(13);
        REQUIRE(static_cast<int>(+a) == static_cast<int>(a));
        REQUIRE(static_cast<int>(-a) == -static_cast<int>(a));
    }
    SECTION("increment")
    {
        int_t a(0);
        REQUIRE(static_cast<int>(++a) == 1);
        REQUIRE(static_cast<int>(a++) == 1);
        REQUIRE(static_cast<int>(a) == 2);
    }
    SECTION("decrement")
    {
        int_t a(0);
        REQUIRE(static_cast<int>(--a) == -1);
        REQUIRE(static_cast<int>(a--) == -1);
        REQUIRE(static_cast<int>(a) == -2);
    }
    SECTION("addition")
    {
        int_t wrapper(0);
        int   normal(0);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper += 5;
        normal += 5;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = wrapper + (-23);
        normal  = normal + (-23);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = 22 + wrapper;
        normal  = 22 + normal;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = int_t(-4) + wrapper;
        normal  = (-4) + normal;
        REQUIRE(static_cast<int>(wrapper) == normal);
    }
    SECTION("subtraction")
    {
        int_t wrapper(0);
        int   normal(0);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper -= 5;
        normal -= 5;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = wrapper - (-23);
        normal  = normal - (-23);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = 22 - wrapper;
        normal  = 22 - normal;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = int_t(-4) - wrapper;
        normal  = (-4) - normal;
        REQUIRE(static_cast<int>(wrapper) == normal);
    }
    SECTION("multiplication")
    {
        int_t wrapper(1);
        int   normal(1);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper *= 5;
        normal *= 5;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = wrapper * (-23);
        normal  = normal * (-23);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = 22 * wrapper;
        normal  = 22 * normal;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = int_t(-4) * wrapper;
        normal  = (-4) * normal;
        REQUIRE(static_cast<int>(wrapper) == normal);
    }
    SECTION("division")
    {
        int_t wrapper(23 * 5);
        int   normal(23 * 5);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper /= 5;
        normal /= 5;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = wrapper / (-23);
        normal  = normal / (-23);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = 22 / wrapper;
        normal  = 22 / normal;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = int_t(-4) / wrapper;
        normal  = (-4) / normal;
        REQUIRE(static_cast<int>(wrapper) == normal);
    }
    SECTION("modulo")
    {
        int_t wrapper(24 * 6);
        int   normal(24 * 6);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper %= 5;
        normal %= 5;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = wrapper % (-23);
        normal  = normal % (-23);
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = 22 % wrapper;
        normal  = 22 % normal;
        REQUIRE(static_cast<int>(wrapper) == normal);

        wrapper = int_t(-4) % wrapper;
        normal  = (-4) % normal;
        REQUIRE(static_cast<int>(wrapper) == normal);
    }
    SECTION("comparison")
    {
        // ==
        REQUIRE(bool(int_t(4) == int_t(4)));
        REQUIRE(!(int_t(5) == int_t(4)));

        REQUIRE(bool(4 == int_t(4)));
        REQUIRE(!(5 == int_t(4)));

        REQUIRE(bool(int_t(4) == 4));
        REQUIRE(!(int_t(5) == 4));

        // !=
        REQUIRE(bool(int_t(5) != int_t(4)));
        REQUIRE(!(int_t(4) != int_t(4)));

        REQUIRE(bool(5 != int_t(4)));
        REQUIRE(!(4 != int_t(4)));

        REQUIRE(bool(int_t(5) != 4));
        REQUIRE(!(int_t(4) != 4));

        // <
        REQUIRE(bool(int_t(4) < int_t(5)));
        REQUIRE(!(int_t(5) < int_t(4)));
        REQUIRE(!(int_t(4) < int_t(4)));

        REQUIRE(bool(4 < int_t(5)));
        REQUIRE(!(5 < int_t(4)));
        REQUIRE(!(4 < int_t(4)));

        REQUIRE(bool(int_t(4) < 5));
        REQUIRE(!(int_t(5) < 4));
        REQUIRE(!(int_t(4) < 4));

        // <=
        REQUIRE(bool(int_t(4) <= int_t(5)));
        REQUIRE(!(int_t(5) <= int_t(4)));
        REQUIRE(bool(int_t(4) <= int_t(4)));

        REQUIRE(bool(4 <= int_t(5)));
        REQUIRE(!(5 <= int_t(4)));
        REQUIRE(bool(4 <= int_t(4)));

        REQUIRE(bool(int_t(4) <= 5));
        REQUIRE(!(int_t(5) <= 4));
        REQUIRE(bool(int_t(4) <= 4));

        // >
        REQUIRE(bool(int_t(5) > int_t(4)));
        REQUIRE(!(int_t(4) > int_t(5)));
        REQUIRE(!(int_t(5) > int_t(5)));

        REQUIRE(bool(5 > int_t(4)));
        REQUIRE(!(4 > int_t(5)));
        REQUIRE(!(5 > int_t(5)));

        REQUIRE(bool(int_t(5) > 4));
        REQUIRE(!(int_t(4) > 5));
        REQUIRE(!(int_t(5) > 5));

        // >=
        REQUIRE(bool(int_t(5) >= int_t(4)));
        REQUIRE(!(int_t(4) >= int_t(5)));
        REQUIRE(bool(int_t(5) >= int_t(5)));

        REQUIRE(bool(5 >= int_t(4)));
        REQUIRE(!(4 >= int_t(5)));
        REQUIRE(bool(5 >= int_t(5)));

        REQUIRE(bool(int_t(5) >= 4));
        REQUIRE(!(int_t(4) >= 5));
        REQUIRE(bool(int_t(5) >= 5));
    }
    SECTION("make_(un)signed")
    {
        int_t             a = 5;
        integer<unsigned> b = make_unsigned(a);
        REQUIRE(static_cast<unsigned>(b) == 5);

        b = 125u;
        a = make_signed(b);
        REQUIRE(static_cast<int>(a) == 125);
    }
    SECTION("i/o")
    {
        std::ostringstream out;
        std::istringstream in("10");

        int_t i(0);
        out << i;
        REQUIRE(out.str() == "0");

        in >> i;
        REQUIRE(static_cast<int>(i) == 10);
    }
    SECTION("abs")
    {
        int               i  = 123;
        integer<unsigned> ia = type_safe::abs(i);
        REQUIRE(static_cast<unsigned>(ia) == 123u);

        i  = -123;
        ia = type_safe::abs(i);
        REQUIRE(static_cast<unsigned>(ia) == 123u);
    }
}
