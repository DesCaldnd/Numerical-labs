//
// Created by fedor on 29.09.2024.
//

#ifndef NUMEROLOGY_FUNCS_H
#define NUMEROLOGY_FUNCS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

std::pair<std::vector<long double>, size_t> Gauss_method(size_t n, std::vector<std::vector<long double>>& matrix);
std::vector<std::vector<long double>> get_single_matrix(size_t n);
std::vector<std::vector<long double>> get_reverse_matrix_by_Gauss(size_t n, std::vector<std::vector<long double>> matrix_A, std::vector<std::vector<long double>> single_matrix);
void print_matrix(std::ostream& ostream, size_t n, std::vector<std::vector<long double>>& matrix);
std::vector<std::vector<long double>> multiplyMatrices(size_t n, const std::vector<std::vector<long double>>& A, const std::vector<std::vector<long double>>& B);


std::vector<std::vector<long double>> get_reverse_matrix_by_Gauss(size_t n, std::vector<std::vector<long double>> matrix_A, std::vector<std::vector<long double>> single_matrix)
{
    std::vector<std::vector<long double>> res(n, std::vector<long double>(n, 0));
    auto clone_matrix_A = matrix_A;

    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            clone_matrix_A[j][n] = single_matrix[j][i];
        }

        //print_matrix(std::cout, n, clone_matrix_A);
        auto [column, not_used] = Gauss_method(n, clone_matrix_A);

        for(size_t j = 0; j < n; ++j)
        {
            res[j][i] = column[j];
        }

        clone_matrix_A = matrix_A;
    }

    //print_matrix(std::cout, n, res);
    return res;

}

std::vector<std::vector<long double>> get_single_matrix(size_t n)
{
    std::vector<std::vector<long double>> res(n, std::vector<long double>(n, 0));
    for(size_t i = 0; i < n; ++i)
    {
        res[i][i] = 1;
    }

    return res;
}

std::pair<std::vector<long double>, size_t> Gauss_method(size_t n, std::vector<std::vector<long double>>& matrix)
{
    size_t amount_replace = 0;


    for(size_t i = 0; i < n; ++i)
    {
        size_t number_line_with_max_elem = i;

        for(size_t j = i; j < n; ++j) //find line with max elem
        {
            number_line_with_max_elem = std::abs(matrix[j][i]) - std::abs(matrix[number_line_with_max_elem][i]) > 0.00000001 ? j : number_line_with_max_elem;
        }

        if(number_line_with_max_elem != i)
        {
            std::swap(matrix[i], matrix[number_line_with_max_elem]);//swap with max elem
            amount_replace++;
        }



        for(size_t k = i + 1; k < n; ++k)
        {
            long double koef = -matrix[k][i]/matrix[i][i];//search koef for multiplication

            std::vector<long double> tmp_vec(n+1, 0);

            for(size_t h = 0; h < n+1; ++h)
            {
                tmp_vec[h] = koef*matrix[i][h]; //get a temporary vector
            }

            for(size_t h = 0; h < n+1; ++h)
            {
                matrix[k][h] += tmp_vec[h];//update matrix value
            }
        }

    }

    std::vector<long double> result(n);

    result[n-1] = matrix[n-1][n]/matrix[n-1][n-1];

    for(long int i = (long int)n - 2; i >= 0; i--)
    {
        long double summ = 0;
        for(size_t k = i+1; k < n; ++k)
        {
            summ += result[k]*matrix[i][k];
        }
        result[i] =  (matrix[i][n] - summ )/matrix[i][i]; //calculate vector of x;
    }

    return std::make_pair(result, amount_replace);
}

