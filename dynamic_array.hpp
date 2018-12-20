// ------------------------------------------------
// @file: array.hpp
// @author: carlos l cuenca
// @description: dynamic array class implementation

#ifndef ARABICA_DYNAMIC_ARRAY_HPP
#define ARABICA_DYNAMIC_ARRAY_HPP

#include "arabica.hpp"

// ------------------------------------------
// @class: dynamic array
// @author: carlos l cuenca
// @description: dynamic array implementation

template<typename Type, typename Index>
class Arabica::DynamicArray: public Arabica::Array<Type, Index>{

private:

	inline void GrowPast(Index);
	inline void SetTo(Arabica::Array<Type, Index> const&);

public:

	// -------------------
	// @public_constructor
	
	DynamicArray(Index=0x0);
	DynamicArray(Arabica::DynamicArray<Type, Index> const&);
	~DynamicArray();

	// ----------------------
	// @public_method:
	// @mutator: ChangeGrowth
	
	inline static void ChangeGrowth(float);
	void SetTo(Type const*, Index);	

	// --------------------
	// overloaded operators
	
	Arabica::Array<Type, Index>& operator=  (Type const&);
	Arabica::Array<Type, Index>& operator=  (Arabica::Array<Type, Index> const&);

	Arabica::Array<Type, Index>  operator+  (Type const&);
	Arabica::Array<Type, Index>  operator+  (Arabica::Array<Type, Index> const&);

	Arabica::Array<Type, Index>& operator+= (Type const&);
	Arabica::Array<Type, Index>& operator+= (Arabica::Array<Type, Index> const&);

};

// ------------------------------------------------------------------
// @method_constructor:
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: length
// @description: default constructor, takes in a length and allocates
// a block of memory, if any, and sets the member variables
// @note: The base class constructor is listed in the initializer list 
// for it to be called properly per multiple inheritence

template<typename Type, typename Index>
Arabica::DynamicArray<Type, Index>::DynamicArray(Index length): Arabica::Array<Type, Index>(length){

}

// --------------------------------------------------------------------
// @method_constructor:
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: array
// @description: copy constructor, takes in an existing array, and sets
// the values of the block to that of the given array
// @note: The base class constructor is listed in the initializer list
// for it to be called properly per multiple inheritence

template<typename Type, typename Index>
Arabica::DynamicArray<Type, Index>::DynamicArray(Arabica::DynamicArray<Type, Index> const& array): Arabica::Array<Type, Index>(array){


}

// --------------------------------------------------------------
// @method_deconstructor:
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: -
// @description: deconstructor, called when out of scope or with
// 'delete' keyword

template<typename Type, typename Index>
Arabica::DynamicArray<Type, Index>::~DynamicArray(){}

// -------------------------------------------------------
// @method: ChangeGrowth
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: -
// @description: Changes the growth rate of dynamic arrays

template<typename Type, typename Index>
void Arabica::DynamicArray<Type, Index>::ChangeGrowth(float growth_rate){

	Arabica::Dynamic_Array_Growth = growth_rate;

}

#endif
