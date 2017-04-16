#include <iostream>
#include <type_traits>

typedef unsigned int uint;

// Sqrt
template<uint n, uint lo = 1, uint hi = n>
struct Sqrt
{
private:
	static const uint mid = (lo + hi + 1) / 2;
public:
	static const uint value =  std::conditional<(n < mid * mid),
                                                Sqrt<n, lo, mid - 1>,
                                                Sqrt<n, mid, hi>>::type::value;
};

template<uint n, uint res>
struct Sqrt<n, res, res>:
std::integral_constant<uint, res>
{
};

// IsPrime
template<uint number, uint cur_div = 3, uint max_div = Sqrt<number>::value>
struct IsPrime:
std::integral_constant<bool, std::conditional<(cur_div > max_div),
                                              std::true_type,
                                              typename std::conditional<number % cur_div,
                                                                        IsPrime<number, cur_div + 2, max_div>,
                                                                        std::false_type>::type>::type::value>
{
};

// DoNthPrime
template<uint n, uint cur_n, uint number>
struct DoNthPrime:
std::integral_constant<uint, std::conditional <IsPrime<number>::value,
                                               DoNthPrime<n, cur_n + 1, number + 2>,
                                               DoNthPrime<n, cur_n    , number + 2>>::type::value>
{
};

template<uint n, uint number>
struct DoNthPrime<n, n, number>:
std::integral_constant<uint, number - 2>
{
};

// NthPrime
template<uint n>
struct NthPrime:
std::integral_constant<uint, DoNthPrime<n, 1, 3>::value>
{
};

template<>
struct NthPrime<0>;

template<>
struct NthPrime<1>:
std::integral_constant<uint, 2>
{
};

int main ()
{
	std::cout << NthPrime<270>::value << std::endl;
	return 0;
}
