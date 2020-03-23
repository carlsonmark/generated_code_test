
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Note: This is what is recommended on the Google benchmark github,
#       but it would only work if find_package() works...
#find_package(benchmark REQUIRED)
#target_link_libraries(bench_library benchmark::benchmark)

include_directories(${generated_code_test_SOURCE_DIR}/src/library)
add_executable(bench_library BenchLibrary.cpp)

target_link_libraries(bench_library
        ${CONAN_LIBS}
        generated_code_test_static
        project_warnings
        project_options
        )

