
#ifndef NUMEROLOGY_FUNCS_H
#define NUMEROLOGY_FUNCS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>

long long factorial(int x)
{
    if(x == 0)
        return 1;

    return x*factorial(x-1);
}

long double func(long double x)
{
    return std::acos(x);
}

long double func_dddd(long double x)
{
    return -(6 * std::pow(x, 7) - 3 * std::pow(x, 5) - 12 * x * x * x + 9 * x) / (std::sqrt(1- x * x) * std::pow(1 - x * x, 5));
}

long double get_multiplication_of_x_star(std::vector<long double>& vector_x_star)
{
    size_t n = vector_x_star.size();
    long double result = 1.0;

    for(size_t i = 0; i < n; ++i)
    {
        result *= vector_x_star[i];
    }

    return std::abs(result);
}

long double get_d_w(long double eps, std::vector<long double>& vector_x, long double x)
{
    size_t n = vector_x.size();
    long double result = 1.0l;


    for(size_t i = 0; i < n; ++i)
    {
        if(std::abs(x - vector_x[i]) < eps)
            continue;

        long double tmp = x - vector_x[i];
        result *= tmp;
    }

    return result;
}

std::string generation_small_expr(size_t position, std::vector<long double>& vector_x)
{
    size_t n = vector_x.size();
    std::string result;

    for(size_t i = 0; i < n; ++i)
    {
        if(i ==position)
            continue;

        result += "(x - " + std::to_string(vector_x[i]) + ")";
    }

    return result;
}

std::string generation_L_x_string(long double eps, std::vector<long double>& vector_x, std::vector<long double>& vector_f)
{
    size_t n = vector_x.size();
    std::string result;

    for(size_t i = 0; i < n; ++i)
    {
        if(std::abs(vector_f[i]) < eps)
            continue;

        if(i != n-1)
        {
            result += std::to_string(vector_f[i]) + generation_small_expr(i, vector_x)  + " + ";
        }
        else
        {
            result += std::to_string(vector_f[i]) + generation_small_expr(i, vector_x);
        }

    }

    return result;
}

long double get_value_brackets(size_t pos, long double x_value, std::vector<long double>& vector_x)
{
    size_t n = vector_x.size();
    long double res = 1.0;

    for(size_t i = 0; i < n; ++i)
    {
        if(i == pos)
            continue;

        res *= (x_value - vector_x[i]);
    }

    return res;
}


long double get_value_L(long double eps, long double x_value, std::vector<long double>& vector_x, std::vector<long double>& vector_f)
{
    size_t n = vector_x.size();
    long double result = 0.0;

    for(size_t i = 0; i < n; ++i)
    {
        result += vector_f[i] * get_value_brackets(i, x_value, vector_x);
    }

    return result;
}


std::vector<std::vector<long double>> compute_all_divided_differences(const std::vector<long double>& x_vals, std::vector<long double>& f_vals, long double eps)
{
    size_t n = f_vals.size();

    std::vector<std::vector<long double>> divided_diffs(n, std::vector<long double>(n, 0));


    for (size_t i = 0; i < n; ++i)
    {
        divided_diffs[i][0] = f_vals[i];
    }

    for (size_t order = 1; order < n; ++order)//тупая генерация следующего столбца на основе предыдущего
    {
        for (size_t i = 0; i < n - order; ++i)
        {
            if (std::abs(x_vals[i] - x_vals[i + order]) < eps)
            {
                throw std::runtime_error("division by zero between x[" + std::to_string(i) + "] and x[" + std::to_string(i + order) + "]");
            }
            divided_diffs[i][order] = (divided_diffs[i][order - 1] - divided_diffs[i + 1][order - 1]) / (x_vals[i] - x_vals[i + order]);
        }
    }

    return divided_diffs;
}

long double get_polynom_newton(long double x_star, const std::vector<long double>& x_vals, const std::vector<std::vector<long double>>& divided_diffs)
{
    long double result = divided_diffs[0][0];
    long double term = 1;

    for (size_t i = 1; i < divided_diffs.size(); ++i)
    {
        term *= (x_star - x_vals[i - 1]);
        result += divided_diffs[0][i] * term;
    }

    return result;
}

std::string get_polynom_newton_str(const std::vector<long double>& x_vals, const std::vector<std::vector<long double>>& divided_diffs)
{
    std::ostringstream equation;

    equation << divided_diffs[0][0];

    long double term = 1;

    for (size_t i = 1; i < divided_diffs.size(); ++i)
    {
        equation << " + (" << divided_diffs[0][i] << ")";

        for (size_t j = 0; j < i; ++j)
        {
            equation << "(x - " << x_vals[j] << ")";
        }
    }

    return equation.str();
}

#endif //NUMEROLOGY_FUNCS_H
