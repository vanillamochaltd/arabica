COMPILER=clang++
CPPFLAGS=-Wall -g -pedantic -pedantic-errors -std=c++11

arabica: arabica.hpp array.hpp
	$(COMPILER) $(CPPFLAGS) -o arabica arabica_test.cpp

clean:
	rm arabica
