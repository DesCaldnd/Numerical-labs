cmake_minimum_required(VERSION 3.22)
project(Tasks
        VERSION 1.0
        DESCRIPTION "Tasks implementation"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(Gauss_Method)
add_subdirectory(Thomas_Method)
add_subdirectory(Simple_iteration_method)
add_subdirectory(Zeidel_method)
add_subdirectory(Rotate_method)
add_subdirectory(Power_method)
add_subdirectory(nonlinear_equation)
add_subdirectory(nonlinear_system)
add_subdirectory(Interpolation)
add_subdirectory(Cube_spline)
add_subdirectory(MNK)
add_subdirectory(Differential)
add_subdirectory(Integy)
add_subdirectory(ODU2)
add_subdirectory(Cauchy)