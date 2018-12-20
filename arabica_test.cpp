// ------------------------------------------
// @file: arabica_test.cpp
// @author: carlos l cuenca
// @description: arabica library test program

#include <iostream>
#include "arabica.hpp"
#include "array.hpp"
#include "dynamic_array.hpp"
#include "arabica_test.hpp"

int main(int argument_count, char* argument_table[]){

	ArabicaTest::TestArray<uint32_t, uint32_t>();
	ArabicaTest::TestDynamicArray<uint32_t, uint32_t>();

	return 0;

}
