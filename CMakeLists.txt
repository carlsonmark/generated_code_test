cmake_minimum_required(VERSION 3.15)
project(generated_code_test
        VERSION 1.0.0
        #LANGUAGES C++
        )

######################################################
# From https://github.com/lefticus/cpp_starter_project

include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which
    # is a good idea if any #define's change
    #
    #
    target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

###############
# Mark's items:

# Python
set(Python_ADDITIONAL_VERSIONS 3.5)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Pybind11 (git submodule)
set(PYBIND11_CPP_STANDARD -std=c++17)
add_subdirectory(submodules/pybind11)
include_directories(submodules/pybind11/include)

set(GEN_DIR ${CMAKE_SOURCE_DIR}/src/library/generated)
set(GEN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/generatefrom)

add_subdirectory(src)

add_custom_target(
    touchCmakeLists ALL
    )

add_custom_command(
    TARGET touchCmakeLists
    COMMAND ${PROJECT_SOURCE_DIR}/bin/touchcmakelists.py
            ${PROJECT_SOURCE_DIR}/CMakeLists.txt
            ${GEN_SOURCE_DIR}
            ${GEN_DIR}
)

if(ENABLE_TESTING)
    enable_testing()
    message(
            "Building Tests."
    )
    add_subdirectory(src/test)
endif()

