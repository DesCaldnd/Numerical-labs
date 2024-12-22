cmake_minimum_required(VERSION 3.22)

project(ODU2)

add_executable(ODU2 main.cpp odu_funcs.h)


set_target_properties(ODU2 PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Gauss method implementation"
)