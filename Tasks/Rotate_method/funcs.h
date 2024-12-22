//
// Created by fedor on 30.09.2024.
//

#ifndef NUMEROLOGY_FUNCS_H
#define NUMEROLOGY_FUNCS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>


size_t analysis(int argc, char** argv, std::ifstream & istream)
{
    if (argc < 2)
        throw std::logic_error("Pass path to config file");

    if (!istream.is_open())
        throw std::runtime_error("cannot open file");

    size_t n;

    istream >> n;

    if (n < 2)
        throw std::logic_error("There must be at least 2 lines");

    return n;
}

template <typename vec_type>
void read_matrix_from_file_with_value_vector(size_t n, std::ifstream& in ,std::vector<std::vector<vec_type>>& matrix)
{
    for(size_t i = 0, end = n; i != end; ++i)
    {
        for(size_t j = 0, j_end = n; j != j_end; ++j )
        {
            in >> matrix[i][j];
        }
    }
}

template <typename vec_type>
void print_matrix(std::ostream& ostream, size_t n, std::vector<std::vector<vec_type>>& matrix)
{
    for(size_t w = 0; w < n; ++w)
    {
        for(size_t q = 0; q < n; ++q )
        {
            ostream << matrix[w][q] << ' ';
        }

        ostream << std::endl;
    }

    ostream << std::endl;
}

template <typename type>
bool check_matrix_for_rotate_method(type eps, std::vector<std::vector<type>>& matrix)//симметрическая матрица должна быть
{
    size_t n = matrix.size();

    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j =0; j < n; ++j)
        {
            if(std::abs(std::abs(matrix[i][j]) - std::abs(matrix[j][i])) > eps)
            {
                return false;
            }
        }
    }

    return true;
}



template <typename type>
void print_vector(std::ostream& ostream, std::vector<type>& vector)
{
    size_t n = vector.size();
    for(size_t w = 0; w < n; ++w)
    {
        ostream << vector[w] << ' ';
    }

    ostream << "\n" << std::endl;
}





template <typename type>
std::pair<size_t, size_t> get_position_max(long double eps, const std::vector<std::vector<type>>& matrix)
{
    size_t n = matrix.size();
    std::pair<size_t, size_t> result{0, 1};

    type max = matrix[0][1];

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            if (std::abs(matrix[i][j]) > std::abs(max) + eps)
            {
                max = matrix[i][j];
                result.first = i;
                result.second = j;
            }
        }
    }

    return result;
}




template <typename type>
std::vector<std::vector<type>> get_matrix_U(long double eps, std::vector<std::vector<type>>& matrix, std::pair<size_t, size_t>  pair)
{
    size_t n = matrix.size();

    std::vector<std::vector<type>> matrix_U(n, std::vector<type>(n, type()));

    for(size_t i = 0; i < n; ++i)
        matrix_U[i][i] = type(1);

    type low_diag = matrix[pair.second][pair.second];//ajj
    type high_diag = matrix[pair.first][pair.first];//aii

    type phi = type();

    if(std::abs(low_diag - high_diag) < eps)
    {
        phi = std::acos(-1)/4;//Pi = arccos(-1);
    }
    else
    {
        phi = 0.5 * std::atan(2*matrix[pair.first][pair.second]/(high_diag - low_diag));
    }


    type sin_phi = std::sin(phi);
    type cos_phi = std::cos(phi);

    matrix_U[pair.first][pair.second] = -sin_phi;
    matrix_U[pair.second][pair.first] = sin_phi;
    matrix_U[pair.first][pair.first] = cos_phi;
    matrix_U[pair.second][pair.second] = cos_phi;

    return matrix_U;
}

template <typename type>
std::vector<std::vector<type>> transpose_matrix(const std::vector<std::vector<type>>& matrix_U)
{
    size_t n = matrix_U.size();


    std::vector<std::vector<type>> transposed_matrix_U(n, std::vector<type>(n, type()));


    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            transposed_matrix_U[j][i] = matrix_U[i][j];
        }
    }

    return transposed_matrix_U;
}


template <typename type>
std::vector<std::vector<type>> multiply_matrices(const std::vector<std::vector<type>>& matrix_A, const std::vector<std::vector<type>>& matrix_B)
{
    size_t n = matrix_A.size();
    size_t m = matrix_B[0].size();
    size_t common_dim = matrix_A[0].size();


    std::vector<std::vector<type>> result_matrix(n, std::vector<type>(m, type()));


    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            for (size_t k = 0; k < common_dim; ++k)
            {
                result_matrix[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }

    return result_matrix;
}

template <typename type>
type sqrt_sum_of_squares_below_diagonal(const std::vector<std::vector<type>>& matrix)
{
    size_t n = matrix.size();
    type sum = type();

    for (size_t i = 1; i < n; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            sum += matrix[i][j] * matrix[i][j];
        }
    }

    return std::sqrt(sum);
}

template <typename type>
std::vector<std::vector<type>> get_single_matrix(size_t n)
{
    std::vector<std::vector<type>> res(n, std::vector<type>(n, type()));
    for(size_t i = 0; i < n; ++i)
    {
        res[i][i] = type(1);
    }

    return res;
}

template <typename type>
bool are_columns_orthogonal(long double eps, const std::vector<std::vector<type>>& matrix)
{
    size_t n = matrix.size();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            type dot_product = type();

            for (size_t k = 0; k < n; ++k)
            {
                dot_product += matrix[k][i] * matrix[k][j];
            }

            if (std::abs(dot_product) > eps)
            {
                return false;
            }
        }
    }

    return true;
}




#endif //NUMEROLOGY_FUNCS_H
