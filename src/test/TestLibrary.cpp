/**
 * Created by mark on 2020-03-14.
 */
#include <catch2/catch.hpp>
#include <complex>
#include <vector>

#include "library.h"
#include "generated/thing1.hpp"
#include "generated/thing2.hpp"

TEST_CASE("Verify methods were generated", "[generated]")
{
    REQUIRE(thing1() == "thing1()");
    REQUIRE(thing2() == "thing2()");
}

TEST_CASE("Verify benchmarked apodization methods produce the same result", "[apodization]") {

    unsigned int rows = 5;
    unsigned int cols = 5;
    std::vector<std::complex<double>> data1(rows*cols, std::complex<double>(0.11,0.11));
    apodizeSineBell(data1, rows);
#ifdef TBB_NOT_BROKEN
    std::vector<std::complex<double>> data2(rows*cols, std::complex<double>(0.11,0.11));
    apodizeSineBellParallel(data2, rows);
    std::vector<std::complex<double>> data3(rows*cols, std::complex<double>(0.11,0.11));
    apodizeSineBellMoreParallel(data3, rows);
#endif
    std::vector<std::complex<double>> data4(rows*cols, std::complex<double>(0.11,0.11));
    apodizeSineBellOpenMP(data4, rows);
//    REQUIRE(data1 == data2);
//    REQUIRE(data1 == data3);
    REQUIRE(data1 == data4);
}
