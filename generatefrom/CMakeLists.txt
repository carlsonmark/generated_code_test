cmake_minimum_required(VERSION 3.15)
project(gen)

add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/src/library/generated/thing1.cpp ${CMAKE_SOURCE_DIR}/src/library/generated/thing1.hpp
        COMMAND ${CMAKE_SOURCE_DIR}/bin/gen.sh ${CMAKE_SOURCE_DIR}/generatefrom/thing1.txt ${CMAKE_SOURCE_DIR}/src/library/generated
        DEPENDS thing1.txt
        COMMENT "Running gen.sh"
)

add_custom_target(run_generator ALL
        DEPENDS ${CMAKE_SOURCE_DIR}/src/library/generated/thing1.cpp ${CMAKE_SOURCE_DIR}/src/library/generated/thing1.hpp

        )
