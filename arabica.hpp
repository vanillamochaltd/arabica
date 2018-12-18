// --------------------------------------
// @file: arabica.hpp
// @author: carlos l cuenca
// @description: declaration for arabica

#ifndef ARABICA_HPP
#define ARABICA_HPP

#include <iostream>
#include <cinttypes>

// ----------------------------------------------------
// @namespace: arabica
// @author: carlos l cuenca
// @description: declaration for common data structures
// and algorithms

namespace Arabica{

    // ---------------
    // Data Structures

    template<typename Type, typename Index>
    class Array;

    template<typename Type, typename Index>
    class DynamicArray;

    // -----------------
    // Utility Functions

    template<typename Type, typename Index>
    std::ostream& operator<< (std::ostream&, Array<Type, Index> const&);

};

#endif
