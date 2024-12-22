
#include "integ_func.h"


int main()
{
    long double eps = 0.000001;
    long double X0 = 0;
    long double X1 = 2;

    long double h1 = 0.5;
    long double h2 = 0.25;

    long double k = 2;


    long double etalon = 0.183862;

    auto F_kh_sq = print_square_method(eps, h1, X0, X1, func_9);
    auto F_h_sq = print_square_method(eps, h2, X0, X1, func_9);
    auto F_kh_tr = print_trapezoid_method(eps, h1, X0, X1, func_9);
    auto F_h_tr = print_trapezoid_method(eps, h2, X0, X1, func_9);
    auto F_kh_par = print_Simpson_method(eps, h1, X0, X1, func_9);
    auto F_h_par = print_Simpson_method(eps, h2, X0, X1, func_9);

    std::cout << "R-square for h = 0.5 <= " << get_R_for_square(eps, h1, X0, X1, func_9_sec_d) << std::endl;
    std::cout << "R-square for h = 0.25 <= " << get_R_for_square(eps, h2, X0, X1, func_9_sec_d) << std::endl;
    std::cout << "R-trapezoid for h = 0.5 <= " << get_R_for_trapezoid(eps, h1, X0, X1, func_9_sec_d) << std::endl;
    std::cout << "R-trapezoid for h = 0.25 <= " << get_R_for_trapezoid(eps, h2, X0, X1, func_9_sec_d) << std::endl;
    std::cout << "R-Simpson for h = 0.5 <= " << get_R_for_Simpson(eps, h1, X0, X1, func_9_forth_d) << std::endl;
    std::cout << "R-Simpson for h = 0.25 <= " << get_R_for_Simpson(eps, h2, X0, X1, func_9_forth_d) << std::endl;

    std::cout <<"\n"<< std::setprecision(6);

    auto tmp1 = get_RRR_cost(F_h_sq, F_kh_sq, k, 2);
    std::cout << "\nvalue of Integral by RRR for square: " << tmp1 << std::endl;

    std::cout << "\nabsolutely diff for square : " << std::abs(etalon - tmp1) << std::endl;



    auto tmp2 = get_RRR_cost(F_h_tr, F_kh_tr, k, 2);
	
    if(std::abs(tmp2) < eps)
	{
		tmp2 = 0;
	}

    std::cout << "\nvalue of Integral by RRR for trapezoid: " << tmp2 << std::endl;
    std::cout << "\nabsolutely diff for trapezoid : " << std::abs(etalon - tmp2) << std::endl;



    auto tmp3 = get_RRR_cost(F_h_par, F_kh_par, k, 4);
    std::cout << "\nvalue of Integral by RRR for Simpson: " << tmp3 << std::endl;

    std::cout << "\nabsolutely diff for Simpson : " << std::abs(etalon - tmp3) << std::endl;
}