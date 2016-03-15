#pragma once

#ifndef _CXS_QUEUE_H_
#define _CXS_QUEUE_H_

#include "cxs-commons.h"
#include "list.h"
#include "allocator.h"
#include "algorithm.h"

_CXS_NS_BEGIN

template<class T, class _Alloc = allocator<T>>
class queue{
public:
	//typedefs
	typedef queue<T, _Alloc> _Myqueue;
	typedef typename _Alloc::value_type value_type;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;

public:
	//constructions
	queue(){}
	queue(const _Myqueue& _right):_list(_right._list){}
	queue(_Myqueue&& _right):_list(std::move(_right._list)){}

public:
	//operators
	_Myqueue& operator=(const _Myqueue& _right){
		if(this != &_right){
			_list = _right._list;
		}
		return *this;
	}

	_Myqueue& operator=(_Myqueue&& _right){
		if(this != &_right){
			_list = std::move(_right._list);
		}
		return *this;
	}

public:
	//push(enqueue) & pop(dequeue)
	void push(const T& elem){
		_list.push_back(elem);
	}
	void push(T&& elem){
		_list.push_back(elem);
	}
	void pop(){
		_list.pop_front();
	}

	//clear
	void clear(){
		_list.clear();
	}

	//front & back
	reference front(){
		return _list.front();
	}

	const_reference front() const{
		return _list.front();
	}

	reference back(){
		return _list.back();
	}

	const_reference back() const{
		return _list.back();
	}

public:
	//swap
	void swap(_Myqueue& _right){
		cxs::swap(*this, _right);
	}

public:
	//empty & size
	bool empty() const{
		return _list.empty();
	}

	size_type size() const{
		return _list.size();
	}

protected:
	list<T, _Alloc> _list;
};

_CXS_NS_END

#endif