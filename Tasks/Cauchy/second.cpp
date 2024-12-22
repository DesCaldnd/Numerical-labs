////
//// Created by fedor on 13.10.2024.
////


#include "c_funcs.h"


int main() {

//    long double x0 = 0.0;
//    long double y0 = 0.0;
//    long double x_end = 0.5;
//    long double h = 0.1;

    long double x0 = 2.0;
    long double y0 = -0.733026;
    long double x_end = 3.0;
    long double h = 0.1;

    //std::vector<long double> result = runge_kutta_4th_order(func_9, func_test_truth, x0, y0, x_end, h);

    std::vector<long double> result = runge_kutta_4th_order(func_9_c, func_9_c_truth, x0, y0, x_end, h);

    std::cout << std::setprecision(10);

    std::vector<long double> vector_x;
    while (std::abs(x0 - x_end) > 0.0001) {
        vector_x.push_back(x0);
        x0 += h;
    }
    vector_x.push_back(x0);

    print_simple_table(vector_x, result);

    return 0;
}

