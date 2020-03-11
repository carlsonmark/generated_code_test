cmake_minimum_required(VERSION 3.15)
project(generated_code_test
        VERSION 1.0.0
        #LANGUAGES C++
        )

set(CMAKE_CXX_STANDARD 17)

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
