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

	Arabica::Array<char, uint32_t> arguments;

	const char char_array[] = {'h','e','l','l','o'};

	Arabica::Array<int, uint32_t> array(ARRAY_SIZE);
	Arabica::Array<int, uint32_t> beta(ARRAY_SIZE + ARRAY_SIZE);

	for(int index = 0; index < array.Length(); index++){
		array[index] = index;
		beta[index] = index + 8;
	}

	std::cout << array << std::endl;

	std::cout << beta << std::endl;

	array = 345;

	std::cout << array << std::endl;

	array = beta;

	std::cout << array << std::endl;

	std::cout << std::endl;

	arguments.SetAs(char_array, 6);

	std::cout << arguments << std::endl;

	return 0;

}
