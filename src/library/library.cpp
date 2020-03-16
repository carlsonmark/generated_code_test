#include "library.h"

#include <algorithm>
#include <complex>
#include <iostream>
#include <execution>
#include <vector>

#include <gsl/span>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

/**
 * Baseline for benchmark.
 * Single-threaded 2D apodization
 */
void apodizeSineBell(std::vector<std::complex<double>> &array, size_t rows)
{
    size_t cols = array.size() / rows;
    double radScale = M_PI / ((double)rows - 1);
    for (size_t row = 0; row < rows; row++)
    {
        size_t begin = row * cols;
        size_t end = (row+1) * cols;
        gsl::span<std::complex<double>> rowSpan(&(*(array.begin() + begin)), cols);
        // Calculate the scaling factor for this index
        double scalingFactor = sin((double)row * radScale);
        // Apply the scaling factor to all columns of the row
        for (size_t col = 0; col < cols; col++)
            rowSpan[col] *= scalingFactor;
    }
}

/**
 * Use OpenMP to parallelize the outer loop.
 * Implementation complexity: Minimal
 * This should spin up a minimal amount of threads to do the work.
 */
void apodizeSineBellOpenMP(std::vector<std::complex<double>> &array, size_t rows)
{
    size_t cols = array.size() / rows;
    double radScale = M_PI / ((double)rows - 1);
#pragma omp parallel for default(shared)
    for (size_t row = 0; row < rows; row++)
    {
        size_t begin = row * cols;
        size_t end = (row+1) * cols;
        gsl::span<std::complex<double>> rowSpan(&(*(array.begin() + begin)), cols);
        // Calculate the scaling factor for this index
        double scalingFactor = sin((double)row * radScale);
        // Apply the scaling factor to all columns of the row
        for (size_t col = 0; col < cols; col++)
            rowSpan[col] *= scalingFactor;
    }
}

/**
 * Use OpenMP to parallelize the outer loop.
 * Implementation complexity: Minimal
 * This should spin up a minimal amount of threads to do the work.
 */
void apodizeSineBellOpenMPAuto(std::vector<std::complex<double>> &array, size_t rows)
{
    size_t cols = array.size() / rows;
    double radScale = M_PI / ((double)rows - 1);
#pragma omp parallel for default(shared)
    for (size_t row = 0; row < rows; row++)
    {
        size_t begin = row * cols;
        size_t end = (row+1) * cols;
        gsl::span<std::complex<double>> rowSpan(&(*(array.begin() + begin)), cols);
        // Calculate the scaling factor for this index
        double scalingFactor = sin((double)row * radScale);
        // Apply the scaling factor to all columns of the row
        for (auto &element : rowSpan)
            element *= scalingFactor;
    }
}
/**
 * Use std::transform to parallelize the inner loop
 * Implementation complexity: Minimal
 * This ends up spinning up a lot of threads to do the work.
 */
void apodizeSineBellParallel(std::vector<std::complex<double>> &array, size_t rows)
{
    size_t cols = array.size() / rows;
    // Parameters calculation
    double radScale = M_PI / ((double)rows - 1);
    // Array Apodization of non-zeroed values
    for (size_t row = 0; row < rows; row++)
    {
        size_t begin = row * cols;
        gsl::span<std::complex<double>> rowSpan(&(*(array.begin() + begin)), cols);
        // Calculate the scaling factor for this index
        double scalingFactor = sin((double)row * radScale);
        // Apply the scaling factor to all columns of the row
        std::transform(std::execution::par, rowSpan.begin(), rowSpan.end(), rowSpan.begin(),
                    [&](std::complex<double> cd){
            return cd * scalingFactor;
        });
    }
}

/**
 * Helper class for iterating over a 2D array
 */
struct ApodHelper {
    // The row data in span format
    gsl::span<std::complex<double>> span;
    // The index of hte row
    size_t row{};
};

/**
 * Use std::transform to parallelize the outer loop
 * Implementation complexity: Moderate
 * This should spin up a minimal amount of threads to do the work.
 * It does require a way of iterating over each row individually, which
 * means a helper is needed.
 */
void apodizeSineBellMoreParallel(std::vector<std::complex<double>> &array, size_t rows)
{
    size_t cols = array.size() / rows;
    double radScale = M_PI / ((double)rows - 1);
    // Create row helpers for iterating over rows within 'array'
    std::vector<ApodHelper> rowHelpers;
    for (size_t row = 0; row < rows; row++) {
        size_t begin = row * cols;
        rowHelpers.push_back(ApodHelper{gsl::span<std::complex<double>>(&(*(array.begin() + begin)), cols), row});
    }
    // Iterate over the rows
    std::transform(std::execution::par, rowHelpers.begin(), rowHelpers.end(), rowHelpers.begin(),
                   [&radScale,&cols](ApodHelper helper){
                       double scalingFactor = sin(helper.row * radScale);
                       for (size_t col = 0; col < cols; col++)
                           helper.span[col] *= scalingFactor;
                       return helper;
                   });
}
