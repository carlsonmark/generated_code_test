/**
 * Created by mark on 2020-03-14.
 */
#include <catch2/catch.hpp>

#include "generated/thing1.hpp"
#include "generated/thing2.hpp"

TEST_CASE("Verify methods were generated", "[generated]")
{
    REQUIRE(thing1() == "thing1()");
    REQUIRE(thing2() == "thing2()");
}
