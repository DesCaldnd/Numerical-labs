//
// Created by fedor on 03.10.2024.
//

#include "funcs.h"

using ld_matrix = std::vector<std::vector<long double>>;
using ld_vec = std::vector<long double>;

int main(int argc, char** argv)
{
    std::ifstream in(argv[1]);

    size_t n = analysis(argc, argv, in);

    long double eps;
    in >> eps;

    ld_matrix matrix(n, ld_vec(n, 0));

    read_matrix_from_file_with_value_vector(n, in, matrix);

    std::cout << std::setprecision(6);

    std::cout << "matrix of A:\n" << std::endl;

    print_matrix(std::cout, n, matrix);

    if(!check_matrix_for_rotate_method(eps, matrix))
        throw std::logic_error("your matrix isn't symmetrical");


    ld_vec y_vector(n, 1.0);


    auto y_normalize = normalize_vector(eps, y_vector);

    long double current_lambda = 1.0;

    long double prev_lambda = 0.0;

    size_t counter = 0;

    while(std::abs(current_lambda - prev_lambda) > eps)
    {
        counter++;

        prev_lambda = (counter != 1) ? current_lambda : prev_lambda;

        //нормировка

        auto z_vector = multiply_matrix_by_vector(eps, matrix, y_normalize);

        if(counter != 1)
            y_normalize = normalize_vector(eps, z_vector);

        current_lambda = z_vector[0]/y_normalize[0];

        if(counter == 1)
            y_normalize = normalize_vector(eps, z_vector);

            //base

//        auto z_vector = multiply_matrix_by_vector(eps, matrix, y_vector);
//
//        current_lambda = z_vector[0]/y_vector[0];
//
//        y_vector = z_vector;


            //скалярное произведение
//
//        auto z_vector = multiply_matrix_by_vector(eps, matrix, y_normalize);
//
//        y_normalize = normalize_vector(eps, z_vector);
//
//        current_lambda = dot_product(eps, y_normalize, multiply_matrix_by_vector(eps, matrix, y_normalize));

    }

    std::cout << "own vector" << std::endl;

    auto tmp = normalize_vector(eps, y_normalize);

    print_vector(std::cout, tmp);

    std::cout << std::setprecision(6);

    std::cout << "max by modulo lambda: "<< std::abs(current_lambda) << std::endl;

    std::cout << "amount of iteration: " << counter << std::endl;



}