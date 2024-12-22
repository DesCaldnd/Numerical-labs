cmake_minimum_required(VERSION 3.22)

project(Interpolation)

add_executable(Interpolation main.cpp funcs.h)

set_target_properties(Interpolation PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)