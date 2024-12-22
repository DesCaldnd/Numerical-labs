//
// Created by fedor on 30.09.2024.
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

    ld_matrix matrix(n, ld_vec(n+1, 0));

    read_matrix_from_file_with_value_vector(n, in, matrix);

    std::cout << std::setprecision(6);

    std::cout << "matrix of A and b:\n" << std::endl;

    print_matrix(std::cout, n, matrix);

    if(!check_matrix_for_simple_iteration(eps, matrix))
        throw std::logic_error("your matrix has zero-elements on the main diagonal");


    auto matrix_c_f = get_matrix_c_f_for_simple_iteration(matrix);

    std::cout << "matrix of C and F:\n" << std::endl;

    print_matrix(std::cout, n, matrix_c_f);

    ld_vec vector_result(n, 0.0);

    long double diff_prev = 0.0;
    long double diff_cur;
    size_t counter = 0;

    do{
        auto tmp = vector_result;

        vector_result = get_next_vector_of_x(matrix_c_f, vector_result);

        diff_cur = get_max_diff_for_two_vectors_for_simple_iteration(eps, vector_result, tmp);

        counter++;
    }
    while(std::abs(diff_cur - diff_prev) > eps);

    std::cout << std::setprecision(6);

    print_vector(std::cout,vector_result);

    std::cout << std::setprecision(0) << "result is:\n";

    print_vector(std::cout,vector_result);

    std::cout << "amount of calculations is: " << counter;

}