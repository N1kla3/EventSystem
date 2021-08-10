cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME eventsystem)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        Delegate.cpp Delegate.h)

set(TESTS
        DelegateTest.cpp
        )

list(TRANSFORM TESTS PREPEND "tests/")
list(TRANSFORM SOURCE PREPEND "src/")


add_executable(${PROJECT_NAME} ${SOURCE} main.cpp)
add_executable(tests ${SOURCE} ${TESTS})
add_test(NAME first COMMAND tests)

target_link_libraries(tests gtest gtest_main)