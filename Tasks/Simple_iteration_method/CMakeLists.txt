cmake_minimum_required(VERSION 3.22)

project(Simple_iteration_method)

add_executable(Simple_iteration_method main.cpp
        funcs.h)

set_target_properties(Simple_iteration_method PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Thomas method implementation"
)