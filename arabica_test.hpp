// ----------------------------------------
// @file: arabica_test.hpp
// @author: carlos l cuenca
// @description: test functions for arabica

#ifndef ARABICA_TEST
#define ARABICA_TEST

#include <iostream>
#include <cinttypes>
#include "arabica.hpp"

// ------------------------------------------------
// @namespace: arabica test
// @author: carlos l cuenca
// @description: declaration for arabica test cases

namespace ArabicaTest{

	// -------------------
	// Namespace Constants

	const char* LOG_DIVIDER_THIN  = "--------------------------------";
	const char* LOG_DIVIDER_THICK = "================================";

	// ----------------
	// Type Definitions

	typedef uint32_t StatusCode;
	typedef uint32_t Word;

	// --------------
	// Test Functions

	template<typename Type, typename Index>
	StatusCode TestArray ();


};

template<typename Type, typename Index>
ArabicaTest::StatusCode ArabicaTest::TestArray(){

	const ArabicaTest::Word ARRAY_SIZE = 0x20;

	Arabica::Array<Type, Index> alpha (ARRAY_SIZE);
	Arabica::Array<Type, Index> beta  (ARRAY_SIZE);

	std::cout << ArabicaTest::LOG_DIVIDER_THICK << "\n" << std::endl;
	std::cout << "Testing Array\n" << std::endl;

	for(ArabicaTest::Word index = 0x0; index < ARRAY_SIZE; index){
	
		alpha[index] = index + 3;
		beta[index]  = index + 4;

	}

	std::cout << ArabicaTest::LOG_DIVIDER_THIN << "\n" << std::endl;

	std::cout << alpha << std::endl;
	std::cout << beta  << std::endl;

	std::cout << ArabicaTest::LOG_DIVIDER_THICK << "\n" << std::endl;
	std::cout << "Testing + Operator" << "\n" << std::endl;

	std::cout << alpha + beta  << std::endl;
	std::cout << beta  + alpha << std::endl;
	std::cout << std::endl;

	std::cout << alpha + 10  << std::endl;
	std::cout << beta  + 666 << std::endl;
	std::cout << std::endl;

	std::cout << alpha << std::endl;
	std::cout << beta  << std::endl;
	std::cout << std::endl;

	std::cout << "Testing += operator" << std::endl;
	std::cout << std::endl;

	alpha += 10;
	beta  += 666;

	std::cout << alpha << std::endl;
	std::cout << beta  << std::endl;

	Arabica::Array<Type, Index> gamma(alpha);

	gamma += alpha;

	std::cout << gamma << std::endl;

	gamma += beta;

	std::cout << gamma << std::endl;

	return 0;


}

#endif
