// ------------------------------------------
// @file: arabica_test.cpp
// @author: carlos l cuenca
// @description: arabica library test program

#include <iostream>
#include "arabica.hpp"
#include "array.hpp"

// TODO: Change the test cases
int main(int argument_count, char* argument_table[]){

	const int ARRAY_SIZE = 32;

	Arabica::Array<uint32_t, uint32_t> alpha(ARRAY_SIZE);
	Arabica::Array<uint32_t, uint32_t> beta(ARRAY_SIZE);

	std::cout << "Testing Array" << std::endl;
	std::cout << std::endl;

	for(uint32_t index = 0; index < ARRAY_SIZE; index++){
	
		alpha[index] = index + 3;
		beta[index]  = index + 4;
	
	}

	std::cout << alpha << std::endl;
	std::cout << beta  << std::endl;

	std::cout << "Testing + operator" << std::endl;
	std::cout << std::endl;

	std::cout << alpha + beta << std::endl;
	std::cout << beta + alpha << std::endl;
	std::cout << std::endl;

	std::cout << alpha + 10 << std::endl;
	std::cout << beta + 666 << std::endl;
	std::cout << std::endl;

	std::cout << alpha << std::endl;
	std::cout << beta << std::endl;
	std::cout << std::endl;

	std::cout << "Testing += operator" << std::endl;
	std::cout << std::endl;

	alpha += 10;
	beta  += 666;

	std::cout << alpha << std::endl;
	std::cout << beta  << std::endl;

	Arabica::Array<uint32_t, uint32_t> gamma(alpha);

	gamma += alpha;

	std::cout << gamma << std::endl;

	gamma += beta;

	std::cout << gamma << std::endl;

	return 0;
}
