/**
 * Created by mark on 2020-03-15.
 */

#include <benchmark/benchmark.h>
#include "library.h"
#include <iostream>

static void BM_Apodize(benchmark::State& state) {
    unsigned int rows = 1024;
    unsigned int cols = 1024;
    for (auto _ : state)
    {
        state.PauseTiming();
        std::vector<std::complex<double>> inputData(rows*cols, std::complex<double>(0.11,0.11));
        state.ResumeTiming();
        apodizeSineBell(inputData, rows);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Apodize);

static void BM_ApodizeOpenMP(benchmark::State& state) {
    unsigned int rows = 1024;
    unsigned int cols = 1024;
    for (auto _ : state)
    {
        state.PauseTiming();
        std::vector<std::complex<double>> inputData(rows*cols, std::complex<double>(0.11,0.11));
        state.ResumeTiming();
        apodizeSineBellOpenMP(inputData, rows);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_ApodizeOpenMP);

static void BM_ApodizeOpenMPAuto(benchmark::State& state) {
    unsigned int rows = 1024;
    unsigned int cols = 1024;
    for (auto _ : state)
    {
        state.PauseTiming();
        std::vector<std::complex<double>> inputData(rows*cols, std::complex<double>(0.11,0.11));
        state.ResumeTiming();
        apodizeSineBellOpenMPAuto(inputData, rows);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_ApodizeOpenMPAuto);

#ifdef TBB_NOT_BROKEN
static void BM_ApodizeParallel(benchmark::State& state) {
    unsigned int rows = 1024;
    unsigned int cols = 1024;
    for (auto _ : state)
    {
        state.PauseTiming();
        std::vector<std::complex<double>> inputData(rows*cols, std::complex<double>(0.11,0.11));
        state.ResumeTiming();
        apodizeSineBellParallel(inputData, rows);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_ApodizeParallel);

static void BM_ApodizeMoreParallel(benchmark::State& state) {
    unsigned int rows = 1024;
    unsigned int cols = 1024;
    for (auto _ : state)
    {
        state.PauseTiming();
        std::vector<std::complex<double>> inputData(rows*cols, std::complex<double>(0.11,0.11));
        state.ResumeTiming();
        apodizeSineBellMoreParallel(inputData, rows);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_ApodizeMoreParallel);
#endif

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
