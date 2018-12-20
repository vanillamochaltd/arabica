COMPILER=clang++
CPPFLAGS=-Wall -g -pedantic -pedantic-errors -std=c++11

arabica: arabica.hpp array.hpp
	$(COMPILER) $(CPPFLAGS) -o arabica arabica_test.cpp

arabica_test: arabica.hpp array.hpp dynamic_array.hpp arabica_test.hpp
	$(COMPILER) $(CPPFLAGS) -o arabica_test arabica_test.cpp

clean:
	rm arabica
