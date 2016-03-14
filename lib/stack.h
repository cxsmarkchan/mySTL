#pragma once
//stack.h
//stack
#ifndef _CXS_STACK_H_
#define _CXS_STACK_H_

#include "cxs-commons.h"
#include "allocator.h"
#include "vector.h"

_CXS_NS_BEGIN

template<class T, class _Alloc = allocator<T>>
class stack{
public:
	typedef stack<T, _Alloc> _Mystack;
	typedef typename _Alloc::value_type value_type;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;
public:
	stack();
	stack(const _Mystack& _right):_vec(_right._vec){}
	stack(_Mystack&& _right):_vec(std::move(_right._vec)){}
public:
	_Mystack& operator=(const _Mystack& _right){
		if(this != &_right){
			_vec = _right._vec;
		}
	}
	_Mystack& operator=(_Mystack** _right){
		if(this != &_right){
			_vec = std::move(_right._vec);
		}
	}
public:
	void push(const T& elem){
		_vec.push_back(x);
	}
	void pop(){
		_vec.pop_back();
	}
	reference top(){
		return _vec.back();
	}
	const_reference top() const{
		return _vec.back();
	}
	bool empty() const{
		return _vec.empty();
	}
	size_type size() const{
		return _vec.size();
	}
public:
	void swap(_Mystack& _right){
		swap(*this, _right);
	}
protected:
	vector<T, _Alloc> _vec;
};

_CXS_NS_END

template

#endif