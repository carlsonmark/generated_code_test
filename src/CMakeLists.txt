add_subdirectory(library)
add_subdirectory(benchmark)

if(ENABLE_TESTING)
    enable_testing()
    message(
            "Building Tests."
    )
    add_subdirectory(test)
endif()
