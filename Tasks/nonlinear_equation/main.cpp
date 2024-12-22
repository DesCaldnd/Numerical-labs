#include "funcs.h"



int main(int argc, char** argv)
{
    long double eps = 0.001;
    long double tmp1, tmp2;

    std::cout << std::setprecision(10);

    std::cout << "\ndichotomy" << std::endl;

    tmp1 = dichotomy(eps, 1.0, 2.0, func);
    std::cout << "the first value: " <<  tmp1 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp1) << std::endl;

    tmp2 = dichotomy(eps, -1.0, 0.0, func);
    std::cout << "the second value: " << tmp2<<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp2) << std::endl;

    std::cout << "\nnewton" << std::endl;

    tmp1 = newton_method(eps, 1.0, 2.0, func, d_func, d_d_func);
    std::cout << "the first value: " << tmp1 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp1) << std::endl;

    tmp2 = newton_method(eps, -1.0, 0.0, func, d_func, d_d_func);
    std::cout << "the second value: " << tmp2 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp2) << std::endl;

    std::cout << "\nsecant" << std::endl;

    tmp1 = secant_method(eps, 1.0, 2.0, func, d_d_func);
    std::cout << "the first value: " << tmp1 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp1) << std::endl;

    tmp2 = secant_method(eps, -1.0, 0.0, func, d_d_func);
    std::cout << "the second value: " << tmp2 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp2) << std::endl;

    std::cout << "\nsimple iteration" << std::endl;

    tmp1 = simple_iteration_method(eps, 1.0, 2.0, phi, d_phi);
    std::cout << "the first value: " <<  tmp1 <<std::endl;
    std::cout << "is correct: " << check_result(eps, func, tmp1) << std::endl;

    tmp2 = simple_iteration_method(eps, -1.0, 0.0, phi_2, d_phi_2);
    std::cout << "the second value: " << tmp2 <<std::endl;//нужно задать такую фи, чтобы на интересующем нас промежутке она была в промежутке таком же в каждом x
    std::cout << "is correct: " << check_result(eps, func, tmp2) << std::endl;

}