#include <iostream>
#include "Arithmetic.hpp"

int main(int argc, char** argv){
	std::cout << "Hello cpp cmake and vim" << std::endl;

	std::cout << "10 + 15 = " << Arithmetic::add(10,15) << std::endl;

	return 0;
}
