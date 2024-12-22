//
// Created by fedor on 04.10.2024.
//

#include "funcs.h"



int main()
{
    long double eps = 0.001;

    long double x_left = 0.15;
    long double x_right = 0.45;
    long double y_up = 0.45;
    long double y_down = 0.15;

    long double x_prev = (x_right + x_left)/2;
    long double y_prev = (y_up + y_down)/2;
    long double cur_x = 0, cur_y = 0;

    long double (*matrix_J[4])(long double, long double) = {dx1_f1, dx2_f1,dx1_f2, dx2_f2};
    long double (*matrix_A1[4])(long double, long double) = {f1_x1_x2, dx2_f1, f2_x1_x2, dx2_f2 };
    long double (*matrix_A2[4])(long double, long double) = {dx1_f1, f1_x1_x2, dx1_f2, f2_x1_x2};

    size_t counter = 0;

    while(get_norm(cur_x, x_prev, cur_y, y_prev) > eps)
    {
        if(counter != 0)
        {
            x_prev = cur_x;
            y_prev = cur_y;
        }

        long double det_j = det_J(matrix_J, x_prev, y_prev);
        if(std::abs(det_j) < eps)
            throw std::runtime_error("division by zero!");

        cur_x = x_prev - det_A1(matrix_A1, x_prev, y_prev)/det_j;
        cur_y = y_prev - det_A2(matrix_A2, x_prev, y_prev)/det_j;

        counter++;
        if (counter > 1000) {
            throw std::runtime_error("too many iterations, possible divergence!");
        }
    }

    std::cout << std::setprecision(10);
    std::cout << "\nNewton method:" << std::endl;
    std::cout <<"x1 = " << cur_x <<std::endl;
    std::cout <<"x2 = " << cur_y << std::endl;
    std::cout << "amount of iteration: " << counter << std::endl;
    std::cout << "is correct: "<<check_value(eps, f1_x1_x2, f2_x1_x2, cur_x, cur_y) <<std::endl;


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Simple_iteration%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    long double (*matrix_phi[4])(long double, long double) = {dx1_phi1, dx2_phi1,dx1_phi2, dx2_phi2};

    auto q = calculate_q(matrix_phi, x_right, y_up);
    if (q - 1 > eps)
        throw std::logic_error("q more 1!");

    long double beg_x = (x_right + x_left)/2;
    long double beg_y = (y_up + y_down)/2;
    long double x_cur = 0, y_cur = 0;

    size_t count = 0;

    while(((q / (1 - q)) * get_norm(x_cur, beg_x, y_cur, beg_y)) > eps)
    {
        if(count != 0)
        {
            beg_x = x_cur;
            beg_y = y_cur;
        }

        x_cur = phi1_x1_x2(beg_x, beg_y);
        y_cur = phi2_x1_x2(beg_x, beg_y);

        count++;
        if (count > 1000) {
            throw std::runtime_error("too many iterations, possible divergence!");
        }
    }

    std::cout << std::setprecision(10);
    std::cout << "\nsimple iteration method:" << std::endl;
    std::cout <<"x1 = " << x_cur <<std::endl;
    std::cout <<"x2 = " << y_cur << std::endl;
    std::cout << "amount of iteration: " << count << std::endl;
    std::cout << "is correct: "<<check_value(eps, f1_x1_x2, f2_x1_x2, x_cur, y_cur);

}