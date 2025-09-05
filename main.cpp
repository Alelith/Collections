#include <iostream>
#include "vector.hpp"

int main() {
	Vector<int> vec;

	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	vec.push_back(42);
	std::cout << "Size after push_back: " << vec.size() << std::endl;
	std::cout << "Capacity after push_back: " << vec.capacity() << std::endl;

	vec.push_back(42);
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(7);
	std::cout << "Size after push_back: " << vec.size() << std::endl;
	std::cout << "Capacity after push_back: " << vec.capacity() << std::endl;

	vec[5];

	int res = 0;
	for (int a : vec)
	{
		res += a;
	}

	std::cout << "La sumatoria del contenido en vec es: " << res << std::endl;

	return 0;
}
