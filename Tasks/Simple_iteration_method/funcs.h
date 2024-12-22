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
        for(size_t j = 0, j_end = n+1; j != j_end; ++j )
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

        ostream << matrix[w][n];

        ostream << std::endl;
    }

    ostream << std::endl;
}

template <typename type>
bool check_matrix_for_simple_iteration(type eps, std::vector<std::vector<type>>& matrix)
{
    size_t n = matrix.size();

    for(size_t i = 0; i < n; ++i)
    {
        if(matrix[i][i] == type())
            return false;
        type summ = type();
        for(size_t j = 0; j < n; ++j)
        {
            summ+= std::abs(matrix[i][j]);
        }

        if(std::abs(std::abs(matrix[i][i]) - summ) < eps)
        {
            return false;
        }
    }

    return true;
}

template <typename type>
std::vector<std::vector<type>> get_matrix_c_f_for_simple_iteration(std::vector<std::vector<type>>& matrix)
{
    size_t n = matrix.size();

    std::vector<std::vector<type>> result(n, std::vector<type>(n+1, type()));

    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            if(i != j)
                result[i][j] = -matrix[i][j]/matrix[i][i];
        }

        result[i][n] = matrix[i][n]/matrix[i][i];
    }

    return result;

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
std::vector<type> get_next_vector_of_x(std::vector<std::vector<type>>& matrix, std::vector<type> vec)
{
    size_t n = matrix.size();

    std::vector<type> result_vec(n, type());

    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            result_vec[i] += vec[j] * matrix[i][j];
        }

        result_vec[i] += matrix[i][n];

    }

    return result_vec;
}

template<typename type>
bool check_matrix_c(long double eps, std::vector<std::vector<type>>& matrix_c)
{




    size_t n = matrix_c.size();
    print_matrix(std::cout, n, matrix_c);
    type max = type();
    for(size_t i = 0; i < n; ++i)
    {
        type summ_of_abs = type();
        for(size_t j = 0; j < n; ++j)
        {
            summ_of_abs += std::abs(matrix_c[i][j]);
        }

        max = summ_of_abs > max ? summ_of_abs : max;
    }



    type tmp = max - type(1);

    if(std::abs(tmp) > eps && tmp > type(0))
    {
        return false;
    }

    return true;
}

template<typename type>
type get_max_diff_for_two_vectors_for_simple_iteration(long double eps, std::vector<type> first, std::vector<type> second)
{
    if(first.size() != second.size())
        throw std::runtime_error("two vectors with different size!");

    size_t n = first.size();

    type max_diff = 0.0;
    for(size_t i = 0; i < n; ++i)
    {
        max_diff = std::abs(std::abs(first[i]) - std::abs(second[i])) - max_diff > eps ? std::abs(std::abs(first[i]) - std::abs(second[i])) : max_diff;
    }

    return max_diff;

}




#endif //NUMEROLOGY_FUNCS_H
