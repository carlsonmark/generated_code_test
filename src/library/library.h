#ifndef GENERATED_CODE_TEST_LIBRARY_H
#define GENERATED_CODE_TEST_LIBRARY_H

#include <complex>
#include <vector>

void hello();
void apodizeSineBell(std::vector<std::complex<double>> &array, size_t rows);
void apodizeSineBellOpenMP(std::vector<std::complex<double>> &array, size_t rows);
void apodizeSineBellOpenMPAuto(std::vector<std::complex<double>> &array, size_t rows);
void apodizeSineBellParallel(std::vector<std::complex<double>> &array, size_t rows);
void apodizeSineBellMoreParallel(std::vector<std::complex<double>> &array, size_t rows);

#endif //GENERATED_CODE_TEST_LIBRARY_H
