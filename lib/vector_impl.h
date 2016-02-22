#pragma once

#ifndef _CXS_VECTOR_IMPL_H_
#define _CXS_VECTOR_IMPL_H_

#include "cxs-commons.h"
#include "vector.h"

#define _CXS_VECTOR_INITIAL_SIZE 1

_CXS_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////////////////
// Constrution & Destruction

template<class T>
vector<T>::vector():_size(0), _capacity(_CXS_VECTOR_INITIAL_SIZE){
	_arr = new T[_capacity];
}

template<class T>
vector<T>::vector(const size_type size):_size(size), _capacity(size){
	_arr = new T[size];
}

template<class T>
vector<T>::vector(const _vecT& _right){
	_size = _right.size();
	_capacity = _right.capacity();
	_arr = new T[_capacity];
	for(size_type i = 0; i < _size; i++){
		_arr[i] = _right[i];
	}
}

template<class T>
vector<T>::vector(const T* arr, size_type len){
	_size = _capacity = len;
	_arr = new T[_capacity];
	for(size_type i = 0; i < _size; i++){
		_arr[i] = arr[i];
	}
}

template<class T>
vector<T>::vector(size_type n, const T& elem):_size(n), _capacity(n){
	_arr = new T[_capacity];
	for(size_type i = 0; i < n; i++){
		_arr[i] = elem;
	}
}

template<class T>
vector<T>::vector(const T* Beg, const T* End){
	_size = _capacity = End - Beg;
	_arr = new T[_capacity];
	T* now = Beg;
	while(now != end){
		_arr[now - Beg] = *now;
		now++;
	}
}

template<class T>
vector<T>::~vector(){
	if(_arr != NULL)
		delete[] _arr;
}

//////////////////////////////////////////////////////////////////////////////////
// Operators

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& _right){
	if(&_vecT != this){
		if(_arr != NULL) delete[] _arr;
		_size = _right._size;
		_capacity = _right._capacity;
		_arr = new T[_capacity];
		for(size_type i = 0; i < _size; i++){
			_arr[i] = _right[i];
		}
	}
	return this;
}

template<class T>
T& vector<T>::operator[](size_type n){
	return _arr[n];
}

///////////////////////////////////////////////////////////////////////
// Updating

// push
template<class T>
void vector<T>::push_back(const T& elem){
	if(_capacity <= _size){
		reserve(_capacity * 2);
	}
	_arr[_size++] = elem;
}

// pop
template<class T>
void vector<T>::pop_back(){
	_size--;
	if(_size <= _capacity / 4){
		reserve(_capacity / 2);
	}
}

// assign
template<class T>
void vector<T>::assign(const T* Beg, const T* End){
	_size = End - Beg;
	_capacity = _size;
	T* _new_arr = new T[_capacity];
	for(size_type i = 0; i < _size; i++){
		_new_arr[i] = *(Beg + i);
	}

	if(_arr != NULL) delete[] _arr;
	_arr = _new_arr;

}

template<class T>
void vector<T>::assign(size_type n, const T& elem){
	_size = _capacity = n;
	if(_arr != NULL) delete[] _arr;
	_arr = new T[_capacity];
	for(size_type i = 0; i < _size; i++){
		_arr[i] = elem;
	}
}

// insert
template<class T>
T* vector<T>::insert(const T* pos, const T& elem){
	if(_capacity <= _size){
		reserve(_capacity * 2);
	}
	size_type index = pos - _arr;
	for(size_type i = _size; i > index; i--){
		_arr[i] = _arr[i - 1];
	}
	_arr[index] = elem;
	_size++;
}

// insert n elem behind pos
template<class T>
void vector<T>::insert(const T* pos, size_type n, const T& elem){
	if(_capacity < _size + n){
		reserve((_size + n) * 2);
	}
	size_type index = pos - _arr;
	for(size_type i = _size + n - 1; i > index + n - 1; i--){
		_arr[i] = _arr[i - n];
	}
	for(size_type i = index; i < index + n; i++){
		_arr[i] = elem;
	}
	_size += n;
}

// insert [begin, end) behind pos
template<class T>
void vector<T>::insert(const T* pos, const T* Beg, const T* End){
	size_type n = End - Beg;
	if(_capacity < _size + n){
		reserve((_size + n) * 2);
	}
	size_type index = pos - _arr;
	for(size_type i = _size + n - 1; i > index + n - 1; i--){
		_arr[i] = _arr[i - n];
	}
	for(size_type i = index; i < index + n; i++){
		_arr[i] = *(Beg + i - index);
	}
	_size += n;
}


///////////////////////////////////////////////////////////////////////////////////////////
// Remove

// clear
template<class T>
void vector<T>::clear(){
	if(_arr != NULL) delete[] _arr;
	_size = 0;
	_capacity = _CXS_VECTOR_INITIAL_SIZE;
	_arr = new T[_capacity];
}

//remove the data at pos and return the pointer of the next data
template<class T>
T* vector<T>::erase(T* pos){
	_size--;
	for(size_type i = pos - _arr; i < _size; i++){
		_arr[i] = _arr[i + 1];
	}
	shrink();
}

//remove [begin, end) return the next data
template<class T>
T* vector<T>::erase(T* Beg, T* End){
	size_type n = End - Beg;
	_size -= n;
	for(T* cur = Beg; cur < End; cur++){
		*cur = *(cur + n);
	}
	shrink();
}

//////////////////////////////////////////////////////////////////////////////////////////
// about size
template<class T>
void vector<T>::resize(size_type new_size){
	if(_capacity <= new_size){
		reserve(new_size);
	}
	_size = new_size;
}

template<class T>
void vector<T>::resize(size_type new_size, const T& elem_fill){
	if(_capacity <= new_size){
		reserve(new_size);
		for(size_type i = _size; i < new_size; i++){
			_arr[i] = elem_fill;
		}
	}
	_size = new_size;
}

template<class T>
void vector<T>::reserve(size_type new_capacity){
	if(_capacity <= new_capacity){
		T* _new_arr = new T[new_capacity];
		if(_arr != NULL){
			for(size_type i = 0; i < _size; i++){
				_new_arr[i] = _arr[i];
			}
			delete[] _arr;
		}
		_arr = _new_arr;
	}
}


// expand if necessary
template<class T>
void vector<T>::expand(){
	if(_capacity <= _size) reserve(_capacity * 2);
}

// shrink if necessary
template<class T>
void vector<T>::shrink(){
	if(_size < _capacity / 4) reserve(_capacity / 2);
}

///////////////////////////////////////////////////////////////////////////
// swap
template<class T>
void vector<T>::swap(vector<T>& c2){
	size_type _tmp_size = _size;
	_size = c2._size;
	c2._size = _tmp_size;

	size_type _tmp_capacity = _capacity;
	_capacity = c2._capacity;
	c2._capacity = _tmp_capacity;

	T* _tmp_arr = _arr;
	_arr = c2._arr;
	c2._arr = _tmp_arr;
}

template<class T>
void swap(vector<T>& c1, vector<T>& c2){
	size_type _tmp_size = c1._size;
	c1._size = c2._size;
	c2._size = _tmp_size;

	size_type _tmp_capacity = c1._capacity;
	c1._capacity = c2._capacity;
	c2._capacity = _tmp_capacity;

	T* _tmp_arr = c1._arr;
	c1._arr = c2._arr;
	c2._arr = _tmp_arr;}

_CXS_NS_END


#endif
