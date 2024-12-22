#ifndef NUMEROLOGY_ODU_FUNCS_H
#define NUMEROLOGY_ODU_FUNCS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <functional>

long double func_9(long double x, long double y, long double z) {
    if(std::abs(x) < 0.000001)
        throw std::runtime_error("division by zero!");
    return (1 / std::sqrt(x)) * z - (1 / (4 * x * x)) * (x + std::sqrt(x) - 8) * y;
}

long double func_9_truth(long double x) {
    return (x * x + 1 / x) * std::exp(std::sqrt(x));
}

void print_table(const std::vector<long double>& vector_x,
                 const std::vector<long double>& vector_y,
                 const std::vector<long double>& vector_z,
                 const std::vector<long double>& vector_diff_y,
                 const std::vector<long double>& vector_diff_v,
                 const std::vector<long double>& vec_truth_y,
                 const std::vector<long double>& vec_ksi)
                 {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << std::string(118, '-') << std::endl;
    std::cout << "| " << std::setw(4) << "k"
              << " | " << std::setw(12) << "x"
              << " | " << std::setw(13) << "y"
              << " | " << std::setw(13) << "z"
              << " | " << std::setw(13) << "delta_y_k"
              << " | " << std::setw(12) << "delta_z_k/func"
              << " | " << std::setw(12) << "y_truth"
              << " | " << std::setw(12) << "err_k" << " |" << std::endl;
    std::cout << std::string(118, '-') << std::endl;

    for (size_t i = 0; i < vector_x.size(); ++i)
    {
        std::cout << "| " << std::setw(4) << i
                  << " | " << std::setw(12) << vector_x[i]
                  << " | " << std::setw(13) << vector_y[i]
                  << " | " << std::setw(13) << vector_z[i];
        if (i < vector_diff_y.size())
        {
            std::cout << " | " << std::setw(13) << vector_diff_y[i];
            std::cout << " | " << std::setw(13) << vector_diff_v[i];
        }
        else
        {
            std::cout << " | " << std::setw(13) << " ";
            std::cout << " | " << std::setw(13) << " ";

        }
        std::cout << " | " << std::setw(13) << vec_truth_y[i]
                  << " | " << std::setw(12) << vec_ksi[i] << " |" << std::endl;
    }

    std::cout << std::string(118, '-') << std::endl;
}

void print_simple_table(const std::vector<long double>& vector_x,
                        const std::vector<long double>& vector_y)
                        {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << std::string(39, '-') << std::endl;
    std::cout << "| " << std::setw(3) << "k"
              << " | " << std::setw(13) << "x_k"
              << " | " << std::setw(13) << "y_k" << " |" << std::endl;
    std::cout << std::string(39, '-') << std::endl;

    for (size_t i = 0; i < vector_x.size(); ++i)
    {
        std::cout << "| " << std::setw(3) << i
                  << " | " << std::setw(13) << vector_x[i]
                  << " | " << std::setw(13) << vector_y[i] << " |" << std::endl;
    }

    std::cout << std::string(39, '-') << std::endl;
}

