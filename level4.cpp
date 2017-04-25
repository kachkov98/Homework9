#include <type_traits>
#include <iterator>
#include <iostream>
#include <vector>
#include <cstring>

struct NonTriviallyCopiable
{
	NonTriviallyCopiable ()
	{
	};
	NonTriviallyCopiable (const NonTriviallyCopiable &rhs)
	{
		std::cout << "copy constructor" << std::endl;
	};
	void operator= (const NonTriviallyCopiable &rhs)
	{
		std::cout << "operator =" << std::endl;
	};
};

template<typename Begin, typename End, typename Out>
void Copy (Begin begin, End end, Out out)
{
	std::cout << "for copy" << std::endl;
	for (auto cur = begin; cur != end; ++cur, ++out)
		*out = *cur;
};

template<typename In, typename Out>
std::enable_if_t<std::is_pointer<In>::value &&
                 std::is_pointer<Out>::value &&
                 std::is_trivially_copyable<typename std::iterator_traits<In>::value_type>::value &&
                 std::is_trivially_copyable<typename std::iterator_traits<Out>::value_type>::value &&
                 sizeof(typename std::iterator_traits<In>::value_type) ==
                 sizeof(typename std::iterator_traits<Out>::value_type)>
Copy (In begin, In end, Out out)
{
	std::cout << "memcpy copy" << std::endl;
	memcpy (reinterpret_cast<void *> (out), reinterpret_cast<void *> (begin), end - begin);
};

int main ()
{
	NonTriviallyCopiable a[5], a_copy[5];
	int b[5] = {1, 2, 3, 4, 5}, b_copy[5] = {};
	std::vector<int> c = {1, 2, 3, 4, 5}, c_copy (5);
	std::cout << "Copy for a:" << std::endl;
	Copy (a, a + 5, a_copy);
	std::cout << "Copy for b:" << std::endl;
	Copy (b, b + 5, b_copy);
	std::cout << "b_copy:" << std::endl;
	for (int i = 0; i < 5; ++i)
		std::cout << b_copy[i] << ' ';
	std::cout << std::endl;
	std::cout << "Copy for c:" << std::endl;
	Copy (c.begin(), c.end(), c_copy.begin());
	std::cout << "c_copy:" << std::endl;
	for (int i = 0; i < 5; ++i)
		std::cout << c_copy[i] << ' ';
	std::cout << std::endl;
	return 0;
}
