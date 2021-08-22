cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME eventsystem)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE
        Delegate.cpp Delegate.h MultiCastDelegate.cpp MultiCastDelegate.h DelegateHandle.cpp DelegateHandle.h)

set(TESTS
        DelegateTest.cpp
        MulticastDelegateTest.cpp)

list(TRANSFORM TESTS PREPEND "tests/")
list(TRANSFORM SOURCE PREPEND "src/")

enable_testing()

add_library(${PROJECT_NAME} ${SOURCE})
add_executable(tests ${TESTS})
add_test(NAME first COMMAND tests)

target_link_libraries(tests gtest gtest_main ${PROJECT_NAME})