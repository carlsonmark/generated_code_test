cmake_minimum_required(VERSION 3.15)

find_package(OpenMP REQUIRED)

file(GLOB globbedInputs ${GEN_SOURCE_DIR}/*.in)

# A list of all of the generated source files
set(GENERATED_SOURCES)

# Add custom commands to generate each source file
foreach(inFile ${globbedInputs})
    # Create the filenames that will be generated, based on the input files
    string(REGEX REPLACE "\\.in" ".cpp" cppFilename ${inFile})
    string(REGEX REPLACE ${GEN_SOURCE_DIR} ${GEN_DIR} cppFilename ${cppFilename})
    string(REGEX REPLACE "\\.in" ".hpp" hppFilename ${inFile})
    string(REGEX REPLACE ${GEN_SOURCE_DIR} ${GEN_DIR} hppFilename ${hppFilename})
    set(GENERATED_SOURCES ${GENERATED_SOURCES} ${cppFilename} ${hppFilename})
    add_custom_command(
            OUTPUT ${cppFilename} ${hppFilename}
            COMMAND ${CMAKE_SOURCE_DIR}/bin/gen.sh ${inFile} ${GEN_DIR}
            DEPENDS ${inFile}
            COMMENT "Running gen.sh ${inFile} ${GEN_DIR}"
    )
endforeach()

set(LIBGENERATED_CODE_TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/library.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/library.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pybinds.cpp
        ${GENERATED_SOURCES})
set(LIBGENERATED_CODE_TEST_SOURCES ${LIBGENERATED_CODE_TEST_SOURCES} PARENT_SCOPE)
add_library(generated_code_test SHARED
        ${LIBGENERATED_CODE_TEST_SOURCES}
        )

target_link_libraries(generated_code_test project_warnings project_options
        CONAN_PKG::ms-gsl
        CONAN_PKG::tbb
        OpenMP::OpenMP_CXX
        pybind11::module
        ${PYTHON_LIBRARIES})

set_target_properties(generated_code_test PROPERTIES
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}")

add_library(generated_code_test_static STATIC
        ${LIBGENERATED_CODE_TEST_SOURCES}
        )
target_link_libraries(generated_code_test_static project_warnings project_options
        CONAN_PKG::ms-gsl
        CONAN_PKG::tbb
        OpenMP::OpenMP_CXX
        ${PYTHON_LIBRARIES})
