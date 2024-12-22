cmake_minimum_required(VERSION 3.22)

project(nonlinear_equation)

add_executable(nonlinear_equation main.cpp funcs.h)

set_target_properties(nonlinear_equation PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)