cmake_minimum_required(VERSION 3.10)
project(lab0_plus CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab0_plus
        main.cpp
        errors.cpp
        file_io.cpp
        utils.cpp
)