//
// Created by fedor on 11.10.2024.
//

#ifndef NUMEROLOGY_C_FUNCS_H
#define NUMEROLOGY_C_FUNCS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <functional>


long double func_9_c(long double x, long double y)
{
    return (y/x)+(1/std::log(std::abs(x)));
}

long double func_9_c_truth(long double x)
{
    return x*std::log(std::abs(std::log(std::abs(x))));
}

void print_separator(int width) {
    std::cout << std::string(width, '-') << std::endl;
}

void print_table(const std::vector<long double>& vector_x,
                 const std::vector<long double>& vector_y,
                 const std::vector<long double>& vector_diff_y,
                 const std::vector<long double>& vec_truth_y,
                 const std::vector<long double>& vec_ksi) {

    std::cout << std::fixed << std::setprecision(10);

    std::cout << std::string(86, '-') << std::endl;
    std::cout << "| " << std::setw(4) << "k"
              << " | " << std::setw(12) << "x"
              << " | " << std::setw(13) << "y"
              << " | " << std::setw(14) << "Δy_k"
              << " | " << std::setw(16) << "y_ист"
              << " | " << std::setw(13) << "ε_k" << " |" << std::endl;
    std::cout << std::string(86, '-') << std::endl;

    for (size_t i = 0; i < vector_x.size(); ++i) {
        std::cout << "| " << std::setw(4) << i
                  << " | " << std::setw(12) << vector_x[i]
                  << " | " << std::setw(13) << vector_y[i];

        if (i < vector_diff_y.size()) {
            std::cout << " | " << std::setw(13) << vector_diff_y[i];
        } else {
            std::cout << " | " << std::setw(13) << " ";
        }

        std::cout << " | " << std::setw(13) << vec_truth_y[i]
                  << " | " << std::setw(12) << vec_ksi[i] << " |" << std::endl;
    }

    std::cout << std::string(86, '-') << std::endl;
}


void print_simple_table(const std::vector<long double>& vector_x,
                        const std::vector<long double>& vector_y) {

    std::cout << std::fixed << std::setprecision(10);

    std::cout << std::string(39, '-') << std::endl;
    std::cout << "| " << std::setw(3) << "k"
              << " | " << std::setw(13) << "x_k"
              << " | " << std::setw(13) << "y_k" << " |" << std::endl;
    std::cout << std::string(39, '-')<< std::endl;

    for (size_t i = 0; i < vector_x.size(); ++i) {
        std::cout << "| " << std::setw(3) << i
                  << " | " << std::setw(13) << vector_x[i]
                  << " | " << std::setw(13) << vector_y[i] << " |" << std::endl;
    }

    std::cout << std::string(39, '-') << std::endl;
}

std::vector<long double> runge_kutta_4th_order(
        std::function<long double(long double, long double)> f,
        std::function<long double(long double)> f_truth,
        long double x0,
        long double y0,
        long double x_end,
        long double h)
{
    std::vector<long double> result;
    long double x = x0;
    long double y = y0;

    result.push_back(y);

    std::cout << std::string(132, '-') << std::endl;
    std::cout << "| " << std::setw(4) << "k"
              << " | " << std::setw(12) << "x_k"
              << " | " << std::setw(13) << "y_k_i"
              << " | " << std::setw(14) << "K_i_k"
              << " | " << std::setw(18) << "Δy_k"
              << " | " << std::setw(13) << "θ_k"
              << " | " << std::setw(21) << "y_ист"
              << " | " << std::setw(17) << "ε_k"
              << " |" << std::endl;
    std::cout << std::string(132, '-') << std::endl;

    size_t counter = 0;

    while (x < x_end) {
        long double K1 = h * f(x, y);
        long double K2 = h * f(x + 0.5 * h, y + 0.5 * K1);
        long double K3 = h * f(x + 0.5 * h, y + 0.5 * K2);
        long double K4 = h * f(x + h, y + K3);

        long double y_truth = f_truth(x);
        long double mistake = std::abs(y_truth - y);

        long double y_diff = (K1 + 2 * K2 + 2 * K3 + K4) / 6.0;
        long double teta = std::abs((K2 - K3) / (K1 - K2));

        std::cout << std::setprecision(10);
        std::cout << "| " << std::setw(4) << counter
                  << " | " << std::setw(12) << std::fixed << std::setprecision(5) << x
                  << " | " << std::setw(14) << std::fixed << std::setprecision(8) << y
                  << " | " << std::setw(14) << std::fixed << std::setprecision(8) << K1
                  << " | " << std::setw(16) << std::fixed << std::setprecision(8) << y_diff
                  << " | " << std::setw(12) << std::fixed << std::setprecision(8) << teta
                  << " | " << std::setw(18) << std::fixed << std::setprecision(8) << y_truth
                  << " | " << std::setw(16) << std::fixed << std::setprecision(8) << mistake
                  << " |" << std::endl;


        std::cout << "| " << std::setw(4) << " "
                  << " | " << std::setw(12) << x + 0.5*h
                  << " | " << std::setw(14) << y + 0.5*K1
                  << " | " << std::setw(14) << K2
                  << " | " << std::setw(16) << " "
                  << " | " << std::setw(12) << " "
                  << " | " << std::setw(18) << " "
                  << " | " << std::setw(16) << " "
                  << " |" << std::endl;

        std::cout << "| " << std::setw(4) << " "
                  << " | " << std::setw(12) << x + 0.5*h
                  << " | " << std::setw(14) << y + 0.5*K2
                  << " | " << std::setw(14) << K3
                  << " | " << std::setw(16) << " "
                  << " | " << std::setw(12) << " "
                  << " | " << std::setw(18) << " "
                  << " | " << std::setw(16) << " "
                  << " |" << std::endl;

        std::cout << "| " << std::setw(4) << " "
                  << " | " << std::setw(12) << x + h
                  << " | " << std::setw(14) << y + K3
                  << " | " << std::setw(14) << K4
                  << " | " << std::setw(16) << " "
                  << " | " << std::setw(12) << " "
                  << " | " << std::setw(18) << " "
                  << " | " << std::setw(16) << " "
                  << " |" << std::endl;

        std::cout << std::string(132, '-') << std::endl;


        y = y + y_diff;
        x = x + h;

        result.push_back(y);
        counter++;
    }


    std::cout << "| " << std::setw(4) << counter
              << " | " << std::setw(12) << std::fixed << std::setprecision(5) << x
              << " | " << std::setw(14) << std::fixed << std::setprecision(8) << y
              << " | " << std::setw(14) << " "
              << " | " << std::setw(16) << " "
              << " | " << std::setw(12) << " "
              << " | " << std::setw(18) << std::fixed << std::setprecision(8) << f_truth(x)
              << " | " << std::setw(16) << std::fixed << std::setprecision(8) << std::abs(f_truth(x) - y)
              << " |" << std::endl;
    std::cout << std::string(132, '-') << std::endl;

    return result;
}

#endif //NUMEROLOGY_C_FUNCS_H
