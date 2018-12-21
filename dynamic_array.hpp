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

	// -------------------------
	// @private_method
	// @mutator: GrowPast, SetTo

	inline void GrowPast(Index);
	inline void SetTo(Arabica::Array<Type, Index> const&);
	static Type* GrowLinear(Index&, Index);
	static Type* GrowExponential(Index&, Index);

public:

	// -------------------
	// @public_constructor
	
	DynamicArray(Index=0x0);
	DynamicArray(Arabica::DynamicArray<Type, Index> const&);
	~DynamicArray();

	// ----------------------
	// @public_method:
	// @mutator: ChangeGrowth
	
	inline static void SetGrowth(float);
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
void Arabica::DynamicArray<Type, Index>::SetGrowth(float growth_rate){

	Arabica::Dynamic_Array_Growth = growth_rate;

}

// -----------------------------------------------------------
// @method: GrowPast
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: length
// @description: grows the internal block past the given index
// by default, the block growth is linear

template<typename Type, typename Index>
void Arabica::DynamicArray<Type, Index>::GrowPast(Index size){

	Arabica::Array<Type, Index> buffer(*this);
	
	if(this->size_) delete[] this->array_;

	else this->size_ = 0x1;

	this->array_ = GrowLinear(this->size_, size);

	for(Index index = 0x0; index < this->length_; index++)
		this->array_[index] = buffer[index];

}

// ------------------------------------------------------------------------------------
// @method: GrowLinear
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: length
// @description: calculates a linear value, allocates the space, and returns the pointer

template<typename Type, typename Index>
Type* Arabica::DynamicArray<Type, Index>::GrowLinear(Index& current_size, Index target_size){

	while(current_size <= target_size) current_size *= Arabica::Dynamic_Array_Growth;

	Type* array = new Type[current_size]();

	return array;

}

// -------------------------------------------------------------------
// @method: GrowExponential
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: length, target length
// @description: calculates an exponential value, allocates the space,
// and returns the pointer to the new block

template<typename Type, typename Index>
Type* Arabica::DynamicArray<Type, Index>::GrowExponential(Index& current_size, Index target_size){

	float size      = current_size ;
	float threshold = target_size  ;

	while(size <= threshold) size *= Arabica::Dynamic_Array_Growth;

	current_size = size;

	Type* array = new Type[current_size]();

	return array;

}

#endif
