#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Copyright: cxsmarkchan
//Github: cxsmarkchan
//Creating: 2016-Feb-21
//Reference: STL <vector>

#ifndef _CXS_VECTOR_H_
#define _CXS_VECTOR_H_

#include "cxs-commons.h"

_CXS_NS_BEGIN

template<class T>
class vector{
//////////////////////////////////////
// Variables
protected:
	T* _arr;
	size_type _size;
	size_type _capacity;public:
	typedef vector<T> _vecT;
////////////////////////////////////////
// Methods
// Construction & Destruction
public:
	vector();//Default
	vector(const size_type size);//A vector with n datafields construted by default construction functions.
	vector(const _vecT& _right);//Copy
	vector(const T* arr, const size_type len);//Copy of an array of T
	vector(size_type n, const T& elem);//A vector with n elements of elem
	vector(const T* begin, const T* end);//copy of elements in [begin, end)

	virtual ~vector();

// Operators
public:
	_vecT& operator=(const _vecT& _right);
	T& operator[](size_type n) const;

// Updating
public:
	//push and pop
	void push_back(const T& elem);//insert at end, O(1)
	void pop_back();//remove at end, O(1)

public:
	//assign
	void assign(const T* begin, const T* end);//copy of [begin, end)
	void assign(size_type n, const T& elem);//n elements initialized by elem.

public:
	//insert
	T* insert(const T* pos, const T& elem);//insert elem behind pos, and return the pointer of new data.
	void insert(const T* pos, size_type n, const T& elem);//insert n elem behind pos
	void insert(const T* pos, const T* begin, const T* end);//insert [begin, end) behind pos

public:
	//remove
	void clear();
	T* erase(T* pos);//remove the data at pos and return the pointer of the next data
	T* erase(T* begin, T* end);//remove [begin, end) return the next data

public:
	//about size
	void resize(size_type new_size);
	void resize(size_type new_size, const T& elem_fill);
	void reserve(size_type new_capacity);

protected:
	// expand or shrink if necessary
	void expand();
	void shrink();
	
public:
	//swap
	void swap(_vecT& c2);//swap the elements of this and c2
	friend void swap(_vecT& c1, _vecT& c2);//swap the elements of c1 and c2


// Query
public:
	T& at(size_type idx) const;
	T& front() const;//the first data
	T& back() const;//the last data
	T* begin() const;//iterator of the first data
	T* end() const;//iterator of the last data
	//rbegin
	//rend
	size_type capacity() const;//allocated storage
	size_type size() const;//length of datafields
	//size_type max_size() const;//max size, I just don't know what it is
	bool empty() const;



};





_CXS_NS_END

#include "vector_impl.h"

#endif