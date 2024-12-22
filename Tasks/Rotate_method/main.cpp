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

    ld_matrix matrix(n, ld_vec(n, 0));

    read_matrix_from_file_with_value_vector(n, in, matrix);

    std::cout << std::setprecision(6);

    std::cout << "matrix of A and b:\n" << std::endl;

    print_matrix(std::cout, n, matrix);

    if(!check_matrix_for_rotate_method(eps, matrix))
        throw std::logic_error("your matrix isn't symmetrical");

    auto [row, col] = get_position_max(eps, matrix);

    size_t counter = 0;

    auto prev_combination_matrix = get_single_matrix<long double>(n);

    do
    {
        auto matrix_U = get_matrix_U(eps, matrix, {row, col});

        prev_combination_matrix = multiply_matrices(prev_combination_matrix, matrix_U);

        auto tr_matrix_U = transpose_matrix(matrix_U);

        auto tmp = multiply_matrices(tr_matrix_U, matrix);


        matrix = multiply_matrices(tmp, matrix_U);



        counter++;

        auto [first, second] = get_position_max(eps, matrix);
        row = first;
        col = second;
    }
    while(sqrt_sum_of_squares_below_diagonal(matrix) > eps);

    ld_vec result_vector_own_value(n, 0);

    for(size_t i = 0; i < n; ++i)
    {
        result_vector_own_value[i] = matrix[i][i];
    }

    std::cout << "result_vector_own_value:\n" << std::endl;

    print_vector(std::cout, result_vector_own_value);

    for(size_t i = 0; i < n ; ++i)
    {
        ld_vec tmp(n, 0);
        for(size_t j = 0; j < n; ++j)
        {

            tmp[j] = prev_combination_matrix[j][i];
        }

        std::cout << "own vector number " << i << " is:\n";
        print_vector(std::cout, tmp);
    }

    print_matrix(std::cout, n, prev_combination_matrix);

    if(!are_columns_orthogonal(eps, prev_combination_matrix))
        throw std::runtime_error("value of own vectors aren't ortogonal!");

    std::cout << "count iteration: " << counter+1 << std::endl;

}