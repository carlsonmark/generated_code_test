cmake_minimum_required(VERSION 3.15)

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
            COMMENT "Running gen.sh"
    )
endforeach()


add_library(generated_code_test SHARED library.cpp library.h
        ${GENERATED_SOURCES}
        )
