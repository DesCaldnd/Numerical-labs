


#include "funcs.h"


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Pass path to config file" << std::endl;
        return 0;
    }

    std::ifstream in(argv[1]);

    if (!in.is_open())
    {
        std::cout << "Filepath is incorrect" << std::endl;
        return 0;
    }

    std::cout << std::setprecision(6);

    size_t n;

    in >> n;

    std::vector<std::vector<long double>> matrix(n, std::vector<long double>(n+1, 0));

    if (n < 2)
    {
        std::cout << "There must be at least 2 lines" << std::endl;
        return 0;
    }

    for(size_t i = 0, end = n; i != end; ++i)
    {
        for(size_t j = 0, j_end = n+1; j != j_end; ++j )
        {
            in >> matrix[i][j];
        }
    }

    auto clone_matrix = matrix;

    auto single_matrix = get_single_matrix(n);

    auto reverse_matrix_A = get_reverse_matrix_by_Gauss(n, clone_matrix, single_matrix);

    auto [result, amount_replace] = Gauss_method(n, matrix);

    std::cout << "!!!!!!!!!" << std::endl;

    print_matrix(std::cout, n, matrix);

    std::cout << "result vector is" << std::endl;

    for(long double i : result)
    {
        std::cout << i <<std::endl;
    }

    long double diag = 1;

    for(size_t i = 0;i < n; ++i)
    {
        diag *= matrix[i][i];
    }

    std::cout << "detA is: " << std::pow(-1L, amount_replace) * diag << "\n" << std::endl;

    std::cout << "original matrix A: \n";

    print_matrix(std::cout, n, clone_matrix);

    std::cout << "reversed matrix A:\n" << std::endl;

    print_matrix(std::cout, n,  reverse_matrix_A);

    auto tmp = multiplyMatrices(n,clone_matrix, reverse_matrix_A);

    std::cout << std::fixed << std::setprecision(6) << "\ncheck:\n";

    print_matrix(std::cout, n, tmp);

    auto tmp2 = multiplyMatrices(n,reverse_matrix_A,clone_matrix );

    std::cout << std::fixed << std::setprecision(6) << "\ncheck:\n";

    print_matrix(std::cout, n, tmp2);

}


