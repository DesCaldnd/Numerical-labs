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




long double find_max_abs_value(long double left, long double right, long double eps, long double (*func)(long double, long double)) {
    if (left >= right)
    {
        throw std::invalid_argument("Left boundary must be less than right boundary.");
    }

    long double max_value = 0.0;

    for (long double x = left; x <= right; x += eps) {
        long double current_value = std::abs(func(eps, x));

        if (current_value > max_value) {
            max_value = current_value;
        }
    }

    return max_value;
}


long double simple_iteration_method(long double eps, long double left, long double right, long double (*phi)(long double, long double),
                                    long double (*d_phi)(long double, long double))
    {
    long double x = (left + right)/2;
    long double prev_x;
    long double q;
    size_t counter = 0;

    do {

        q = std::abs(d_phi(eps, x));//проверка условия сходимости, так как производная должна быть по модулю быть меньше 1 в любой точке промежутка
        if (q >= 1.0) {
            throw std::runtime_error("condition false: |phi'(x)| >= 1 FOR SOME x");//пытался решить этот момент commit equation done 4.10.24 ~ 21:25
        }

        prev_x = x;
        x = phi(eps, x);// x = phi(prev_x)
        counter++;

        if (counter > 1000) {
            throw std::runtime_error("method is diverged for interval between " + std::to_string(left) + "and " + std::to_string(right));
        }
    } while ((q/(1-q))*std::abs(x - prev_x) > eps);


    return x;
}


long double secant_method(long double eps, long double left, long double right,
                          long double (*func)(long double, long double),
                          long double (*second_d)(long double, long double))
{
    if(std::abs(left - right) < eps)
        throw std::logic_error("left and right are too close!");

    long double initial;
    long double second_initial;

    long double f_left = func(eps, left);
    long double f_double_left = second_d(eps, left);

    long double f_right = func(eps, right);
    long double f_double_right = second_d(eps, right);


    if (f_left * f_double_left > 0)//начальное значение берется там, где функция и ее вторая производная имеют один и тот же знак
    {
        initial = left;
        second_initial = initial + 0.5*eps; // второе начальное значение берем близко к первому, стараемся чтобы оно было между корнем и первым значением
    }
    else if (f_right * f_double_right > 0)
    {
        initial = right;
        second_initial = initial - 0.5*eps;
    }
    else
    {
        initial = (left + right) / 2;
        second_initial = initial + 0.5*eps;
    }


    long double x_prev = initial;
    long double x_curr = second_initial;

    long double x_next;
    long double f_x_prev, f_x_curr;

    size_t iteration_counter = 0;

    do
    {
        iteration_counter++;

        f_x_prev = func(eps, x_prev);
        f_x_curr = func(eps, x_curr);

        if (std::abs(f_x_curr - f_x_prev) < eps)
            throw std::runtime_error("Division by zero in secant method!");


        x_next = x_curr - f_x_curr * (x_curr - x_prev) / (f_x_curr - f_x_prev);//тут главный прикол, что без производной самой делаем, а чисто по определению


        x_prev = x_curr;
        x_curr = x_next;

    } while (std::abs(x_curr - x_prev) > eps && iteration_counter < 1000);

    if (iteration_counter >= 1000)
        throw std::runtime_error("Secant method did not converge!");

    return x_next;
}



long double newton_method(long double eps, long double left, long double right,
                                             long double (*func)(long double, long double),
                                             long double (*first_d)(long double, long double),
                                             long double (*second_d)(long double, long double))
{

    long double initial;

    long double f_left = func(eps, left);
    long double f_double_left = second_d(eps, left);

    long double f_right = func(eps, right);
    long double f_double_right = second_d(eps, right);


    if (f_left * f_double_left > 0)//начальное значение берется там, где функция и ее вторая производная имеют один и тот же знак
    {
        initial = left;
    }
    else if (f_right * f_double_right > 0)
    {
        initial = right;
    }
    else
    {
        initial = (left + right) / 2;//иначе берем срединное значение
    }

    long double x = initial;
    long double prev_x;
    long double f_x;
    long double d_f_x;

    do
    {

        prev_x = x;

        f_x = func(eps, x);

        d_f_x = first_d(eps, x);

        if (std::abs(d_f_x) < eps)
            throw std::runtime_error("division by zero!");

        x = x - f_x / d_f_x;
    }
    while (std::abs(prev_x - x) > eps);

    return x;
}



long double dichotomy(long double eps, long double left, long double right, long double (*func)(long double,long double))
{
    long double f_left = func(eps, left);
    long double f_right = func(eps, right);

    if(f_left * f_right > 0)
        throw std::logic_error("the same sign!");


    while(std::abs(right - left) > eps)
    {
        long double mid = (left + right)/2;
        long double f_mid = func(eps, mid);

        if(std::abs(f_mid) < eps)
        {
            return mid;
        }
        else if(f_left * f_mid < 0)//смещаемся так, чтобы на концах отрезка были разные знаки
        {
            right = mid;
            f_right = f_mid;
        }
        else
        {
            left = mid;
            f_left = f_mid;
        }

    }

    return (left+right)/2;//если так и не попали в ответ, то возвращаем середину финального отрезка
}

bool check_result(long double eps, long double (*func)(long double, long double), long double x)
{
    return std::abs(func(eps, x)) < 2.15*eps;
}


long double func(long double eps, long double x)
{
    return x * x * x + x * x - 2 * x - 1;
}

long double d_func(long double eps, long double x)
{
    return 3 * x * x + 2 * x - 2;
}

long double d_d_func(long double eps, long double x)
{
    return 6 * x + 2;
}

long double phi(long double eps, long double x)
{

    return std::cbrt(-x * x + 2 * x + 1);
}

long double d_phi(long double eps, long double x)
{
        return (-2 * x + 2) / (3 * std::cbrt(std::pow(-x * x + 2 * x + 1, 2)));
}

long double phi_2(long double eps, long double x)
{
    return std::sqrt(-x * x * x + 2 * x - 1);
}



long double d_phi_2(long double eps, long double x)
{
    return (-3 * x * x + 2) / (2 * std::sqrt(- x * x * x + 2 * x - 1));
}




#endif //NUMEROLOGY_FUNCS_H
