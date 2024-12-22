//
// Created by fedor on 04.10.2024.
//

#ifndef NUMEROLOGY_FUNCS_H
#define NUMEROLOGY_FUNCS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>

long double f1_x1_x2(long double x1, long double x2)
{
    return 4*x1 - std::cos(x2);
}

long double dx1_f1(long double x1, long double x2)
{
    return 4;
}

long double dx2_f1(long double x1, long double x2)
{
    return std::sin(x2);
}


long double f2_x1_x2(long double x1, long double x2)
{
    return 4*x2 - std::exp(x1);
}

long double dx1_f2(long double x1, long double x2)
{
    return -std::exp(x1);
}

long double dx2_f2(long double x1, long double x2)
{
    return 4;
}

long double det_J(long double (*matrix_J[])(long double, long double), long double x1, long double x2)
{
    return matrix_J[0](x1,x2)*matrix_J[3](x1,x2) - matrix_J[1](x1,x2)*matrix_J[2](x1,x2);
}

long double det_A1(long double (*matrix_A1[])(long double, long double), long double x1, long double x2)
{
    return matrix_A1[0](x1,x2)*matrix_A1[3](x1,x2) - matrix_A1[1](x1,x2)*matrix_A1[2](x1,x2);
}

long double det_A2(long double (*matrix_A2[])(long double, long double), long double x1, long double x2)
{
    return matrix_A2[0](x1,x2)*matrix_A2[3](x1,x2) - matrix_A2[1](x1,x2)*matrix_A2[2](x1,x2);
}

long double get_norm(long double cur_x, long double prev_x, long double cur_y, long double prev_y)
{
    return std::max(std::abs(cur_x - prev_x), std::abs(cur_y - prev_y));
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Simple_iteration%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

long double phi1_x1_x2(long double x1, long double x2)
{
    return 0.25*std::cos(x2);
}

long double phi2_x1_x2(long double x1, long double x2)
{
    return 0.25*std::exp(x1);
}

long double dx1_phi1(long double x1, long double x2)
{
    return 0;
}

long double dx2_phi1(long double x1, long double x2)
{
    return -0.25*std::sin(x2);
}

long double dx1_phi2(long double x1, long double x2)
{
    return 0.25*std::exp(x1);
}

long double dx2_phi2(long double x1, long double x2)
{
    return 0;
}

long double calculate_q(long double (*matrix_phi[])(long double, long double), long double x_right, long double x2_up)
{
    long double first_line = std::abs(matrix_phi[0](x_right, x2_up)) + std::abs(matrix_phi[1](x_right, x2_up));
    long double second_line = std::abs(matrix_phi[2](x_right, x2_up)) + std::abs(matrix_phi[3](x_right, x2_up));
    return std::max(first_line, second_line);
}

bool check_value(long double eps, long double (*func1)(long double, long double), long double (*func2)(long double, long double), long double x1, long double x2)
{
    return (func1(x1, x2) < 2*eps) && (func2(x1,x2) < 2*eps);
}

#endif //NUMEROLOGY_FUNCS_H
