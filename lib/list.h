#pragma once

#ifndef _CXS_LIST_H_
#define _CXS_LIST_H_

#include "cxs-commons.h"
#include "allocator.h"

_CXS_NS_BEGIN
//iterator
template<class V, class pointer, class reference>
class _list_iterator_base{
public:
	//typedefs
	typedef _list_iterator_base<V, pointer, reference> _Myiter;
	typedef typename V::node_pointer _innerPointer;
	typedef typename V::size_type size_type;
	typedef typename V::difference_type difference_type;
	typedef typename pointer pointer;
	typedef typename reference reference;

public:
	//constructions
	_list_iterator_base():_ptr(0){}
	_list_iterator_base(_innerPointer p):_ptr(p){}
	_list_iterator_base(const _Myiter& _it):_ptr(_it._ptr)){}
	template<class _Iter>
	_list_iterator_base(const _Iter& _it):_ptr(_it._ptr){}
	
public:
	//pointer and reference
	reference operator*() const{return _ptr->value;}
	pointer operator->() const{return &_ptr->value;}

	//++/--
	_Myiter& operator++(){_ptr = _ptr->next; return *this;}
	_Myiter operator++(int){
		_Myiter _it(_ptr);
		_ptr = _ptr->next;
		return _it;
	}

	_Myiter& operator--(){_ptr = _ptr->prev; return *this;}
	_Myiter operator--(int){
		_Myiter _it(_ptr);
		_ptr = _ptr->prev;
		return _it;
	}

	//==,!=
	bool operator==(const _Myiter& _right) const{return _ptr == _right._ptr);
	bool operator!=(const _Myiter& _right) const{return _ptr != _right._ptr);

protected:
	_innerPointer _ptr;

};

template<_Iter>
class _list_inverse_iterator: public _Iter{
public:
	//typedefs
	typedef _list_inverse_iterator<_Iter> _Myiter;
	typedef typename _Iter::_innerPointer _innerPointer;
	typedef typename _Iter::size_type size_type;
	typedef typename _Iter::difference_type difference_type;
	typedef typename _Iter::pointer pointer;
	typedef typename _Iter::reference reference;

public:
	//constructions
	_list_inverse_iterator():_Iter(){}
	_list_inverse_iterator(_innerPointer p):_Iter(p){}
	_list_inverse_iterator(const _Myiter& _right):_Iter(_right._ptr){}
	_list_inverse_iterator(const _Iter _right):_Iter(_Iter);
	//下面两句的访问权限问题还没有想清楚
	//template<class _IterOther>
	//_list_inverse_iterator(const _IterOther& _right):_Iter(_right._ptr){}

public:
	//++,--
	_Myiter& operator++(){return _Iter::operator--();}
	_Myiter operator++(int){return _Iter::operator--(0);}
	_Myiter& operator--(){return _Iter::operator++();}
	_Myiter operator--(){return _Iter::operator++(0);}
}

_CXS_NS_END

#endif