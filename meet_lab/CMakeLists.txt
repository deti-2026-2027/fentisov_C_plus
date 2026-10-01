cmake_minimum_required(VERSION 4.3)
project(lab0 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab0 main.c
        errors.c
        file_io.c
        utils.c)
