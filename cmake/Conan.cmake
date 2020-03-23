macro(run_conan)
    find_program(CONAN_FOUND conan)
    if (NOT CONAN_FOUND)
        message(FATAL_ERROR
                "---------------------------------\n"
                "Conan not found. Install it with:\n"
                "# pip3 install conan\n")
    endif()

    # Download automatically, you can also just copy the conan.cmake file
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(
                STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME bincrafters URL
            https://api.bintray.com/conan/bincrafters/public-conan)

    conan_cmake_run(
            REQUIRES
            ${CONAN_EXTRA_REQUIRES}
            benchmark/1.5.0
            catch2/2.11.0
            fmt/6.0.0
            ms-gsl/2.0.0
            # tbb/2020.0 # Currently broken
            OPTIONS
            ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
            CMAKE_TARGETS # individual targets to link to
            BUILD
            missing)
endmacro()
