#pragma once


#ifndef _CXS_LIST_IMPLEMENT_H
#define _CXS_LIST_IMPLEMENT_H

#include "cxs-commons.h"
#include "list.h"

_CXS_NS_BEGIN

//constructions
template<class T, class _Alloc>
list<T, _Alloc>::list():_size(0){
	_head = new _Mylistnode();
	_tail = new _Mylistnode();
	_head->next = _tail;
	_tail->prev = _head;
}


template<class T, class _Alloc>
list<T, _Alloc>::list(size_type init_size):_size(init_size){
	_head = new _Mylistnode();
	_Mylistnode *tmp = _head;
	for(size_type i = 0; i < _size; i++){
		tmp->next = new _Mylistnode();
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	_tail = new _Mylistnode();
	tmp->next = _tail;
	_tail->prev = tmp;
}

template<class T, class _Alloc>
list<T, _Alloc>::list(size_type init_size, const T& elem):_size(init_size){
	_head = new _Mylistnode();
	_Mylistnode *tmp = _head;
	for(size_type i = 0; i < _size; i++){
		tmp->next = new _Mylistnode(elem, tmp);
		tmp = tmp->next;
	}
	_tail = new _Mylistnode();
	tmp->next = _tail;
	_tail->prev = tmp;
}

template<class T, class _Alloc>
list<T, _Alloc>::list(const _Mylist& _right):_size(_right._size){
	_head = new _Mylistnode();
	_Mylistnode *tmp1 = _head;
	_Mylistnode *tmp2 = _right._head->next;
	while(tmp2 != NULL){
		tmp1->next = new _Mylistnode(tmp2->value, tmp1);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	_tail = tmp1;
}

template<class T, class _Alloc>
list<T, _Alloc>::list(_Mylist&& _right):_size(_right.size), _head(_right._head), _tail(_right._tail){
	_right._head = NULL;
	_right._tail = NULL;
}

template<class T, class _Alloc>
list<T, _Alloc>::list(const_iterator _begin, const_iterator _end){
	_size = 0;
	_head = new _Mylistnode();
	_Mylistnode *tmp1 = _head;
	const_iterator tmp2 = _begin;
	while(tmp2 != _end){
		tmp1->next = new _Mylistnode(*tmp2, tmp1);
		tmp1 = tmp1->next;
		tmp2++;
		_size++;
	}
	_tail = new _Mylistnode();
	tmp1->next = _tail;
	_tail->prev = tmp1;
}

//destructions
template<class T, class _Alloc>
list<T, _Alloc>::~list(){
	_Mylistnode *tmp = _head;
	_Mylistnode *del;
	while(tmp != NULL){
		del = tmp;
		tmp = tmp->next;
		delete del;
	}
}

///////////////////////////////////////////////////////////////////////////////////
// Operators
template<class T, class _Alloc>
list<T, _Alloc>& list<T, _Alloc>::operator=(const _Mylist& _right){
	if(this != &_right){
		_size = _right._size;

		_Mylistnode *tmp = _head;
		_Mylistnode *del;
		while(!tmp != NULL){
			del = tmp;
			tmp = tmp->next;
			delete del;
		}
		_head = new _Mylistnode(_right._head->value);
		_Mylistnode *tmp1 = _head;
		_Mylistnode *tmp2 = _right._head->next;
		while(tmp2 != NULL){
			tmp1->next = new _Mylistnode(tmp2->value, tmp1);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		_tail = tmp1;
	}
	return *this;
}

template<class T, class _Alloc>
list<T, _Alloc>& list<T, _Alloc>::operator=(_Mylist&& _right){
	if(this != &_right){
		_Mylistnode *tmp = _head;
		_Mylistnode *del;
		while(!tmp != NULL){
			del = tmp;
			tmp = tmp->next;
			delete del;
		}
		_size = _right._size;
		_head = _right._head;
		_tail = _right._tail;
		_right._head = NULL;
		_right._tail = NULL;
	}
	return *this;
}


//begin
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::begin(){
	return iterator(_head->next);
}

//end
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::end(){
	return iterator(_tail);
}
//size
template<class T, class _Alloc>
typename list<T, _Alloc>::size_type list<T, _Alloc>::size() const{
	return _size;
}

_CXS_NS_END

#endif