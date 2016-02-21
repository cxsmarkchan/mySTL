#pragma once

#ifndef _CXS_VECTOR_IMPL_H_
#define _CXS_VECTOR_IMPL_H_

#include "cxs-commons.h"
#include "vector.h"

_CXS_NS_BEGIN

//////////////////////////////////////////////////////////////////////////////////////////
//Constrution & Destruction

template<class T>
vector<T>::vector():_size(0), _capacity(1){
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

template<class T>
T& vector<T>::operator[](size_type n){
	return _arr[n];
}

template<class T>
void vector<T>::push_back(const T& elem){
	if(_size < _capacity){
		_arr[_size++] = elem;
	}else{
	}
}


_CXS_NS_END


#endif
