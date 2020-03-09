cmake_minimum_required(VERSION 3.15)

execute_process(COMMAND ${CMAKE_SOURCE_DIR}/bin/gencmakelists.sh ${GEN_DIR} ${GENERATED_SOURCES})
add_custom_target(touch_cmakelists.txt ALL
        COMMAND touch ${CMAKE_SOURCE_DIR}/CMakeLists.txt
        )

include(generated/generated.cmake)

add_library(generated_code_test SHARED library.cpp library.h ${GENERATED_SOURCES})