std::tuple<std::vector<long double>, std::vector<long double>, std::vector<long double>> solve_second_order_ode(long double left, long double right, long double h, long double y0, long double v0, long double eps, std::function<long double(long double, long double, long double)> func, std::function<long double(long double)> func_truth)
{
    std::vector<long double> vector_x;
    std::vector<long double> vector_y;
    std::vector<long double> vector_v;


    vector_y.push_back(y0);
    vector_v.push_back(v0);

    long double beg = left;
    while (std::abs(beg - right) > eps)
    {
        vector_x.push_back(beg);
        beg += h;
    }
    vector_x.push_back(beg);

    size_t n = vector_x.size();


    for (size_t i = 1; i < n; ++i)
    {
        long double x_prev = vector_x[i - 1];
        long double y_prev = vector_y[i - 1];
        long double v_prev = vector_v[i - 1];

        long double y_new = y_prev + h * v_prev;
        long double v_new = v_prev + h * func(x_prev, y_prev, v_prev);

        vector_y.push_back(y_new);
        vector_v.push_back(v_new);
    }


    std::vector<long double> vector_diff_y;
    std::vector<long double> vector_diff_v;
    std::vector<long double> vec_truth_y;
    vec_truth_y.push_back(func_truth(vector_x[0]));
    std::vector<long double> vec_ksi;
    vec_ksi.push_back(std::abs(vector_y[0] - vec_truth_y[0]));

    for (size_t i = 1; i < n; ++i)
    {
        vector_diff_y.push_back(vector_y[i] - vector_y[i - 1]);

        vector_diff_v.push_back(vector_v[i] - vector_v[i - 1]);

        vec_truth_y.push_back(func_truth(vector_x[i]));

        vec_ksi.push_back(std::abs(vector_y[i] - vec_truth_y[i]));
    }


    print_table(vector_x, vector_y, vector_v, vector_diff_y, vector_diff_v, vec_truth_y, vec_ksi);
//    print_simple_table(vector_x, vector_y);

    return {vector_x, vector_y, vector_v};
}

std::tuple<std::vector<long double>, std::vector<long double>, std::vector<long double>> solve_second_order_ode_rk4(long double left, long double right, long double h, long double y0, long double v0, long double eps, std::function<long double(long double, long double, long double)> func, std::function<long double(long double)> func_truth)//добавить std::function
{
    std::vector<long double> vector_x;
    std::vector<long double> vector_y;
    std::vector<long double> vector_v;

    vector_y.push_back(y0);
    vector_v.push_back(v0);

    long double beg = left;
    while (std::abs(beg - right) > eps)
    {
        vector_x.push_back(beg);
        beg += h;
    }
    vector_x.push_back(beg);

    size_t n = vector_x.size();

    for (size_t i = 1; i < n; ++i)
    {
        long double x_prev = vector_x[i - 1];
        long double y_prev = vector_y[i - 1];
        long double v_prev = vector_v[i - 1];


        long double k1_y = h * v_prev;
        long double k1_v = h * func(x_prev, y_prev, v_prev);

        long double k2_y = h * (v_prev + 0.5 * k1_v);
        long double k2_v = h * func(x_prev + 0.5 * h, y_prev + 0.5 * k1_y, v_prev + 0.5 * k1_v);

        long double k3_y = h * (v_prev + 0.5 * k2_v);
        long double k3_v = h * func(x_prev + 0.5 * h, y_prev + 0.5 * k2_y, v_prev + 0.5 * k2_v);

        long double k4_y = h * (v_prev + k3_v);
        long double k4_v = h * func(x_prev + h, y_prev + k3_y, v_prev + k3_v);

        long double y_new = y_prev + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6.0;
        long double v_new = v_prev + (k1_v + 2 * k2_v + 2 * k3_v + k4_v) / 6.0;

        vector_y.push_back(y_new);
        vector_v.push_back(v_new);
    }

    std::vector<long double> vector_diff_y;
    std::vector<long double> vector_diff_v;
    std::vector<long double> vec_truth_y;
    vec_truth_y.push_back(func_truth(vector_x[0]));
    std::vector<long double> vec_ksi;
    vec_ksi.push_back(std::abs(vector_y[0] - vec_truth_y[0]));

    for (size_t i = 1; i < n; ++i)
    {
        vector_diff_y.push_back(vector_y[i] - vector_y[i - 1]);

        vector_diff_v.push_back(vector_v[i] - vector_v[i - 1]);

        vec_truth_y.push_back(func_truth(vector_x[i]));

        vec_ksi.push_back(std::abs(vector_y[i] - vec_truth_y[i]));
    }

    print_table(vector_x, vector_y, vector_v, vector_diff_y, vector_diff_v, vec_truth_y, vec_ksi);
//    print_simple_table(vector_x, vector_y);

    return {vector_x, vector_y, vector_v};
}

