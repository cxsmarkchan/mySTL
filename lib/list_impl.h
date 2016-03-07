#pragma once


#ifndef _CXS_LIST_IMPLEMENT_H
#define _CXS_LIST_IMPLEMENT_H

#include "cxs-commons.h"
#include "list.h"
#include "functional.h"
#include "algorithm.h"

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
list<T, _Alloc>::list(_Mylist&& _right):_size(_right._size), _head(_right._head), _tail(_right._tail){
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
		while(tmp != NULL){
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
		while(tmp != NULL){
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

/////////////////////////////////////////////////////////////////
//assign
template<class T, class _Alloc>
void list<T, _Alloc>::assign(size_type n, const T& elem){
	clear();
	_Mylistnode *cur = _head;
	for(size_type i = 0; i < n; i++){
		cur->next = new _Mylistnode(elem, cur);
		cur = cur->next;
	}
	cur->next = _tail;
	_tail->prev = cur;
	_size = n;
}

template<class T, class _Alloc>
void list<T, _Alloc>::assign(const_iterator _begin, const_iterator _end){
	clear();
	_Mylistnode *cur = _head;
	for(const_iterator _it = _begin; _it != _end; _it++){
		cur->next = new _Mylistnode(*_it, cur);
		cur = cur->next;
		_size++;
	}
	cur->next = _tail;
	_tail->prev = cur;
}

/////////////////////////////////////////////////////////////////////
//insert functions
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::insert(iterator pos, const T& elem){
	_Mylistnode *_cur = pos.getPointer();
	_Mylistnode *_ins = new _Mylistnode(elem, _cur->prev, _cur);
	_cur->prev->next = _ins;
	_cur->prev = _ins;
	_size++;
	return iterator(_ins);
}

template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::insert(iterator pos, size_type n, const T& elem){
	_Mylistnode *_cur = pos.getPointer();
	for(size_type i = 0; i < n; i++){
		_Mylistnode *_ins = new _Mylistnode(elem, _cur->prev, _cur);
		_cur->prev = _ins;
		_cur = _cur->prev;
		_size++;
	}
	_cur->prev->next = _cur;
	return _cur;
}


template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::insert(iterator pos, const_iterator _begin, const_iterator _end){
	_Mylistnode *_cur = pos.getPointer();
	for(const_iterator _it = _end; _it != _begin;){
		_Mylistnode *_ins = new _Mylistnode(*(--_it), _cur->prev, _cur);
		_cur->prev = _ins;
		_cur = _cur->prev;
		_size++;
	}
	_cur->prev->next = _cur;
	return _cur;
}
/////////////////////////////////////////////////////////////////////
//erase functions

//clear
template<class T, class _Alloc>
void list<T, _Alloc>::clear(){
	while(_head->next != _tail){
		_Mylistnode *tmp = _head->next;
		_head->next = _head->next->next;
		delete tmp;
	}
	_tail->prev = _head;
	_size = 0;
}

//erase
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::erase(iterator pos){
	_Mylistnode *_cur = pos.getPointer();
	_Mylistnode *_prev = _cur->prev;
	_Mylistnode *_next = _cur->next;
	_prev->next = _next;
	_next->prev = _prev;
	delete _cur;
	_size--;
	return iterator(_next);
}

/////////////////////////////////////////////////////////////////////
//push and pop
template<class T, class _Alloc>
void list<T, _Alloc>::push_back(const T& elem){
	_Mylistnode *_cur = new _Mylistnode(elem, _tail->prev, _tail);
	_tail->prev->next = _cur;
	_tail->prev = _cur;
	_size++;
}


template<class T, class _Alloc>
void list<T, _Alloc>::push_front(const T& elem){
	_Mylistnode *_cur = new _Mylistnode(elem, _head, _head->next);
	_head->next->prev = _cur;
	_head->next = _cur;
	_size++;
}

template<class T, class _Alloc>
void list<T, _Alloc>::pop_back(){
	_Mylistnode *_cur = _tail->prev;
	_tail->prev = _tail->prev->prev;
	_tail->prev->next = _tail;
	delete _cur;
	_size--;
}

template<class T, class _Alloc>
void list<T, _Alloc>::pop_front(){
	_Mylistnode *_cur = _head->next;
	_head->next = _head->next->next;
	_head->next->prev = _head;
	delete _cur;
	_size--;
}

////////////////////////////////////////////////////////////////
//resize
template<class T, class _Alloc>
void list<T, _Alloc>::resize(size_type n){
	resize(n, T());
}

template<class T, class _Alloc>
void list<T, _Alloc>::resize(size_type n, const T& elem){
	if(_size < n){
		insert(end(), n - _size, elem);
	}else{
		for(size_type i = 0; i < _size - n; i++){
			_Mylistnode *tmp = _tail->prev;
			_tail->prev = _tail->prev->prev;
			delete tmp; 
		}
		_tail->prev->next = _tail;
		_size = n;
	}
}

//////////////////////////////////////////////////////////////////
//swap
template<class T, class _Alloc>
void list<T, _Alloc>::swap(_Mylist& _right){
	cxs::swap(*this, _right);
}

/////////////////////////////////////////////////////////////////
//erase_return
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::erase_return(iterator _it){
	_Mylistnode *node = _it.getPointer();
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->prev = node->next = NULL;
	_size--;
	return node;
}

//insert_exist
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::insert_exist(iterator pos, iterator _it_elem){
	_Mylistnode *_to = pos.getPointer();
	_Mylistnode *_from = _it_elem.getPointer();
	_to->prev->next = _from;
	_from->prev = _to->prev;
	_from->next = _to;
	_to->prev = _from;
	_size++;
	return iterator(_from);
}
/////////////////////////////////////////////////////////////////
//queries

//begin
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::begin(){
	return iterator(_head->next);
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_iterator list<T, _Alloc>::begin() const{
	return const_iterator(_head->next);
}

//end
template<class T, class _Alloc>
typename list<T, _Alloc>::iterator list<T, _Alloc>::end(){
	return iterator(_tail);
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_iterator list<T, _Alloc>::end() const{
	return const_iterator(_tail);
}

//rbegin
template<class T, class _Alloc>
typename list<T, _Alloc>::reverse_iterator list<T, _Alloc>::rbegin(){
	return reverse_iterator(_tail->prev);
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_reverse_iterator list<T, _Alloc>::rbegin() const{
	return const_reverse_iterator(_tail->prev);
}

//rend
template<class T, class _Alloc>
typename list<T, _Alloc>::reverse_iterator list<T, _Alloc>::rend(){
	return reverse_iterator(_head);
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_reverse_iterator list<T, _Alloc>::rend() const{
	return const_reverse_iterator(_head);
}

//front
template<class T, class _Alloc>
typename list<T, _Alloc>::reference list<T, _Alloc>::front(){
	return _head->next->value;
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_reference list<T, _Alloc>::front() const{
	return _head->next->value;
}


//back
template<class T, class _Alloc>
typename list<T, _Alloc>::reference list<T, _Alloc>::back(){
	return _tail->prev->value;
}

template<class T, class _Alloc>
typename list<T, _Alloc>::const_reference list<T, _Alloc>::back() const{
	return _tail->prev->value;
}

template<class T, class _Alloc>
bool list<T, _Alloc>::empty() const{
	return (_size == 0);
}

//size
template<class T, class _Alloc>
typename list<T, _Alloc>::size_type list<T, _Alloc>::size() const{
	return _size;
}

//merge
template<class T, class _Alloc>
template<class _Pred>
void list<T, _Alloc>::merge(_Mylist& _right, _Pred _pred){
	iterator _it1 = begin();
	iterator _it2 = _right.begin();
	while(_it1 != end() && _it2 != _right.end()){
		if(_pred(*_it2, *_it1)){ //*_it2 < *_it1 应该把_it2插入到_it1前面
			iterator _from = _it2;
			_it2++;
			iterator _it_tmp = _right.erase_return(_from);
			insert_exist(_it1, _it_tmp);
		}else{ //其他情况下，_it1在前面，但因为我们是合并到本列表，所以无需移动
			_it1++;
		}
	}
	if(_it2 != _right.end()){
		splice(end(), _right, _it2, _right.end());
	}
}

template<class T, class _Alloc>
void list<T, _Alloc>::merge(_Mylist& _right){
	merge(_right, less<T>());
}

//splice
template<class T, class _Alloc>
void list<T, _Alloc>::splice(iterator pos, _Mylist& _right, iterator _begin, iterator _end){
	for(iterator _it = _begin; _it != _end;){
		iterator _from = _it;
		_it++;
		_from = _right.erase_return(_from);
		insert_exist(pos, _from);
	}
}

template<class T, class _Alloc>
void list<T, _Alloc>::splice(iterator pos, _Mylist& _right, iterator pos2){
	iterator _end = pos2;
	iterator _begin = _end++; //这样_begin指向pos2，_end指向pos2后一个位置
	splice(pos, _right, _begin, _end);
}

template<class T, class _Alloc>
void list<T, _Alloc>::splice(iterator pos, _Mylist& _right){
	splice(pos, _right, _right.begin(), _right.end());
}
_CXS_NS_END

#endif