#include <iostream>
#include <cstdlib>
#include <ratio>
#include "for_each.hpp"

typedef unsigned int uint;
typedef unsigned long long ullong;

template<uint N>
struct Fact:
std::integral_constant<ullong, N * Fact<N-1>::value>
{
};

template<>
struct Fact<0>:
std::integral_constant<ullong, 1>
{
};

template<uint N, uint K>
struct BinomCoeffNorm:
std::ratio<-Fact<N-1>::value, Fact<N-K>::value * Fact<K>::value>
{
};

template<uint N, uint K>
struct DoBernulliNum:
std::ratio_add<std::ratio_multiply<BinomCoeffNorm<N+1, K+1>,
                                   DoBernulliNum<N-K, 1>>,
               DoBernulliNum<N, K+1>>
{
};

template<uint N>
struct DoBernulliNum<N, N>:
std::ratio<-1, N+1>
{
};

template<uint N>
struct BernoulliNum:
DoBernulliNum<N, 1>
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
		long long integral = num / den;
		long long fractional = llabs(num % den);
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
	List<BernoulliNum, 0, 20> bernoulli_nums;
	bernoulli_nums.for_each(ratio_printer());
	return 0;
}
