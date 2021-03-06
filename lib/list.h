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
class _list_reverse_iterator: public _Iter{
public:
	//typedefs
	typedef _list_reverse_iterator<_Iter> _Myiter;
	typedef typename _Iter::_innerPointer _innerPointer;
	typedef typename _Iter::size_type size_type;
	typedef typename _Iter::difference_type difference_type;
	typedef typename _Iter::pointer pointer;
	typedef typename _Iter::reference reference;

public:
	//constructions
	_list_reverse_iterator():_Iter(){}
	_list_reverse_iterator(_innerPointer p):_Iter(p){}
	_list_reverse_iterator(const _Myiter& _right):_Iter(_right._ptr){}
	_list_reverse_iterator(const _Iter& _right):_Iter(_right){}
	//template<class _IterOther>
	//_list_reverse_iterator(const _IterOther& _right):_Iter(_right.getPointer()){}

public:
	//++,--
	_Myiter& operator++(){_Iter::operator--(); return *this;}
	_Myiter operator++(int){return _Myiter(_Iter::operator--(0));}
	_Myiter& operator--(){_Iter::operator++(); return *this;}
	_Myiter operator--(int){return _Myiter(_Iter::operator++(0));}
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
	typedef _list_reverse_iterator<iterator> reverse_iterator;
	typedef _list_reverse_iterator<const_iterator> const_reverse_iterator;

public:
	//constructions & destruction
	list();
	list(size_type init_size);
	list(size_type init_size, const T& elem);
	list(const _Mylist& _right);
	list(_Mylist&& _right);
	list(const_iterator _begin, const_iterator _end);
	~list();

public:
	//Updating
	//=
	_Mylist& operator=(const _Mylist& _right);
	_Mylist& operator=(_Mylist&& _right);

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
	void swap(_Mylist& _right);

	//新增接口，把节点断开并返回，而不删除
	iterator erase_return(iterator _it);
	//新增接口，直接将一个节点插入，而不用复制
	iterator insert_exist(iterator pos, iterator _it_elem);

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
	//将_right中的所有元素清空，并有序地插入排到本列表中。如果两个元素相等，则本列表的元素在前，_right元素在后。
	//只有本列表和_right列表均有序的时候，merge的结果才有序。
	void merge(_Mylist& _right);
	template<class _Pred>
	void merge(_Mylist& _right, _Pred _pred);
	//splice，列表拼接
	void splice(iterator pos, _Mylist& _right);//将_right拼接到pos前，并清空_right
	void splice(iterator pos, _Mylist& _right, iterator pos2);//将_right中的pos2拼接到pos前，并在_right中删除pos2
	void splice(iterator pos, _Mylist& _right, iterator _begin, iterator _end);//将_right中[_begin, _end)拼接到pos前，并在_right中删除这些元素
	//remove elements with a certain value
	void remove(const T& value);
	template<class _Pred>
	void remove_if(_Pred pred);// if _Pred(val), remove val
	//reverse
	void reverse();
	//unique
	//剔除重复元素，重复判据为连续相等。即：如果两个相等元素中间隔有若干不相等的元素，则这两个元素均会被保留。
	void unique();
	//sort，采用快速排序技术，平均时间复杂度O(nlogn)，平均空间复杂度O(logn)
	//目前采用的算法是以列表第一个元素作为分界点，因此在顺序数组的情况下会出现最坏情况。
	void sort();
	template<class _Pred>
	void sort(_Pred _pred);
	//stable_sort，采用归并排序技术，似乎标准STL模板中采用的是这种方法
	void stable_sort();
	template<class _Pred>
	void stable_sort(_Pred _pred);

protected:
	_Mylistnode *_head;
	_Mylistnode *_tail;
	size_type _size;

protected:
	template<class _Pred>
	void sort(iterator _begin, iterator _end, _Pred _pred);
	template<class _Pred>
	iterator stable_sort(iterator _begin, size_type _size, _Pred _pred);

	//归并[_begin, _middle)和[_middle, _end)之间的元素
	template<class _Pred>
	void inner_merge(iterator _begin, iterator _middle, iterator _end, _Pred _pred);


};

_CXS_NS_END

#include "list_impl.h"

#endif