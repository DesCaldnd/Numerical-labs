
#ifndef NUMEROLOGY_INTEG_FUNC_H
#define NUMEROLOGY_INTEG_FUNC_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

long double func_9(long double eps, long double x)
{
    if(std::abs(x * x + 9) < eps)
        throw std::runtime_error("division by zero!");

    return x / (x * x + 9);
}

long double func_9_sec_d(long double eps, long double x)
{
    if(std::abs(x * x + 9) < eps)
        throw std::runtime_error("division by zero!");
    return (2 * x * x * x - 54 * x) / std::pow(x * x + 9, 3);
}


long double func_9_forth_d(long double eps, long double x)
{
    if(std::abs(x * x + 9) < eps)
        throw std::runtime_error("division by zero!");
    return (24 * x * x * x * x * x - 2160 * x * x * x + 9720 * x) / std::pow(x * x + 9, 5);
}

long double square_method(long double eps, long double h, long double left, long double right, long double (*func)(long double, long double))
{
    if(std::abs(left - right) < eps)
    {
        return 0.0;
    }

    long double sum = 0.0;
    long double x_cur = left+h;
    long double x_prev = left;

    while(true)
    {
        auto y = func(eps, (x_prev + x_cur)*0.5);
        sum += y;
        x_prev = x_cur;


        if(std::abs(right - x_cur) < eps)
        {
            break;
        }
        x_cur += h;
    }

    return sum*h;
}

long double print_square_method(long double eps, long double h, long double left, long double right, long double (*func)(long double, long double))
{
    std::cout << "Table for square method with h = " << h << std::endl;

	std::cout << std::string(66, '-') << std::endl;
    std::cout << std::setw(5) << "i" << " | "
              << std::setw(15) << "xi" << " | "
              << std::setw(15) << "yi" << " | "
              << std::setw(20) << "Square Method" << " | " << std::endl;

    std::cout << std::string(65, '-') << "|" << std::endl;

    long double x_cur = left;
    size_t counter = 0;
    long double res_square;

	while(true)
    {
        std::cout << std::setw(5) << counter << " | "
                  << std::setw(15) << std::fixed << std::setprecision(10) << x_cur << " | ";

        long double y = func(eps, x_cur);
        std::cout << std::setw(15) << std::fixed << std::setprecision(10) << y << " | ";

        res_square = square_method(eps, h, left, x_cur, func);
        std::cout << std::setw(20) << std::fixed << std::setprecision(10) << res_square << " | " << std::endl;

        if (std::abs(right - x_cur) < eps)
        {
            break;
        }

        x_cur += h;
        counter++;
    }

	std::cout << std::string(66, '-') << std::endl;
    std::cout << std::endl;

    return res_square;
}

long double trapezoid_method(long double eps, long double h, long double left, long double right, long double (*func)(long double, long double))
{
    if(std::abs(left - right) < eps)
    {
        return 0.0;
    }

    long double sum = 0.0;
    long double x_cur = left+h;
    long double x_prev = left;



	while(true)
    {
        auto y1 = func(eps, x_prev);
        auto y2 = func(eps, x_cur);
        sum += y1+y2;
        x_prev = x_cur;


        if(std::abs(right - x_cur) < eps)
        {
            break;
        }
        x_cur += h;
    }

    return sum*h*0.5;
}

long double print_trapezoid_method(long double eps, long double h, long double left, long double right, long double (*func)(long double, long double))
{
    std::cout << "Table for trapezoidezoid method with h = " << h << std::endl;

	std::cout << std::string(66, '-') << std::endl;
    std::cout << std::setw(5) << "i" << " | "
              << std::setw(15) << "xi" << " | "
              << std::setw(15) << "yi" << " | "
              << std::setw(20) << "trapezoid Method" << " | " << std::endl;

    std::cout << std::string(65, '-') << std::endl;

    long double x_cur = left;
    size_t counter = 0;
    long double res_trapezoid;

	while(true)
    {
        std::cout << std::setw(5) << counter << " | "
                  << std::setw(15) << std::fixed << std::setprecision(10) << x_cur << " | ";

        long double y = func(eps, x_cur);
        std::cout << std::setw(15) << std::fixed << std::setprecision(10) << y << " | ";

        res_trapezoid = trapezoid_method(eps, h, left, x_cur, func);
        std::cout << std::setw(20) << std::fixed << std::setprecision(10) << res_trapezoid << " | " << std::endl;

        if (std::abs(right - x_cur) < eps)
        {
            break;
        }

        x_cur += h;
        counter++;
    }

	std::cout << std::string(66, '-') << std::endl;
    std::cout << std::endl;

    return res_trapezoid;
}

long double Simpson_method(long double h, std::vector<long double>& vector_y) {

    size_t n = vector_y.size();

    long double sum = 0.0;


    for (size_t i = n - 1; i > 0; i -= 2) {
        sum += vector_y[i - 2] + 4 * vector_y[i - 1] + vector_y[i];
    }

    return sum * h / 3;
}

long double print_Simpson_method(long double eps, long double h, long double left, long double right, long double (*func)(long double, long double))
{
    std::cout << "Table for Simpson method with h = " << h << std::endl;

	std::cout << std::string(66, '-') << std::endl;

    std::cout << std::setw(5) << "i" << " | "
              << std::setw(15) << "xi" << " | "
              << std::setw(15) << "yi" << " | "
              << std::setw(20) << "Simpson Method" << " | " << std::endl;

    std::cout << std::string(65, '-') << "| " << std::endl;

    long double x_cur = left;
    std::vector<long double> vector_y;
    long double res_square = 0.0;


    for (size_t i = 0;; ++i)
    {
        long double y = func(eps, x_cur);
        vector_y.push_back(y);


        if (i % 2 == 0)
        {
            std::cout << std::setw(5) << i << " | "
                      << std::setw(15) << std::fixed << std::setprecision(10) << x_cur << " | "
                      << std::setw(15) << std::fixed << std::setprecision(10) << y << " | ";

            res_square = (i == 0) ? 0.0 : Simpson_method(h, vector_y);
            std::cout << std::setw(20) << std::fixed << std::setprecision(10) << res_square << " | " << std::endl;
        }


        if (std::abs(right - x_cur) < eps)
        {
            break;
        }

        x_cur += h;
    }

	std::cout << std::string(66, '-') << std::endl;
    std::cout << std::endl;

    return res_square;
}

long double get_R_for_square(long double eps, long double h, long double X0, long double X1, long double (*func)(long double, long double))
{
    return h*h*(X1-X0)*std::abs(func(eps, 1.2))/24;
}

long double get_R_for_trapezoid(long double eps, long double h, long double X0, long double X1, long double (*func)(long double, long double))
{
    return h*h*(X1-X0)*std::abs(func(eps, 1.2))/12;
}

long double get_R_for_Simpson(long double eps, long double h, long double X0, long double X1, long double (*func)(long double, long double))
{
    return h*h*h*h*(X1-X0)*std::abs(func(eps, 1.1))/180;
}

long double get_RRR_cost(long double F_h, long double F_hk, long double k, long double p)
{
    return F_h + (F_h - F_hk)/(std::pow(k, p) - 1);
}

#endif //NUMEROLOGY_INTEG_FUNC_H
