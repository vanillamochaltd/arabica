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
	static Type* GrowLinear(Index&, Index);
	static Type* GrowExponential(Index&, Index);
	inline void SetTo(Arabica::Array<Type, Index> const&);
	void Append(Type const&);

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
Arabica::DynamicArray<Type, Index>::DynamicArray(Index length){

	if(length) this->GrowPast(length);

	this->length_ = length;
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
Arabica::DynamicArray<Type, Index>::DynamicArray(Arabica::DynamicArray<Type, Index> const& array){

	this->SetTo(array);

}

// --------------------------------------------------------------
// @method_deconstructor:
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: -
// @description: deconstructor, called when out of scope or with
// 'delete' keyword

template<typename Type, typename Index>
Arabica::DynamicArray<Type, Index>::~DynamicArray(){

	this->Release();

}

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
	
	else this->size_ = 0x2;

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

// -------------------------------------------------
// @method: SetTo
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: current size, target size
// @description: Sets the current state of the array
// to the given array

template<typename Type, typename Index>
void Arabica::DynamicArray<Type, Index>::SetTo(Arabica::Array<Type, Index> const& array){

	if(this->size_ < array.size_) this->GrowPast(array.size_);

	for(Index index = 0x0; index < array.length_; index++)
		this->array_[index] = array[index];

	this->length_ = array.length_;

}

// -------------------------------------------------------
// @method: SetTo
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: array, length
// @description: Sets the current state to the given array

template<typename Type, typename Index>
void Arabica::DynamicArray<Type, Index>::SetTo(Type const* array, Index length){

	if(this->size_ < length) this->GrowPast(length);

	for(Index index = 0x0; index < length; index++)
		this->array_[index] = array[index];

	this->length_ = length;

}

// ------------------------------------------------------------
// @method: Append
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: Type
// @description: appends the given element to the current state

template<typename Type, typename Index>
void Arabica::DynamicArray<Type, Index>::Append(Type const& type){

	if(this->length_ == this->size_) this->GrowPast(this->size_ + 1);

	this->array_[this->length_] = type;

	this->length_++;

}

// -----------------------------------------------
// @operator: =
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: Type
// @description: Sets the array to single element 

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::DynamicArray<Type, Index>::operator= (Type const& type){

	this->Release();

	this->array_    = new Type[2] ;
	*(this->array_) = type        ;
	this->size      = 2           ;
	this->length_   = 1           ;

	return *this;

}

// -------------------------------------------------------
// @operator: =
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: Array<Type, Index>
// @description: Sets the current state to the given array

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::DynamicArray<Type, Index>::operator= (Arabica::Array<Type, Index> const& array){

	this->SetTo(array);

	return *this;

}

// ------------------------------------------------------
// @operator: +
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: array
// @description: Appends the element to the current state

template<typename Type, typename Index>
Arabica::Array<Type, Index> Arabica::DynamicArray<Type, Index>::operator+ (Type const& type){

	Index aggregate_size = this->size_ * Arabica::Dynamic_Array_Growth; 

	Arabica::DynamicArray<Type, Index> aggregate(aggregate_size);

	for(Index index = 0x0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	aggregate[aggregate.Length() - 1] = type;

	return aggregate;

}

// ------------------------------------------------------------
// @operator: +
// @class: dynamic array
// @author: carlos l cuenca
// @parameters: array<Type, Index>
// @description: aggregate the given array to the current state

template<typename Type, typename Index>
Arabica::Array<Type, Index> Arabica::DynamicArray<Type, Index>::operator+ (Arabica::Array<Type, Index> const& array){

	Index aggregate_size = this->size_ * Arabica::Dynamic_Array_Growth;

	Arabica::DynamicArray<Type, Index> aggregate(aggregate_size);

	for(Index index = 0x0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	for(Index index = 0x0; index < array.length_; index++)
		aggregate[this->length_ + index] = array[index];

	return aggregate;

}

#endif
