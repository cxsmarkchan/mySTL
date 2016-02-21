#pragma once

#ifndef _CXS_VECTOR_IMPL_H_
#define _CXS_VECTOR_IMPL_H_

#include "cxs-commons.h"
#include "vector.h"

_CXS_NS_BEGIN

template<class T>
vector<T>::vector(const size_type size):_size(0), _capacity(size){
	_arr = new T[size];
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
