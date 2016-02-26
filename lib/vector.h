#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Copyright: cxsmarkchan
//Github: cxsmarkchan
//Creating: 2016-Feb-21
//Reference: STL <vector>
//遗留问题：分配内存与构造函数分开的机制还没有完全实现。

#ifndef _CXS_VECTOR_H_
#define _CXS_VECTOR_H_

#include <cstdlib>
#include "cxs-commons.h"
#include "allocator.h"

_CXS_NS_BEGIN

//V：向量类型
template<class V, class pointer, class reference>
class _vector_iterator_base{
public:
	//typedefs
	typedef _vector_iterator_base<V, pointer, reference> _Myiter;
	typedef typename V::pointer _innerPointer;
	typedef typename V::value_type value_type;
	typedef typename V::difference_type difference_type;
	friend V;

public:
	//constructions
	_vector_iterator_base():_ptr(NULL){}
	_vector_iterator_base(_innerPointer p):_ptr(p){}
	
public:
	//operations

	//*, ->
	reference operator*() const{return *_ptr;}
	pointer operator->() const{return _ptr;}

	//++, --
	_Myiter& operator++(){_ptr++; return *this;}
	_Myiter operator++(int){
		_Myiter tmp = *this;
		_ptr++;
		return tmp;
	}
	_Myiter& operator--(){_ptr--; return *this;}
	_Myiter operator--(int){
		_Myiter tmp = *this;
		_ptr--;
		return tmp;
	}

	//+=, -=, +, -
	_Myiter& operator+=(difference_type _diff){_ptr += _diff; return *this;}
	_Myiter& operator-=(difference_type _diff){_ptr -= _diff; return *this;}
	_Myiter operator+(difference_type _diff) const{return _Myiter(_ptr + _diff);}
	_Myiter operator-(difference_type _diff) const{return _Myiter(_ptr - _diff);}
	difference_type operator-(const _Myiter& _right) const{return _ptr - _right._ptr;}

	//subscript[]
	reference operator[](difference_type idx) const{return *(_ptr + idx);}

	//comparisons
	bool operator==(const _Myiter& _right) const{return _ptr == _right._ptr;}
	bool operator!=(const _Myiter& _right) const{return _ptr != _right._ptr;}
	bool operator>(const _Myiter& _right) const{return _ptr > _right._ptr;}
	bool operator>=(const _Myiter& _right) const{return _ptr >= _right._ptr;}
	bool operator<(const _Myiter& _right) const{return _ptr < _right._ptr;}
	bool operator<=(const _Myiter& _right) const{return _ptr <= _right._ptr;}
	
protected: //stl中该变量是public，不是非常能理解
	_innerPointer _ptr; //维护的指针变量
};


template<class V>
class _vector_const_iterator;

template<class V>
class _vector_iterator:
	public _vector_iterator_base<V, typename V::pointer, typename V::reference>{
public:
	typedef _vector_iterator<V> _Myiter;
	typedef _vector_iterator_base<V, typename V::pointer, typename V::reference> _Mybase;
public:
	_vector_iterator():_vector_iterator_base(){}
	_vector_iterator(_innerPointer p):_vector_iterator_base(p){}
	_vector_iterator(const _Mybase& _it):_vector_iterator_base(_it){}
	friend _vector_const_iterator<V>;
public:
	_Myiter& operator=(const _Mybase& _base){
		if(this != (_Myiter*)&_base){
			_ptr = _base._ptr;
		}
		return *this;
	}
};

template<class V>
class _vector_const_iterator:
	public _vector_iterator_base<V, typename V::const_pointer, typename V::const_reference>{
public:
	typedef _vector_const_iterator<V> _Myiter;
	typedef _vector_iterator_base<V, typename V::const_pointer, typename V::const_reference> _Mybase;
public:
	_vector_const_iterator():_vector_iterator_base(){}
	_vector_const_iterator(_innerPointer p):_vector_iterator_base(p){}
	_vector_const_iterator(const _Mybase& _it):_vector_iterator_base(_it){}
	_vector_const_iterator(const _vector_iterator<V>& _it):_vector_iterator_base(_it._ptr){}
public:
	_Myiter& operator=(const _Mybase& _base){
		if(this != (_Myiter*)&_base){
			_ptr = _base._ptr;
		}
		return *this;
	}
};

