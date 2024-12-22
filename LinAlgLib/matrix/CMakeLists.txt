cmake_minimum_required(VERSION 3.22)

project(LinAlgLib_matrix)

add_library(LinAlgLib_matrix matrix.hpp crutch.cpp)

add_subdirectory(test)
target_include_directories(
        LinAlgLib_matrix
        PUBLIC
        .)

set_target_properties(LinAlgLib_matrix PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Linear Algebra library - matrix"
)