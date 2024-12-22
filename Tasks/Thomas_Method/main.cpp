//
// Created by Des Caldnd on 9/16/2024.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <iomanip>

using ldvec = std::vector<long double>;
using iter = ldvec::iterator;

enum class error_type
{
	c_zero, a_zero, b_small, se_err, ok
};

long double det(iter ast, iter aend, iter bst, iter pst);
error_type check(iter ast, iter aend, iter bst, iter cst);

bool ld_eq(long double a, long double b)
{
    return abs(a - b) < 0.00000001;
}

int main(int argc, char* argv[])
{
    std::vector<std::vector<double>> t, r;

//    for(auto&& col : std::ranges::zip_view(t, r))
//    {
//
//    }



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

    size_t N;

    ldvec a, b, c, d, x, p, q;

    in >> N;

    if (N < 2)
    {
        std::cout << "There must be at least 2 lines" << std::endl;
        return 0;
    }

    a.resize(N, 0);
    b.resize(N, 0);
    c.resize(N, 0);
    d.resize(N, 0);
    x.resize(N, 0);
    p.resize(N, 0);
    q.resize(N, 0);

    in >> b[0] >> c[0] >> d[0];

    for(size_t i = 1; i < N - 1; ++i)
    {
        in >> a[i] >> b[i] >> c[i] >> d[i];
    }

    in >> a[N - 1] >> b[N - 1] >> d[N - 1];

	error_type err;

    if ((err = check(a.begin(), a.end(), b.begin(), c.begin())) != error_type::ok)
    {
        std::cout << "Data could not be evaluated correctly" << std::endl;
		switch (err)
		{
			case error_type::a_zero:
				std::cout << "One or more values in A vector equals zero" << std::endl;
				break;
			case error_type::c_zero:
				std::cout << "One or more values in C vector equals zero" << std::endl;
				break;
			case error_type::b_small:
				std::cout << "One or more rows failed check: abs(b) < abs(a) + abs(c)" << std::endl;
				break;
			case error_type::se_err:
				std::cout << "First or last line has incorrect values" << std::endl;
				break;
		}
        return 0;
    }

    p[0] = -(c[0] / b[0]);
    q[0] = d[0] / b[0];

    for(size_t i = 1; i < N; ++i)
    {
        p[i] = (-c[i]) / (b[i] + a[i] * p[i - 1]);
        q[i] = (d[i]- a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
    }

//    auto it = std::ranges::find_if(p, [](long double val)
//    {
//        return abs(val) > 1;
//    });

    auto it = std::find_if(p.begin(), p.end(), [](long double val)
    {
        return std::abs(val) > 1;
    });

    if (it != p.end())
    {
        std::cout << "One or more elements of vector P evaluated out of range (-1; 1)" << std::endl;
        return 0;
    }

    x.back() = q.back();

    for (long i = N - 2; i >= 0; --i)
    {
        x[i] = p[i] * x[i + 1] + q[i];
    }

    std::cout << "Answer: " << std::endl;

//    std::ranges::for_each(x, [](long double val){
//        std::cout << val << std::endl;
//    });

    std::for_each(x.begin(), x.end(), [](long double val){
        std::cout << val << std::endl;
    });

	std::cout << "Matrix determinant: " << det(a.begin() + 1, a.end(), b.begin(), p.begin()) << std::endl;

    return 0;
}


error_type check(iter ast, iter aend, iter bst, iter cst)
{
    if(ld_eq(*cst, 0) || ld_eq(*bst, 0) || ld_eq(*(bst + std::distance(ast, aend) - 1), 0) || ld_eq(*(aend - 1), 0))
        return error_type::se_err;

	++ast;
	++bst;
	++cst;
	--aend;

    for(; ast != aend; ++ast, ++bst, ++cst)
    {
        if (abs(*bst) < abs(*ast) + abs(*cst))
            return error_type::b_small;
        if (ld_eq(*ast, 0))
            return error_type::a_zero;
		if (ld_eq(*cst, 0))
			return error_type::c_zero;
    }

    return error_type::ok;
}


long double det(iter ast, iter aend, iter bst, iter pst)
{
	long double res = *bst;
	++bst;

	for(; ast != aend; ++ast, ++bst, ++pst)
	{
		res *= *bst + *ast * *pst;
	}
	return res;
}