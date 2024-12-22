cmake_minimum_required(VERSION 3.22)

project(Thomas_Method)

add_executable(Thomas_Method main.cpp)

set_target_properties(Thomas_Method PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDART 23
        CXX_STANDART_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "Thomas method implementation"
)