template<class _Iter>
class _vector_reverse_iterator:
	public _Iter{
//一个问题：利用_Iter实现inverse iterator，在调用各种运算符时需要先返回_Iter类型，再返回inverse类型
//其中涉及内存复制操作，是否会影响效率？（因为iterator操作的调用非常频繁）
public:
	typedef _vector_reverse_iterator<_Iter> _Myiter;
	typedef typename _Iter::_innerPointer _innerPointer;
	typedef typename _Iter::difference_type difference_type;
	typedef typename _Iter::reference reference;
public:
	_vector_reverse_iterator():_Iter(){}
	_vector_reverse_iterator(_innerPointer p):_Iter(p){}
	_vector_reverse_iterator(const _Iter& _base){
		std::memcpy(this, _base, sizeof(_Iter));
	}
public:
	_Myiter& operator++(){return _Myiter(_Iter::operator--());}
	_Myiter operator++(int){return _Myiter(_Iter::operator--(0));}
	_Myiter& operator--(){return _Myiter(_Iter::operator++());}
	_Myiter operator--(int){return _Myiter(_Iter::operator++(0));}

	//+=, -=, +, -
	_Myiter& operator+=(difference_type _diff){return _Myiter(_Iter::operator-=(_diff));}
	_Myiter& operator-=(difference_type _diff){return _Myiter(_Iter::operator+=(_diff));}
	_Myiter operator+(difference_type _diff) const{return _Myiter(_Iter::operator-(_diff));}
	_Myiter operator-(difference_type _diff) const{return _Myiter(_Iter::operator+(_diff));}
	difference_type operator-(const _Myiter& _right) const{return _right._Iter::operator-(*this);}

	//subscript[]
	reference operator[](difference_type idx) const{return _Iter::operator[](idx);}

	//comparisons
	bool operator==(const _Myiter& _right) const{return _Iter::operator==(_right);}
	bool operator!=(const _Myiter& _right) const{return _Iter::operator!=(_right)}
	bool operator>(const _Myiter& _right) const{return _Iter::operator<(_right);}
	bool operator>=(const _Myiter& _right) const{return _Iter::operator<=(_right);}
	bool operator<(const _Myiter& _right) const{return _Iter::operator>(_right);}
	bool operator<=(const _Myiter& _right) const{return _Iter::operator>=(_right);}

};

template<class T, class _Alloc = allocator<T>>
class vector{
public:
	//typedefs
	typedef vector<T, _Alloc> _vecT;
	typedef _Alloc allocator_type;
	typedef typename _Alloc::value_type value_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;
	typedef _vector_iterator<_vecT> iterator;
	typedef _vector_const_iterator<_vecT> const_iterator;
	typedef _vector_reverse_iterator<iterator> reverse_iterator;
	typedef _vector_reverse_iterator<const_iterator> const_reverse_iterator;

//////////////////////////////////////
// Variables
protected:
	T* _arr;
	size_type _size;
	size_type _capacity;
public:
	typedef vector<T, _Alloc> _vecT;
////////////////////////////////////////
// Methods
// Construction & Destruction
public:
	vector();//Default
	vector(const size_type size);//A vector with n datafields construted by default construction functions.
	vector(const _vecT& _right);//Copy
	vector(const T* arr, const size_type len);//Copy of an array of T
	vector(size_type n, const T& elem);//A vector with n elements of elem
	template<class _Iter>
	vector(_Iter begin, _Iter end);//copy of elements in [begin, end)

	virtual ~vector();

// Operators
public:
	_vecT& operator=(const _vecT& _right);
	reference operator[](size_type n);
	const_reference operator[](size_type n) const;

// Updating
public:
	//push and pop
	void push_back(const T& elem);//insert at end, O(1)
	void pop_back();//remove at end, O(1)

public:
	//assign
	void assign(const_iterator begin, const_iterator end);//copy of [begin, end)
	void assign(size_type n, const T& elem);//n elements initialized by elem.

public:
	//insert
	iterator insert(const_iterator pos, const T& elem);//insert elem behind pos, and return the pointer of new data.
	void insert(const_iterator pos, size_type n, const_reference elem);//insert n elem behind pos
	void insert(const_iterator pos, const_iterator begin, const_iterator end);//insert [begin, end) behind pos

public:
	//remove
	void clear();
	iterator erase(const_iterator pos);//remove the data at pos and return the pointer of the next data
	iterator erase(const_iterator begin, const_iterator end);//remove [begin, end) return the next data

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
	reference at(size_type idx);
	const_reference at(size_type idx) const;
	reference front();//the first data
	const_reference front() const;
	reference back();//the last data
	const_reference back() const;
	iterator begin();//iterator of the first data
	const_iterator begin() const;
	iterator end();//iterator of the last data
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	size_type capacity() const;//allocated storage
	size_type size() const;//length of datafields
	//size_type max_size() const;//max size, I just don't know what it is
	bool empty() const;

protected:
	//辅助
	//由const_iterator得到iterator
	iterator _make_iterator(const_iterator _it) const{return iterator(_it._ptr);}


};





_CXS_NS_END

#include "vector_impl.h"

#endif