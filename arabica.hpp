// --------------------------------------
// @file: arabica.hpp
// @author: carlos l cuenca
// @description: declaration for arabica

#ifndef ARABICA_HPP
#define ARABICA_HPP

#include <cinttypes>

// ----------------------------------------------------
// @namespace: arabica
// @author: carlos l cuenca
// @description: declaration for common data structures
// and algorithms

namespace Arabica{

    // ----------
    // Type alias

    typedef uint64_t Scalar    ;
    typedef uint64_t Quantity  ;
    typedef uint64_t Index     ;
    typedef bool     Boolean   ;
    typedef char     Character ;

	// ---------------
	// Data Structures

    template<typename Type, typename Index>
    class Array;

	template<typename Type, typename Index>
	class StaticArray;

	template<typename Type, typename Index>
	class DynamicArray;

	// -----------------
	// Utility Functions

	template<typename Type, typename Index>
	std::ostream& operator<< (std::ostream&, Array<Type, Index> const&);


};

#endif
