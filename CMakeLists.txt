cmake_minimum_required(VERSION 3.15)
project(generated_code_test)

set(CMAKE_CXX_STANDARD 17)

set(GEN_DIR ${CMAKE_SOURCE_DIR}/src/library/generated)
add_subdirectory(generatefrom)

add_subdirectory(src)

