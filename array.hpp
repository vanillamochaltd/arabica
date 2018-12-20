// ----------------------------------------
// @file: array.hpp
// @author: carlos l cuenca
// @description: array class implementation

#ifndef ARABICA_ARRAY_HPP
#define ARABICA_ARRAY_HPP

#include "arabica.hpp"

// -------------------------------------------
// @class: array [base]
// @author: carlos l cuenca
// @description: base array implementation

template<typename Type, typename Index>
class Arabica::Array{

protected:

	// -----------------------------
	// @private_member:
	// @array_: location in memory
	// @size_:  block size
	// @length_: valid data in block

	Type* array_  ;
	Index size_   ;
	Index length_ ;

	inline void Release();
	inline void SetTo(Arabica::Array<Type, Index> const&);

public:

	// -----------------------------
	// @public_constructor:

	Array(Index=0x00);
	Array(Arabica::Array<Type, Index> const&);
	~Array();

	// -----------------
	// @public_member:
	// @accessor: Length
	// @mutator: SetAs
	// @operator: [], =, +

	Index const& Length ()             const;
	void SetAs(Type const*, Index);

	// --------------------
	// Overloaded Operators

	Type& operator[] (Index const&) const;

	Arabica::Array<Type, Index>& operator=  (Type const&);
	Arabica::Array<Type, Index>& operator=  (Arabica::Array<Type, Index> const&);

	Arabica::Array<Type, Index>  operator+  (Type const&);
	Arabica::Array<Type, Index>  operator+  (Arabica::Array<Type, Index> const&);

	Arabica::Array<Type, Index>& operator+= (Type const&);
	Arabica::Array<Type, Index>& operator+= (Arabica::Array<Type, Index> const&);

	// ----------------
	// Friend Functions

	template<typename Type_, typename Index_>
	friend std::ostream& Arabica::operator<< (std::ostream&, Arabica::Array<Type_, Index_> const&);

};


// --------------------------------------------------------------------
// @method_constructor:
// @class: array
// @author: carlos l cuenca
// @parameters: length
// @description: default constructor, takes in a length, and allocates
// a block of memeory, if any, and sets the member variables

template<typename Type, typename Index>
Arabica::Array<Type, Index>::Array(Index length): array_(0x00), size_(0), length_(0){

	if(length) this->array_ = new Type[length]();

	this->size_   = length;
	this->length_ = length;

}

// ------------------------------------------------------------------------
// @method_constructor:
// @class: array
// @author: carlos l cuenca
// @parameters: length
// @description: copy constructor, takes in an existing array, and set the
// values of the block from that array

template<typename Type, typename Index>
Arabica::Array<Type, Index>::Array(Arabica::Array<Type, Index> const& array): array_(0x00), size_(0), length_(0){

	this->SetTo(array);

}

// ---------------------------------------------------------------------
// @method_deconstructor:
// @class: array
// @author: carlos l cuenca
// @parameters: -
// @description: deconstructor, called when out of scope if it's a scope
// local variable, or when the 'delete[]' keyword is marked

template<typename Type, typename Index>
Arabica::Array<Type, Index>::~Array(){

	this->Release();

}

// ------------------------------------------------------------------
// @method: Release
// @class: array
// @author: carlos l cuenca
// @parameters: -
// @description: Releases the memory, and clears the member variables

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::Release(){

	if(this->array_) delete[] this->array_;

	this->array_  = 0;
	this->size_   = 0;
	this->length_ = 0;

}

// -----------------------------------------------
// @method: SetTo
// @class: array
// @author: carlos l cuenca
// @parameters: array
// @description: Sets the array to the given array

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::SetTo(Arabica::Array<Type, Index> const& array){

	this->Release();

	if(array.length_){

		this->array_ = new Type[array.size_]();

		for(Index index = 0; index < array.length_; index++)
			this->array_[index] = array[index];

		this->size_   = array.size_;
		this->length_ = array.length_;

	}

}

// ---------------------------------------------
// @method: Length
// @class: array
// @author: carlos l cuenca
// @parameters: -
// @description: Returns the length of the array

template<typename Type, typename Index>
Index const& Arabica::Array<Type, Index>::Length() const{
	return this->length_;
}

