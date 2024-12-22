//
// Created by fedor on 11.10.2024.
//
#include "c_funcs.h"

int main()
{
    long double eps = 0.0000001;
    long double x0 = 2.0;
    long double y0 = -0.733026;

    long double left = 2.0;
    long double right = 3.0;

    long double h = 0.1;

    std::vector<long double> vector_x;
    std::vector<long double> vector_y;

    vector_y.push_back(y0);

    long double beg = left;
    while(std::abs(beg - right) > eps)
    {
        vector_x.push_back(beg);
        beg += h;
    }
    vector_x.push_back(beg);

    size_t n = vector_x.size();

    for(size_t i = 1; i < n; ++i)
    {
        auto tmp = vector_y[i-1] + h * func_9_c(vector_x[i - 1], vector_y[i - 1]);
        vector_y.push_back(tmp);
    }

    std::vector<long double> vector_diff_y;

    for(size_t i = 0; i< n-1; ++i)
    {
        auto tmp = vector_y[i+1] - vector_y[i];
        vector_diff_y.push_back(tmp);
    }

    std::vector<long double> vec_truth_y;

    for(size_t i = 0; i < n; ++i)
    {
        vec_truth_y.push_back(func_9_c_truth(vector_x[i]));
    }

    std::vector<long double> vec_ksi;

    for(size_t i = 0; i < n; ++i)
    {
        vec_ksi.push_back(std::abs(vector_y[i] - vec_truth_y[i]));
    }

    print_table(vector_x,vector_y, vector_diff_y, vec_truth_y, vec_ksi);
    print_simple_table(vector_x, vector_y);

    std::cout << std::endl;



}