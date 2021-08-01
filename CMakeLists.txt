cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME template)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        )

set(TESTS
        tests/test.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE} main.cpp)
add_executable(tests ${SOURCE} ${TESTS})

target_link_libraries(tests gtest gtest_main)