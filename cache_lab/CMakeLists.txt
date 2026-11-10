cmake_minimum_required(VERSION 4.3)
project(oop_lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cache_lib
        lru_cache.cpp
        lfu_cache.cpp
        fib_calc.cpp
)
target_include_directories(cache_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cache_app main.cpp)
target_link_libraries(cache_app cache_lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(cache_tests
        tests/lru_cache_tests.cpp
        tests/lfu_cache_tests.cpp
        tests/fib_calc_tests.cpp
)
target_link_libraries(cache_tests cache_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cache_tests)