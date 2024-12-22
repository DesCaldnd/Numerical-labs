//
// Created by fedor on 03.10.2024.
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
void print_vector(std::ostream& ostream, std::vector<type>& vector)
{
    size_t n = vector.size();
    for(size_t w = 0; w < n; ++w)
    {
        ostream << (vector[w]) << ' ';
    }

    ostream << "\n" << std::endl;
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
std::vector<type> multiply_matrix_by_vector(long double eps, const std::vector<std::vector<type>>& matrix, const std::vector<type>& vec)
{
    size_t n = matrix.size();

    if(vec.size() != n)
        throw std::invalid_argument("size of matrix and vector is different!");

    std::vector<type> result(n, type());
    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            result[i] += matrix[i][j] * vec[j];
        }
    }

    return result;
}

template <typename type>
std::vector<type> normalize_vector(long double eps, std::vector<type>& vec)
{
    size_t n = vec.size();

    type norm_value = 0;
    for (size_t i = 0; i < n; ++i) {
        norm_value += vec[i] * vec[i];
    }

    norm_value = std::sqrt(norm_value);

    if (norm_value < eps)
        throw std::runtime_error("Невозможно нормировать нулевой вектор.");


    std::vector<type> normalized_vec(n);
    for (size_t i = 0; i < n; ++i) {
        normalized_vec[i] = vec[i] / norm_value;
    }

    return normalized_vec;
}


template <typename type>
type dot_product(type eps, const std::vector<type>& vector_a, const std::vector<type>& vector_b)
{
    if (vector_a.size() != vector_b.size())
        throw std::invalid_argument("Vectors must have the same size for dot product.");


    type result = 0;
    size_t n = vector_a.size();

    for (size_t i = 0; i < n; ++i)
    {
        result += vector_a[i] * vector_b[i];
    }

    return result;
}



#endif //NUMEROLOGY_FUNCS_H