void print_matrix(std::ostream& ostream, size_t n, std::vector<std::vector<long double>>& matrix)
{
    for(size_t w = 0; w < n; ++w)
    {
        for(size_t q = 0; q < n+1; ++q )///////////////////////////// <<<<q < n+1>>>>  тут может быть неправильно, так как я сплайны делал
        {
            std::cout << matrix[w][q] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

std::vector<std::vector<long double>> multiplyMatrices(size_t n, const std::vector<std::vector<long double>>& A, const std::vector<std::vector<long double>>& B)
{


    std::vector<std::vector<long double>> result(n, std::vector<long double>(n, 0));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

long double get_h_i(size_t i, std::vector<long double>& vector_x)
{
    return vector_x[i] - vector_x[i-1];
}

template <typename type>
void print_vector(std::ostream& ostream, std::vector<type>& vector)
{
    ostream << std::setprecision(6);
    size_t n = vector.size();
    for(size_t w = 0; w < n; ++w)
    {
        ostream << vector[w] << ' ';
    }

    ostream << "\n" << std::endl;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% для сплайна %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

size_t get_index_of_vector_x(long double eps, long double x_star, std::vector<long double>& vector_x)
{
    size_t n = vector_x.size();

    for(size_t i = 1; i < n-1; ++i)
    {
        if( (std::abs(x_star - vector_x[i]) > eps) && (std::abs(vector_x[i+1] - x_star) > eps))
        {
            return i;
        }
    }

    return 0;
}

long double function_spline(long double eps, long double X, size_t i,
                            std::vector<long double>& x,
                            std::vector<long double>& a,
                            std::vector<long double>& b,
                            std::vector<long double>& c,
                            std::vector<long double>& d)
{

    for(size_t i =0 ; i < a.size(); ++i)
    {
        std::cout << a[i] << ' ';
        std::cout << b[i] << ' ';

        std::cout << c[i] << ' ';

        std::cout << d[i] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return a[i] + b[i]*(X - x[i]) + c[i]*(X - x[i])*(X - x[i]) + d[i]*(X - x[i])*(X - x[i])*(X - x[i]);
}

void check_spline_conditions(long double eps,
                             const std::vector<long double>& x,
                             const std::vector<long double>& a,
                             const std::vector<long double>& b,
                             const std::vector<long double>& c,
                             const std::vector<long double>& d)
 {
    size_t n = x.size() - 1;

    for (size_t i = 0; i < n - 1; ++i) {
        long double x_right = x[i + 1];


        long double S_i_right = a[i] + b[i] * (x_right - x[i]) + c[i] * (x_right - x[i]) * (x_right - x[i]) + d[i] * (x_right - x[i]) * (x_right - x[i]) * (x_right - x[i]);

        long double S_next_left = a[i + 1];


        long double S_i_prime_right = b[i] + 2 * c[i] * (x_right - x[i]) + 3 * d[i] * (x_right - x[i]) * (x_right - x[i]);

        long double S_next_prime_left = b[i + 1];


        long double S_i_double_prime_right = 2 * c[i] + 6 * d[i] * (x_right - x[i]);

        long double S_next_double_prime_left = 2 * c[i + 1];


        if (std::abs(S_i_right - S_next_left) > eps)
        {
            std::cerr << "Ошибка в значении функции на стыке между интервалами "
                      << i << " и " << i + 1 << ": " << S_i_right
                      << " != " << S_next_left << std::endl;
        }


        if (std::abs(S_i_prime_right - S_next_prime_left) > eps)
        {
            std::cerr << "Ошибка в первой производной на стыке между интервалами "
                      << i << " и " << i + 1 << ": " << S_i_prime_right
                      << " != " << S_next_prime_left << std::endl;
        }

        if (std::abs(S_i_double_prime_right - S_next_double_prime_left) > eps)
        {
            std::cerr << "Ошибка во второй производной на стыке между интервалами "
                      << i << " и " << i + 1 << ": " << S_i_double_prime_right
                      << " != " << S_next_double_prime_left << std::endl;
        }
    }

    std::cout << "OK" << std::endl;
}

void print_spline_polynomials(const std::vector<long double>& x,
                              const std::vector<long double>& a,
                              const std::vector<long double>& b,
                              const std::vector<long double>& c,
                              const std::vector<long double>& d)
{
    size_t n = x.size() - 1;
    std::cout << "\n\nCube splines:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cout << "S" << i << "(x) = " << a[i] << " + "
                  << b[i] << "(x - " << x[i] << ") + "
                  << c[i] << "(x - " << x[i] << ")^2 + "
                  << d[i] << "(x - " << x[i] << ")^3, "
                  << "for x in [" << x[i] << ", " << x[i + 1] << "]\n";
    }
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% для MNK %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



long double get_summ_vector_elems_in_degree(std::vector<long double>& vec, size_t degree)
{
    size_t n = vec.size();

    long double sum = 0;

    for(size_t i = 0; i < n; ++i)
    {
        long double mult = 1.0;
        for(size_t j = 0; j < degree; ++j)
        {
            mult *= vec[i];
        }
        sum += mult;
    }

    return sum;
}

long double get_summ_mult_elem_from_two_vector(std::vector<long double>& vec1, std::vector<long double>& vec2)
{
    size_t n = vec1.size();

    if(n != vec2.size())
        throw std::runtime_error("arrays diff size!");

    long double sum = 0;

    for(size_t i = 0; i < n; ++i)
    {
        sum += vec1[i]*vec2[i];
    }

    return sum;
}


long double get_sum_x_x_y(std::vector<long double>& vector_x, std::vector<long double>& vector_y)
{
    size_t n = vector_x.size();

    if(n != vector_y.size())
        throw std::runtime_error("arrays diff size!");

    long double sum = 0;

    for(size_t i = 0; i < n; ++i)
    {
        sum += vector_x[i]*vector_x[i]*vector_y[i];
    }

    return sum;
}


long double get_function_1(long double x, long double a0, long double a1)
{
    return a0 + x*a1;
}

long double get_function_2(long double x, long double a0, long double a1, long double a2)
{
    return a0 + x*a1 + x*x*a2;
}

long double get_sum_square_mistake(std::vector<long double>& vector_F, std::vector<long double>& vector_y)
{
    size_t n = vector_y.size();
    if(n != vector_F.size())
        throw std::runtime_error("diff size of vec!");

    long double sum = 0;
    for(size_t i = 0; i < n; ++i)
    {
        sum += (vector_F[i] - vector_y[i])*(vector_F[i] - vector_y[i]);
    }

    return sum;
}


#endif //NUMEROLOGY_FUNCS_H
