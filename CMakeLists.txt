cmake_minimum_required(VERSION 3.24)

project(cpp_skills LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_BENCHMARKS "Build benchmark executables" OFF)

add_library(codility
    src/codility/binary_gap.cpp
)

target_include_directories(codility
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(CTest)

if(BUILD_TESTING)
    include(cmake/dependencies.cmake)

    add_executable(codility_tests
        tests/codility/test_binary_gap.cpp
    )

    target_link_libraries(codility_tests
        PRIVATE
            codility
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(codility_tests)
endif()

if(BUILD_BENCHMARKS)
    add_executable(binary_gap_benchmark
        benchmarks/codility/benchmark_binary_gap.cpp
    )

    target_link_libraries(binary_gap_benchmark
        PRIVATE
            codility
    )
endif()
