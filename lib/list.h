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
	_list_iterator_base(const _Myiter& _it):_ptr(_it._ptr){}
	template<class _Iter>
	_list_iterator_base(const _Iter& _it):_ptr(_it.getPointer()){}
	
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
	bool operator==(const _Myiter& _right) const{return _ptr == _right._ptr;}
	bool operator!=(const _Myiter& _right) const{return _ptr != _right._ptr;}

public:
	_innerPointer getPointer() const{return _ptr;}

protected:
	_innerPointer _ptr;

};

template<class _Iter>
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
	_list_inverse_iterator(const _Iter _right):_Iter(_right){}
	//下面两句的访问权限问题还没有想清楚
	//template<class _IterOther>
	//_list_inverse_iterator(const _IterOther& _right):_Iter(_right._ptr){}

public:
	//++,--
	_Myiter& operator++(){return _Iter::operator--();}
	_Myiter operator++(int){return _Iter::operator--(0);}
	_Myiter& operator--(){return _Iter::operator++();}
	_Myiter operator--(){return _Iter::operator++(0);}
};

template<class T, class _Alloc = allocator<T>>
struct list_node{
	typedef list_node<T, _Alloc> _Mylistnode;
	typedef typename _Alloc::value_type value_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;

	T value;
	_Mylistnode* prev;
	_Mylistnode* next;

	list_node():value(), prev(NULL), next(NULL){}
	list_node(const T& val):value(val), prev(NULL), next(NULL){}
	list_node(const T& val, _Mylistnode *_prev):value(val), prev(_prev), next(NULL){}
	list_node(const T& val, _Mylistnode *_prev, _Mylistnode *_next):value(val), prev(_prev), next(_next){}
};

template<class T, class _Alloc = allocator<T>>
class list{
public:
	//typedefs
	typedef list<T, _Alloc> _Mylist;
	typedef list_node<T, _Alloc> _Mylistnode;
	typedef allocator<_Mylistnode> _nodeAlloc;
	typedef typename _nodeAlloc::pointer node_pointer;
	typedef typename _Alloc::value_type value_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;
	typedef _list_iterator_base<_Mylist, pointer, reference> iterator;
	typedef _list_iterator_base<_Mylist, const_pointer, const_reference> const_iterator;
	typedef _list_inverse_iterator<iterator> reverse_iterator;
	typedef _list_inverse_iterator<const_iterator> const_reverse_iterator;

public:
	//constructions & destruction
	list();
	list(size_type init_size);
	list(size_type init_size, const T& elem);
	list(const _Mylist& _right);
	list(const_iterator _begin, const_iterator _end);
	~list();

public:
	//Updating
	//=
	_Mylist& operator=(const _Mylist& _right);

	//assign
	void assign(size_type n, const T& elem);
	void assign(const_iterator _begin, const_iterator _end);

	//insert
	iterator insert(iterator pos, const T& elem);
	iterator insert(iterator pos, size_type n, const T& elem);
	iterator insert(iterator pos, const_iterator _begin, const_iterator _end);

	//clear, erase
	void clear();
	iterator erase(iterator pos);

	//push, pop
	void push_back(const T& elem);
	void pop_back();
	void push_front(const T& elem);
	void pop_front();

	//resize
	void resize(size_type n);
	void resize(size_type n, const T& elem);

	//swap
	void swap(const _Mylist& _right);

public:
	//Queries
	//begin, end
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	//rbegin, rend
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	//front, back
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	//empty
	bool empty() const;
	//size
	size_type size() const;
	//size_type max_size()
	

public:
	//advanced operations
	//merge
	void merge(const _Mylist& _right);
	void merge(const _Mylist& _right, bool (*is_less_than)(const T&, const T&));
	//splice
	void splice(iterator pos, const _Mylist& _right);
	void splice(iterator pos, const _Mylist& _right, iterator pos2);
	void splice(iterator pos, const _Mylist& _right, iterator _begin, iterator _end);
	//remove elements with a certain value
	void remove(const T& value);
	void remove_if(bool (*cond)(const T&));
	//reverse
	void reverse();
	//unique
	void unique();
	//sort
	void sort();
	void sort(bool (*is_less_than)(const T&));

protected:
	_Mylistnode *_head;
	_Mylistnode *_tail;
	size_type _size;

};

_CXS_NS_END

#include "list_impl.h"

#endif