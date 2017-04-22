#include <iostream>
#include <cstdlib>
#include <ratio>
#include "for_each.hpp"

typedef unsigned int uint;
typedef unsigned long long ullong;

template<uint N, uint K>
struct BinomCoeff:
std::integral_constant<ullong, BinomCoeff<N-1, K-1>::value + BinomCoeff<N-1, K>::value>
{
};

template<uint N>
struct BinomCoeff<N, 0>:
std::integral_constant<ullong, 1>
{
};

template<uint N>
struct BinomCoeff<N, N>:
std::integral_constant<ullong, 1>
{
};

template<uint N, uint K>
struct DoBernoulliNum:
std::ratio_add<std::ratio_multiply<std::ratio<-1, N+1>,
               std::ratio_multiply<std::ratio<BinomCoeff<N+1, K+1>::value>,
                                   DoBernoulliNum<N-K, 1>>>,
               DoBernoulliNum<N, K+1>>
{
};

template<uint N>
struct DoBernoulliNum<N, N>:
std::ratio<-1, N+1>
{
};

template<uint N>
struct BernoulliNum:
DoBernoulliNum<N, 1>
{
};

template<>
struct BernoulliNum<0>:
std::ratio<1>
{
};

struct ratio_printer
{
	template <typename Ratio>
	void operator() (Ratio number, uint i)
	{
		std::cout << "B(" << i << ") = ";
		long long num = Ratio::num;
		long long den = Ratio::den;
		long long integral = llabs (num / den);
		long long fractional = llabs(num % den);
		if (num < 0)
			std::cout << '-';
		if (integral || !fractional)
			std::cout << integral << ' ';
		if (fractional)
			std::cout << fractional;
		if (den != 1)
			std::cout << '/' << den;
		std::cout << std::endl;
	};
};

int main ()
{
	List<BernoulliNum, 0, 35> bernoulli_nums;
	bernoulli_nums.for_each(ratio_printer());
	return 0;
}
