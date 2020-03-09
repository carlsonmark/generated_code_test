cmake_minimum_required(VERSION 3.15)
project(gen)

set(GENERATED_SOURCES
        ${GEN_DIR}/thing1.cpp ${GEN_DIR}/thing1.hpp
        PARENT_SCOPE)

add_custom_command(
        OUTPUT ${GEN_DIR}/thing1.cpp ${GEN_DIR}/thing1.hpp
        COMMAND ${CMAKE_SOURCE_DIR}/bin/gen.sh ${CMAKE_CURRENT_SOURCE_DIR}/thing1.txt ${GEN_DIR}
        DEPENDS thing1.txt
        COMMENT "Running gen.sh"
)

add_custom_command(
        OUTPUT ${GEN_DIR}/CMakeLists.txt
        COMMAND ${CMAKE_SOURCE_DIR}/bin/gencmakelists.sh ${GEN_DIR}/CMakeLists.txt ${GEN_DIR}/thing1.cpp ${GEN_DIR}/thing1.hpp
        COMMENT "Running gencmakelists.sh"
)


add_custom_target(run_generator ALL
        DEPENDS ${GEN_DIR}/thing1.cpp ${GEN_DIR}/thing1.hpp ${GEN_DIR}/CMakeLists.txt
        )
