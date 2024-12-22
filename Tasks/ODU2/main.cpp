#include "odu_funcs.h"

int main()
{
    long double left = 1.0;
    long double right = 2.0;
    long double h = 0.01;
    long double y0 = 2 * std::exp(1.0);
    long double v0 = 2 * std::exp(1.0);
    long double eps = 1e-6;


    std::cout << "RRR" <<std::endl;

    std::cout << "\nEuler: steps h and 2h for RRR:\n\n";

	solve_second_order_ode_with_richardson(left, right, h, y0, v0, eps, func_9, func_9_truth, solve_second_order_ode);

    std::cout << "\nRunge-Kutta: steps h and 2h for RRR:\n\n";

	solve_second_order_ode_with_richardson(left, right, h, y0, v0, eps, func_9, func_9_truth, solve_second_order_ode_rk4);

    std::cout << "\nAdams: steps h and 2h for RRR:\n\n";

	solve_second_order_ode_with_richardson(left,right, h,y0,v0,eps,func_9,func_9_truth,solve_second_order_ode_adams);
}