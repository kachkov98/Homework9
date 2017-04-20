#include <iostream>
#include "metaprime.hpp"
#include "for_each.hpp"

bool RuntimeIsPrime (uint x)
{
	for (uint i = 3; i * i <= x; i+=2)
		if (!(x % i))
			return false;
	return true;
}

uint RuntimeNthPrime (uint n)
{
	if (n == 1)
		return 2;
	uint cur_n = 1, cur_num = 3;
	while (cur_n < n)
	{
		if (RuntimeIsPrime(cur_num))
			++cur_n;
		cur_num += 2;
	}
	return cur_num - 2;
};

struct callback
{
	static bool errors;
	template<typename MetaPrime>
	void operator() (MetaPrime meta_prime, uint i)
	{
		uint prime = RuntimeNthPrime(i);
		if (prime != MetaPrime::value)
		{
			std::cout << "Error: N = " << i << " Prime = " << prime << " Meta-prime = " << meta_prime << std::endl;
			errors = true;
		}
	};
};
bool callback::errors = false;

int main ()
{
	List<NthPrime, 1, 200> list;
	list.for_each (callback());
	if (!callback::errors)
		std::cout << "no errors" << std::endl;
	return 0;
}
