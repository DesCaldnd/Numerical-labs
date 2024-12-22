#include "../Gauss_Method/funcs.h"


int main()
{
    long double eps = 0.00001;
    size_t n = 5;
    std::vector<long double> vector_x = {-0.4, -0.1, 0.2, 0.5, 0.8};
    std::vector<long double> vector_f = {1.9823, 1.6710, 1.3694, 1.0472, 0.64350};
    long double x_star = 0.1;

    std::vector<long double> vector_a(n-1, 0);

    for(size_t i = 1; i < n; ++i)       //заполнение массива a
    {
        vector_a[i-1] = vector_f[i-1];
    }




    std::vector<std::vector<long double>> matrix(n-2, std::vector<long double>(n, 0));

    for(size_t i = 2; i < n; ++i)                           //генерация матрицы в соответствии с условием генерации всех ее значений, но эти условия избыточны!
    {
        matrix[i-2][i-2] = get_h_i(i-1, vector_x);

        matrix[i-2][i-1] = 2*(get_h_i(i-1, vector_x) + get_h_i(i, vector_x));

        matrix[i - 2][i] = get_h_i(i, vector_x);

        matrix[i-2][n-1] = 3 * ((vector_f[i] -  vector_f[i-1])/ get_h_i(i, vector_x) - (vector_f[i-1] -  vector_f[i-2])/ get_h_i(i-1, vector_x));

        matrix[i-2][0] = 0;
    }

    //print_matrix(std::cout, n-2, matrix);



    std::vector<std::vector<long double>> final_matrix(n-2, std::vector<long double>(n-1, 0));

    for(size_t i = 0; i < n-2; ++i)// так как матрица выше избыточна, то можно её сжать до трехдиагональной, вычеркнув первую строку и первый столбец (это здесь и делаю)
    {
        for(size_t j = 1; j < n-1; ++j)
        {
            final_matrix[i][j-1] = matrix[i][j];
        }
        final_matrix[i][n-2] = matrix[i][n-1];
    }

    //print_matrix(std::cout, n-2, final_matrix);


    auto [vector_c_tmp, tmp] = Gauss_method(n-2, final_matrix);//получилась матрица, которую можно спокойно посчитать методом реализованным ранее (Гаусс или прогонка)

    //print_vector(std::cout, vector_c_tmp);

    std::vector<long double> vector_c(n-1, 0);

    for(size_t i = 1; i < n-1; ++i)//настоящий вектор С - тот, у которого первый элемент 0
    {
        vector_c[i] = vector_c_tmp[i-1];
    }

    //print_vector(std::cout, vector_c);


    std::vector<long double> vector_b(n-1, 0);//подсчет вектора B с учетом того, что мы знаем вектор С(сложные размышления тут были под Крылова)

    for(size_t i = 0; i < n-2; ++i)
    {
        vector_b[i] = (vector_f[i+1] - vector_f[i])/get_h_i(i+1, vector_x) - 1.0/3*(get_h_i(i+1, vector_x)*(vector_c[i+1] + 2*vector_c[i]));
    }
    vector_b[n-2] = (vector_f[n-1] - vector_f[n-2])/ get_h_i(n-1, vector_x) - 2.0/3*(get_h_i(n-1, vector_x)*(vector_c[n-2]));

    //print_vector(std::cout, vector_b);



    std::vector<long double> vector_d(n-1, 0);

    for(size_t i = 0; i < n-2; ++i) //аналогичный способ посчитать вектор D
    {
        vector_d[i] = (vector_c[i+1] - vector_c[i])/(3* get_h_i(i+1, vector_x));
    }
    vector_d[n-2] = -vector_c[n-2] / (3* get_h_i(n-1, vector_x));

    //print_vector(std::cout, vector_d);

    auto index = get_index_of_vector_x(eps, x_star, vector_x);//поиск индекса вхождения требуемого x*
    if(index == 0)
        throw std::runtime_error("out of range vector_x!");

    check_spline_conditions(eps, vector_x, vector_a, vector_b, vector_c, vector_d);

    std::cout << "answer: \n"<< function_spline(eps, x_star, index, vector_x, vector_a, vector_b, vector_c, vector_d);


    print_spline_polynomials(vector_x, vector_a, vector_b, vector_c, vector_d);


}