std::tuple<std::vector<long double>, std::vector<long double>, std::vector<long double>> solve_second_order_ode_adams(long double left, long double right, long double h, long double y0, long double v0, long double eps, std::function<long double(long double, long double, long double)> func, std::function<long double(long double)> func_truth)
{
    std::vector<long double> vector_x;
    std::vector<long double> vector_y;
    std::vector<long double> vector_v;

    vector_y.push_back(y0);
    vector_v.push_back(v0);

    long double beg = left;
    while (std::abs(beg - right) > eps)
    {
        vector_x.push_back(beg);
        beg += h;
    }
    vector_x.push_back(beg);

    size_t n = vector_x.size();


    for (size_t i = 1; i < 4; ++i)
    {
        long double x_prev = vector_x[i - 1];
        long double y_prev = vector_y[i - 1];
        long double v_prev = vector_v[i - 1];

        long double k1_y = h * v_prev;
        long double k1_v = h * func(x_prev, y_prev, v_prev);

        long double k2_y = h * (v_prev + 0.5 * k1_v);
        long double k2_v = h * func(x_prev + 0.5 * h, y_prev + 0.5 * k1_y, v_prev + 0.5 * k1_v);

        long double k3_y = h * (v_prev + 0.5 * k2_v);
        long double k3_v = h * func(x_prev + 0.5 * h, y_prev + 0.5 * k2_y, v_prev + 0.5 * k2_v);

        long double k4_y = h * (v_prev + k3_v);
        long double k4_v = h * func(x_prev + h, y_prev + k3_y, v_prev + k3_v);

        long double y_new = y_prev + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6.0;
        long double v_new = v_prev + (k1_v + 2 * k2_v + 2 * k3_v + k4_v) / 6.0;

        vector_y.push_back(y_new);
        vector_v.push_back(v_new);
    }


    for (size_t i = 4; i < n; ++i)
    {
        long double f_n   = func(vector_x[i-1], vector_y[i-1], vector_v[i-1]);
        long double f_n1  = func(vector_x[i-2], vector_y[i-2], vector_v[i-2]);
        long double f_n2  = func(vector_x[i-3], vector_y[i-3], vector_v[i-3]);
        long double f_n3  = func(vector_x[i-4], vector_y[i-4], vector_v[i-4]);

        long double v_new = vector_v[i-1] + (h/24.0) * (55.0 * f_n - 59.0 * f_n1 + 37.0 * f_n2 - 9.0 * f_n3);
        long double y_new = vector_y[i-1] + (h/24.0) * (55.0 * vector_v[i-1] - 59.0 * vector_v[i-2] + 37.0 * vector_v[i-3] - 9.0 * vector_v[i-4]);

        vector_y.push_back(y_new);
        vector_v.push_back(v_new);
    }


    std::vector<long double> vector_diff_y;
    std::vector<long double> vector_diff_v;
    std::vector<long double> vec_truth_y;
    vec_truth_y.push_back(func_truth(vector_x[0]));
    std::vector<long double> vec_ksi;
    vec_ksi.push_back(std::abs(vector_y[0] - vec_truth_y[0]));

    std::vector<long double> vector_func;

    for(size_t i = 0; i < n; ++i)
    {
        vector_func.push_back(func(vector_x[i], vector_y[i], vector_v[i]));
    }

    for (size_t i = 1; i < n; ++i)
    {
        vector_diff_y.push_back(vector_y[i] - vector_y[i - 1]);
        vector_diff_v.push_back(vector_v[i] - vector_v[i - 1]);
        vec_truth_y.push_back(func_truth(vector_x[i]));
        vec_ksi.push_back(std::abs(vector_y[i] - vec_truth_y[i]));
    }

    print_table(vector_x, vector_y, vector_v, vector_diff_y, vector_func, vec_truth_y, vec_ksi);
//    print_simple_table(vector_x, vector_y);

    return {vector_x, vector_y, vector_v};
}




