cmake_minimum_required(VERSION 3.22)

project(Differential)

add_executable(Differential main.cpp diff_funcs.h)

set_target_properties(Differential PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)