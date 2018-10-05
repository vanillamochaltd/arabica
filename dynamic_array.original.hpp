// Pre-Processor Directives

#ifndef ARABICA_ARRAY_HPP
#define ARABICA_ARRAY_HPP

#include "arabica.hpp"

template<typename Type, typename Index>
class Arabica::Array{

private:

	Type* array    ;
	Index size     ;
	Index quantity ;

	inline void setTo(Arabica::Array<Type, Index> const&);
	inline void release();
	inline void shiftForwardFrom(Index const&);
	inline bool reachedLimit() const;
	void grow();

public:

	// -------------
	// Rule of three

	Array(Index=0x00);
	Array(Arabica::Array<Type, Index> const&);
	~Array();

	// ----------------
	// Public Interface

	// --------
	// Mutators

	void append  (Type const&);
	void prepend (Type const&);
	void insert  (Type const&, Index const&);

	void append  (Arabica::Array<Type, Index> const&);
	void prepend (Arabica::Array<Type, Index> const&);
	void insert  (Arabica::Array<Type, Index> const&);

	void set     (Type const&, Index const&);

	// ---------
	// Accessors

	Type  const& at     (Index const&) const;
	Index const& length () const;

	// --------------------
	// Overloaded Operators

	Arabica::Array<Type, Index>& operator=  (Type const&);
	Arabica::Array<Type, Index>& operator+= (Type const&);

	Arabica::Array<Type, Index>& operator=  (Arabica::Array<Type, Index> const&);
	Arabica::Array<Type, Index>& operator+= (Arabica::Array<Type, Index> const&);

	Type& operator[] (Index const&) const;

};


template<typename Type, typename Index>
Arabica::Array<Type, Index>::Array(Index prelength): array(0), size(0), quantity(0){

	// Grow the array until we have reached the prelength
	while(prelength > quantity) grow();

	// Set the length to the prelength
	size = prelength;

}

template<typename Type, typename Index>
Arabica::Array<Type, Index>::Array(Arabica::Array<Type, Index> const& array): array(0), size(0), quantity(0){

	// Call the copy function
	this->copyFrom(array);

}

template<typename Type, typename Index>
Arabica::Array<Type, Index>::~Array(){

	// Call the release function
	this->release();

}

// ---------------
// Private Methods

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::setTo(Arabica::Array<Type,Index> const& array){

	// If we have items, release them
	if(this->array) delete[] this->array;

	// Create a new array
	this->array = new Type[array.quantity];

	// Copy the values
	for(Index index = 0; index < array.length; index++)
		this->array[index] = array[index];

	// Set our values
	this->length   = array.length;
	this->quantity = array.quantity;

}

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::release(){

	// If we have elements, release them
	if(array) delete[] array;

	// Reset the values
	array    = 0 ;
	size     = 0 ;
	quantity = 0 ;

}

template<typename Type, typename Index>
bool Arabica::Array<Type, Index>::reachedLimit() const{
	return (!array || size == quantity);
}

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::shiftForwardFrom(Index const& position){

	// Check if the position is out of bounds
	if(position >= size || position < 0) return;

	// If there is no array or we've reached the limit, make it grow
	if(reachedLimit()) grow();

	// Begin to loop and shift
	for(Index index = size - 1; index >= position && index < size; index--)
		array[index + 1] = array[index];


}

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::grow(){

	Index factor      = 2      ;
	Index newQuantity = factor ;

	if(size) newQuantity *= size;

	// Allocate new space
	Type* newArray = new Type[newQuantity];

	// If we have contents
	if(array){

		// Loop and add the contents
		for(Index index = 0; index < size; index++){

			newArray[index] = array[index];

		}

		// Release the old memory
		delete[] array;

	}

	// Set the new array
	array = newArray;

	// Update the quantity
	quantity = newQuantity;

}

// --------------
// Public Methods

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::append(Type const& type){

	// If we reached the limit, grow
	if(reachedLimit()) grow();

	// Otherwise, insert at the latest index
	array[size] = type ;

	// Update the length
	size++;

}

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::prepend(Type const& type){

	insert(type, 0);

}

template<typename Type, typename Index>
void Arabica::Array<Type, Index>::insert(Type const& type, Index const& position){

	// If the index is not within bounds
	if(position >= size || position < 0) return;

	// If there is no array or we've reached the limit, make it grow
	if(reachedLimit()) grow();

	// Shift forward
	shiftForwardFrom(position);

	// Set the given element
	array[position] = type;

	// Update the length
	size++;

}

template<typename Type, typename Index>
Type const& Arabica::Array<Type, Index>::at(Index const& index) const{
	return array[index];
}

template<typename Type, typename Index>
Index const& Arabica::Array<Type, Index>::length() const{
	return size;
}

// --------------------
// Overloaded Operators

template<typename Type, typename Index>
Arabica::Array<Type, Index>& Arabica::Array<Type, Index>::operator= (Arabica::Array<Type, Index> const& array){

	this->setTo(array);

}

template<typename Type, typename Index>
Type& Arabica::Array<Type, Index>::operator[] (Index const& index) const{
	return array[index];
}


#endif