void print_table_with_truth_and_richardson(const std::vector<long double>& x_vals,
                                           const std::vector<long double>& y_h_vals,
                                           const std::vector<long double>& y_2h_vals,
										   const std::vector<long double>& y_truth,
                                           const std::vector<long double>& richardson_errors_y)
{
    std::cout << std::setw(10) << "x_k"
              << std::setw(15) << "y_h_k"
              << std::setw(15) << "y_2h_k"
			  << std::setw(15) << "y_truth"
              << std::setw(15) << "RRR"
              << std::endl;

    for (size_t i = 0; i < x_vals.size(); ++i)
    {
        if(i % 2 == 0)
        {
            std::cout << std::setw(10) << x_vals[i]
                      << std::setw(15) << y_h_vals[i]
                      << std::setw(15) << y_2h_vals[i/2]
					  << std::setw(15) << y_truth[i]
                      << std::setw(15) << richardson_errors_y[i/2]
                      << std::endl;
        }
        else
        {
            std::cout << std::setw(10) << x_vals[i]
                      << std::setw(15) << y_h_vals[i]
                      << std::setw(15) << " "
					  << std::setw(15) << y_truth[i]
                      << std::setw(15) << " "
                      << std::endl;
        }

    }
}

void solve_second_order_ode_with_richardson(long double left, long double right, long double h, long double y0, long double v0,
                                            long double eps, std::function<long double(long double, long double, long double)> func,
                                            std::function<long double(long double)> func_truth,
                                            std::function<std::tuple<std::vector<long double>,
                                                    std::vector<long double>,
                                                            std::vector<long double>>(long double, long double,
                                                                    long double, long double, long double,
                                                                    long double,
                                                                    std::function<long double(long double, long double, long double)>,
                                                                            std::function<long double(long double)> )> type_solving )
{

    auto [vector_x_h, vector_y_h, vector_v_h] = type_solving(left, right, h, y0, v0, eps, func, func_truth);


    auto [vector_x_2h, vector_y_2h, vector_v_2h] = type_solving(left, right, 2 * h, y0, v0, eps * 2, func, func_truth);


    size_t n = vector_x_h.size();
    size_t n_2h = vector_x_2h.size();
    if (n_2h * 2 != n+1) {
        throw std::runtime_error("Количество точек не совпадает между шагами h и 2h");
    }


    std::vector<long double> vector_richardson_error_y;
    long double p = 4.0;
    for (size_t i = 0; i < n_2h; ++i)
    {

        long double error_y = std::abs((vector_y_h[2 * i] - vector_y_2h[i]) / (std::pow(2, p) - 1));
        vector_richardson_error_y.push_back(error_y);
    }


    std::vector<long double> vector_diff_y;
    std::vector<long double> vector_diff_v;
    std::vector<long double> vec_truth_y;
    vec_truth_y.push_back(func_truth(vector_x_h[0]));
    std::vector<long double> vec_ksi;
    vec_ksi.push_back(std::abs(vector_y_h[0] - vec_truth_y[0]));

    for (size_t i = 1; i < n; ++i)
    {
        vector_diff_y.push_back(vector_y_h[i] - vector_y_h[i - 1]);
        vector_diff_v.push_back(vector_v_h[i] - vector_v_h[i - 1]);
        vec_truth_y.push_back(func_truth(vector_x_h[i]));
        vec_ksi.push_back(std::abs(vector_y_h[i] - vec_truth_y[i]));
    }


    print_table_with_truth_and_richardson(vector_x_h, vector_y_h, vector_y_2h, vec_truth_y, vector_richardson_error_y);
}

#endif //NUMEROLOGY_ODU_FUNCS_H
