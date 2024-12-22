//
// Created by fedor on 09.10.2024.
//

#include "../Gauss_Method/funcs.h"


int main()
{
    std::cout << std::fixed << std::setprecision(4);
    std::vector<long double> vector_x = {-0.7, -0.4, -0.1, 0.2, 0.5, 0.8};
    std::vector<long double> vector_y = {2.3462, 1.9823, 1.671, 1.3694, 1.0472, 0.6435};

    size_t n = vector_x.size();

    auto sum_x = get_summ_vector_elems_in_degree(vector_x, 1);
    auto sum_y = get_summ_vector_elems_in_degree(vector_y, 1);
    auto sum_x_x = get_summ_vector_elems_in_degree(vector_x, 2);
    auto sum_xy = get_summ_mult_elem_from_two_vector(vector_x, vector_y);
    auto sum_x_x_x = get_summ_vector_elems_in_degree(vector_x, 3);
    auto sum_x_x_x_x = get_summ_vector_elems_in_degree(vector_x, 4);
    auto sum_x_x_y = get_sum_x_x_y(vector_x, vector_y);



    std::vector<std::vector<long double>> matrix_1 =
            {
                    {static_cast<long double>(n), sum_x, sum_y},
                    {sum_x, sum_x_x, sum_xy},
            };

    auto [vector_a_0_1, tmp] = Gauss_method(matrix_1.size(), matrix_1);


    std::cout << "vector of a0 and a1 of first nearing polynom:" << std::endl;

    print_vector(std::cout, vector_a_0_1);

    std::vector<long double> vector_F_1(n, 0);

    for(size_t i = 0; i < n; ++i)
    {
        vector_F_1[i] = get_function_1(vector_x[i], vector_a_0_1[0], vector_a_0_1[1]);
    }

    std::cout << "vector F1" << std::endl;
    print_vector(std::cout, vector_F_1);

    std::cout << "F1(x) = " << vector_F_1[0] << " + ( " << vector_F_1[1] <<" ) * x" << std::endl;

    std::cout << "sum square of mistake is: " << get_sum_square_mistake(vector_F_1, vector_y) << "\n" << std::endl;


    std::vector<std::vector<long double>> matrix_2 =
            {
                    {static_cast<long double>(n), sum_x, sum_x_x, sum_y},
                    {sum_x, sum_x_x, sum_x_x_x, sum_xy},
                    {sum_x_x, sum_x_x_x, sum_x_x_x_x, sum_x_x_y}
            };

    auto [vector_a_0_1_2, temp] = Gauss_method(matrix_2.size(), matrix_2);

    std::cout << "vector of a0, a1, a2 of second nearing polynom: " << std::endl;
    print_vector(std::cout, vector_a_0_1_2);

    std::cout << "F2(x) = " << vector_a_0_1_2[0] << "+ ( " << vector_a_0_1_2[1] <<" ) * x  + ( " << vector_a_0_1_2[2] << " ) * x^2"<< std::endl;

    std::vector<long double> vector_F_2(n, 0);

    for(size_t i = 0; i < n; ++i)
    {
        vector_F_2[i] = get_function_2(vector_x[i], vector_a_0_1_2[0], vector_a_0_1_2[1], vector_a_0_1_2[2]);
    }

    std::cout << "vector F2:" << std::endl;
    print_vector(std::cout, vector_F_2);

    std::cout << "sum square of mistake is: " << get_sum_square_mistake(vector_F_2, vector_y) << std::endl;



}