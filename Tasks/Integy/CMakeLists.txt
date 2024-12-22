cmake_minimum_required(VERSION 3.22)

project(Integy)

add_executable(Integy main.cpp integ_func.h)

set_target_properties(Integy PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)