// --------------------------------------------------
// @method: Length
// @class: array
// @author: carlos l cuenca
// @parameters: pointer to array, count
// @description: Sets the current state to the given
// primitive array

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::SetAs(Type const* array, Index length){

	this->Release();

	if(length){

		this->array_ = new Type[length];

		for(Index index = 0; index < length; index++)
			this->array_[index] = array[index];

		this->size_   = length;
		this->length_ = length;

	}

}

// --------------------------------------------------
// @operator: []
// @class: array
// @author: carlos l cuenca
// @parameters: index
// @description: Returns the nth element in the array
template<typename Type, typename Index>
Type& Arabica::Array<Type, Index>::operator[] (Index const& index) const{
	return this->array_[index];

}

// ------------------------------------------------
// @operator: =
// @class: array
// @author: carlos l cuenca
// @parameters: Type
// @description: Sets the array to the single type

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::Array<Type, Index>::operator= (Type const& type){

	this->Release();

	this->array_    = new Type[1];
	*(this->array_) = type;
	this->size_     = 1;
	this->length_   = 1;

	return *this;

}

// -----------------------------------------------
// @operator: =
// @class: array
// @author: carlos l cuenca
// @parameters: array
// @description: Set the array to the given array

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::Array<Type, Index>::operator= (Arabica::Array<Type, Index> const& array){

	this->Release();
	this->SetTo(array);

	return *this;
}

// ---------------------------------------------------------------------
// @operator: +
// @class:array
// @author: carlos l cuenca
// @parameters: Type
// @description: Builds and returns an aggregation of an array and Type

template<typename Type, typename Index>
Arabica::Array<Type, Index> Arabica::Array<Type, Index>::operator+ (Type const& type){

	Arabica::Array<Type, Index> aggregate(this->size_ + 1);

	for(Index index = 0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	aggregate[aggregate.Length() - 1] = type;

	return aggregate;
}

// ---------------------------------------------------------------------
// @operator: +
// @class: array
// @author carlos l cuenca
// @parameters: array<Type, Index>
// @description: Create and Return an aggregate array from the result of
// combining this array with another

template<typename Type, typename Index>
Arabica::Array<Type, Index> Arabica::Array<Type, Index>::operator+ (Arabica::Array<Type, Index> const& array){

	Arabica::Array<Type, Index> aggregate(this->size_ + array.size_);

	for(Index index = 0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	for(Index index = 0; index < array.length_; index++)
		aggregate[this->length_ + index] = array[index];

	return aggregate;

}

// ----------------------------------------------------------
// @operator: +=
// @class: array
// @author: carlos l cuenca
// @parameters: Type
// @description: Append the data of Type to the current array

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::Array<Type, Index>::operator+= (Type const& type){

	Type* aggregate = new Type[this->size_ + 1]();

	for(Index index = 0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	aggregate[this->length_] = type;

	if(this->array_) delete[] this->array_;

	this->array_ = aggregate;
	this->length_++;
	this->size_++;

	return *this;

}

// ------------------------------------------------------------------
// @operator: +=
// @class: array
// @author: carlos l cuenca
// @parameters: Array<Type, Index>&
// @description: Append the given array of Type to the current array

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::Array<Type, Index>::operator+= (Arabica::Array<Type, Index> const& array){

	Type* aggregate = new Type[this->size_ + array.size_]();

	for(Index index = 0; index < this->length_; index++)
		aggregate[index] = this->array_[index];

	for(Index index = 0; index < array.length_; index++)
		aggregate[this->length_ + index] = array.array_[index];

	if(this->array_) delete[] this->array_;

	this->array_   = aggregate;
	this->length_ += array.length_;
	this->size_   += array.size_;

	return *this;
}

// -------------------------------------------------------
// @friend_operator: <<
// @class: array
// @author: carlos l cuenca
// @parameters: output stream, array
// @description: prints out the array to the output stream

template<typename Type, typename Index>
std::ostream& Arabica::operator<< (std::ostream& outputstream, Arabica::Array<Type, Index> const& array){

	for(Index index = 0; index < array.Length(); index++)
		std::cout << array[index] << " ";

	return outputstream;

}

#endif
