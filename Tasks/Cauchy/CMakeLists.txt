cmake_minimum_required(VERSION 3.22)

project(Cauchy)

add_executable(Cauchy_1 first.cpp c_funcs.h)
add_executable(Cauchy_2 second.cpp c_funcs.h)

set_target_properties(Cauchy_1 PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)

set_target_properties(Cauchy_2 PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)