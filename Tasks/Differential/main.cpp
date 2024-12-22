#include <ranges>
#include "diff_funcs.h"

int main()
{
    long double eps = 0.00001;

    std::vector<long double> vector_x = {-1.0, 0.0, 1.0, 2.0, 3.0};
    std::vector<long double> vector_y = {2.3562, 1.5708, 0.7854, 0.46365, 0.32175};
    long double x_star = 1.0;

    size_t n = vector_x.size();

    auto index = find_index(eps, x_star, vector_x);

    long double left , right, central, second;

	std::cout << "Output for values:" << std::endl;

	bool first = true;

	for(auto&& p : std::ranges::zip_view(vector_x, vector_y))
	{
		if (first)
		{
			first = false;
		} else
		{
			std::cout << ", ";
		}
		std::cout << "(" << std::get<0>(p) << "; " << std::get<1>(p) << ")";
	}

	std::cout << std::endl << "is:" << std::endl;

    if(index  != 0 && index != n-1)
    {
        left = left_diff(eps, index, vector_y, vector_x);
        right = right_diff(eps, index, vector_y, vector_x);
        central = central_diff(eps, index-1, x_star, vector_y, vector_x);
        second = second_diff(eps, index - 1, vector_y, vector_x);
    }
    else if(index == 0)
    {
        std::cout << "cann't calculate left diff" <<std::endl;
        right = right_diff(eps, index, vector_y, vector_x);

        central = central_diff(eps, index, x_star, vector_y, vector_x);
        second = second_diff(eps, index, vector_y, vector_x);

        std::cout << "right diff: " <<  right << std::endl;
        std::cout << "central diff: "  <<  central << std::endl;
        std::cout << "second diff: "  <<  second << std::endl;

        return 0;
    }
    else
    {
        std::cout << "cann't calculate right diff" <<std::endl;
        right = left_diff(eps, index, vector_y, vector_x);
        std::cout << "right diff: " <<  right << std::endl;
        std::cout << "cann't calculate centralt diff" <<std::endl;
        std::cout << "cann't calculate second diff" <<std::endl;
        return 0;

    }

    std::cout << std::fixed << std::setprecision(20);
    std::cout << "left diff: " <<  left << std::endl;
    std::cout << "right diff: " <<  right << std::endl;
    std::cout << "central diff: " <<  central << std::endl;
	std::cout << "central diff check: " << ((std::abs((left + right) / 2 - central) < eps) ? "true" : "false") << std::endl;
    std::cout << "second diff: "  << second << std::endl;

}