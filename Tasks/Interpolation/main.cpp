//
// Created by fedor on 07.10.2024.
//

#include "funcs.h"



int main()
{
    size_t n = 4;
    long double eps = 0.000001;
    long double x_star = 0.1;//точка, в которой нужно произвести расчет

    std::vector<long double> vector_x_1 = {-0.4, -0.1, 0.2, 0.5};//начальные точки
    std::vector<long double> vector_x_2 = {-0.4, 0, 0.2, 0.5};

    std::vector<long double> vector_fi_div_w_1(n, 0);
    std::vector<long double> vector_fi_div_w_2(n, 0);
    std::vector<long double> vector_x_star(n, 0);

    for(size_t i = 0; i < n; ++i)
    {
        long double y_i_1 = func(vector_x_1[i]);//вычисление функции в точке
        long double y_i_2 = func(vector_x_2[i]);
        long double d_w_i_1 = get_d_w(eps, vector_x_1, vector_x_1[i]); //вычисление производной омеги в точке
        long double d_w_i_2 = get_d_w(eps, vector_x_2, vector_x_2[i]);


        if(std::abs(d_w_i_1) < eps)
            throw std::runtime_error("division by zero!");

        vector_fi_div_w_1[i] = y_i_1/d_w_i_1; // вычисление fi/d_wi
        vector_fi_div_w_2[i] = y_i_2/d_w_i_2;
        vector_x_star[i] = x_star - vector_x_1[i];
    }

    std::cout << "Inter by Lagrange:\n";
    std::cout << generation_L_x_string(eps, vector_x_1, vector_fi_div_w_1) <<std::endl;//вывод самого полинома как он выглядит

    std::cout << "the value of L by own\n";
    auto tmp1 = get_value_L(eps, x_star, vector_x_1, vector_fi_div_w_1); //подсчет полинома
    std::cout << tmp1 <<std::endl;

    std::cout << "the value of L by func\n";
    auto tmp2 = func(x_star); // вычисление функции библиотечными функциями
    std::cout <<  tmp2 << std::endl;

    std::cout << "absolutely: \n";
    std::cout << std::abs(tmp1 - tmp2) << std::endl; // находим разницу

    std::cout << "cost of interpolation is\n";
    std::cout << func_dddd(0.1) / factorial(4) * get_multiplication_of_x_star(vector_x_star); // сравнение с теоремой 3.9

    std::cout << "\n\n\nInter by Lagrange:\n";
    std::cout << generation_L_x_string(eps, vector_x_2, vector_fi_div_w_2) <<std::endl;

    std::cout << "the value of L by own\n";
    auto tmp3 = get_value_L(eps, x_star, vector_x_2, vector_fi_div_w_2);
    std::cout << tmp3 <<std::endl;

    std::cout << "the value of L by func\n";
    auto tmp4 = func(x_star);
    std::cout <<  tmp4 << std::endl;

    std::cout << "absolutely: \n";
    std::cout << std::abs(tmp3 - tmp4) << std::endl;

    std::cout << "cost of interpolation is\n";
    std::cout << func_dddd(0.05) / factorial(4) * get_multiplication_of_x_star(vector_x_star);//вблизи 0 функция ведет ссебя нестабильно,
                                                                                                                //точки 0,1 или 0.05 находятся ближе к интервалу, где
                                                                                                                //функция ведет себя более стабильно


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Newton%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



//    std::vector<long double> newton_vec_f_i_1(n, 0);//первая версия - тупо закоденный алгоритм
//    std::vector<long double> newton_vec_f_i_2(n, 0);
//
//    for(size_t i = 0; i < n; ++i)
//    {
//        newton_vec_f_i_1[i] = func_18(vector_x_1[i]);
//        newton_vec_f_i_2[i] = func_18(vector_x_2[i]);
//    }
//
//    std::vector<long double> newton_vec_f_i_i_1(n-1, 0);
//    std::vector<long double> newton_vec_f_i_i_2(n-1, 0);
//
//    for(size_t i = 0; i < n-1; ++i)
//    {
//        if(std::abs(vector_x_1[i] - vector_x_1[i+1]) < eps || std::abs(vector_x_2[i] - vector_x_2[i+1]) < eps)
//            throw std::runtime_error("division by zero!");
//        newton_vec_f_i_i_1[i] = (newton_vec_f_i_1[i] - newton_vec_f_i_1[i+1]) / (vector_x_1[i] - vector_x_1[i+1]);
//        newton_vec_f_i_i_2[i] = (newton_vec_f_i_2[i] - newton_vec_f_i_2[i+1]) / (vector_x_2[i] - vector_x_2[i+1]);
//    }
//
//    std::vector<long double> newton_vec_f_i_i_i_1(n-2, 0);
//    std::vector<long double> newton_vec_f_i_i_i_2(n-2, 0);
//
//    for(size_t i = 0; i < n - 2; ++i)
//    {
//        if(std::abs(vector_x_1[i] - vector_x_1[i+2]) < eps || std::abs(vector_x_2[i] - vector_x_2[i+2]) < eps)
//            throw std::runtime_error("division by zero!");
//
//        newton_vec_f_i_i_i_1[i] = (newton_vec_f_i_i_1[i] - newton_vec_f_i_i_1[i+1])/(vector_x_1[i] - vector_x_1[i+2]);
//        newton_vec_f_i_i_i_2[i] = (newton_vec_f_i_i_2[i] - newton_vec_f_i_i_2[i+1])/(vector_x_2[i] - vector_x_2[i+2]);
//    }
//
//    if(std::abs(vector_x_1[0] - vector_x_1[3]) < eps || std::abs(vector_x_2[0] - vector_x_2[3]) < eps)
//        throw std::runtime_error("division by zero!");
//    long double i_i_i_i_1 = (newton_vec_f_i_i_i_1[0] - newton_vec_f_i_i_i_1[1])/ (vector_x_1[0] - vector_x_1[3]);
//    long double i_i_i_i_2 = (newton_vec_f_i_i_i_2[0] - newton_vec_f_i_i_i_2[1])/ (vector_x_2[0] - vector_x_2[3]);
//
//    long double result_1 =  get_polynom_newton(x_star, vector_x_1, newton_vec_f_i_i_1[0], newton_vec_f_i_i_i_1[0], i_i_i_i_1);
//    long double result_2 =  get_polynom_newton(x_star, vector_x_2, newton_vec_f_i_i_2[0], newton_vec_f_i_i_i_2[0], i_i_i_i_2);
//
//
//    std::cout << "\n\n" << result_1 << std::endl;
//    std::cout << "\n\n" << result_2 << std::endl;


    std::cout << "\n\n\nNEWTON" << std::endl;



    std::vector<long double> newton_vec_f_i_1(n, 0);
    std::vector<long double> newton_vec_f_i_2(n, 0);


    for (size_t i = 0; i < n; ++i)
    {
        newton_vec_f_i_1[i] = func(vector_x_1[i]);// вычисление f_i
        newton_vec_f_i_2[i] = func(vector_x_2[i]);
    }


    std::vector<std::vector<long double>> divided_diffs_1 = compute_all_divided_differences(vector_x_1, newton_vec_f_i_1, eps);//сбор треугольной матрицы значений полиномов
    std::vector<std::vector<long double>> divided_diffs_2 = compute_all_divided_differences(vector_x_2, newton_vec_f_i_2, eps);


    long double result_1 = get_polynom_newton(x_star, vector_x_1, divided_diffs_1);//вычисление результа полинома от функции --> достаточно брать только коэффициенты первой строки матрицы
    long double result_2 = get_polynom_newton(x_star, vector_x_2, divided_diffs_2);


    std::cout << "\n\n\nInter by Mewton:\n";

    std::cout << get_polynom_newton_str(vector_x_1, divided_diffs_1);//записать полином в виде строки как в Лагранже

    std::cout << "\n\nResult 1 by polynom: " << result_1 << std::endl;

    auto var1 = func(x_star);

    std::cout << "\n\nResult 1 by func: " << var1 << std::endl;

    std::cout << "\nabsolutely: "<< std::abs(result_1 - var1) << std::endl;

    std::cout << "cost of interpolation is\n";

    std::cout << func_dddd(0.1) / factorial(4) * get_multiplication_of_x_star(vector_x_star);// оценка погрешности по теореме 3.9



    std::cout << "\n\n\nInter by Mewton:\n";

    std::cout << get_polynom_newton_str(vector_x_2, divided_diffs_2);

    std::cout << "\n\nResult 2: " << result_2 << std::endl;

    auto var2 = func(x_star);

    std::cout << "\n\nResult 1 by func: " << var2 << std::endl;

    std::cout << "\nabsolutely: "<< std::abs(result_2 - var2) << std::endl;

    std::cout << "cost of interpolation is\n";

    std::cout << func_dddd(0.1) / factorial(4) * get_multiplication_of_x_star(vector_x_star);

}





