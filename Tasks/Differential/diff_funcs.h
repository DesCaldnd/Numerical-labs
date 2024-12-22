
#ifndef NUMEROLOGY_DIFF_FUNCS_H
#define NUMEROLOGY_DIFF_FUNCS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

size_t find_index(long double eps, long double x_star, std::vector<long double>& vector_x)
{
    size_t n = vector_x.size();

    for(size_t i = 0; i < n; ++i)
    {
        if(std::abs(x_star - vector_x[i]) < eps)
        {
            return i;
        }
    }

    throw std::logic_error("out of range!");
}


long double left_diff(long double eps, size_t ind, std::vector<long double>& vector_y, std::vector<long double>& vector_x)
{
    if(std::abs(vector_x[ind] - vector_x[ind-1]) < eps)
        throw std::runtime_error("division by zero!");

    return (vector_y[ind] - vector_y[ind-1])/(vector_x[ind] - vector_x[ind-1]);

}

long double right_diff(long double eps, size_t ind, std::vector<long double>& vector_y, std::vector<long double>& vector_x)
{
    if(std::abs(vector_x[ind+1] - vector_x[ind]) < eps)
        throw std::runtime_error("division by zero!");

    return (vector_y[ind+1] - vector_y[ind])/(vector_x[ind+1] - vector_x[ind]);

}

long double central_diff(long double eps, size_t ind, long double x_star, std::vector<long double>& vector_y, std::vector<long double>& vector_x)
{
    if(std::abs(vector_x[ind + 1] - vector_x[ind]) < eps || std::abs(vector_x[ind + 2] - vector_x[ind + 1]) < eps || std::abs(vector_x[ind + 2] - vector_x[ind]) < eps)
        throw std::runtime_error("division by zero!");

    return (vector_y[ind+1] - vector_y[ind])/(vector_x[ind + 1] - vector_x[ind]) + (((vector_y[ind+2] - vector_y[ind+1])/(vector_x[ind + 2] - vector_x[ind + 1])) - ((vector_y[ind+1] - vector_y[ind])/(vector_x[ind + 1] - vector_x[ind])))/(vector_x[ind + 2] - vector_x[ind]) * (2*x_star - vector_x[ind] - vector_x[ind+1]);
}

long double second_diff(long double eps, size_t ind, std::vector<long double>& vector_y, std::vector<long double>& vector_x)
{
    if(std::abs(vector_x[ind+2] - vector_x[ind+1]) < eps || std::abs(vector_x[ind+2] - vector_x[ind]) < eps || std::abs(vector_x[ind+1] - vector_x[ind]) < eps)
        throw std::runtime_error("division by zero!");

    return 2 * ((vector_y[ind+2] - vector_y[ind+1])/(vector_x[ind+2] - vector_x[ind+1]) - (vector_y[ind+1] - vector_y[ind])/(vector_x[ind+1] - vector_x[ind]))/(vector_x[ind+2] - vector_x[ind]);
}

#endif //NUMEROLOGY_DIFF_FUNCS_H
