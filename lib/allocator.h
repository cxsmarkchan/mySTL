#pragma once

// ʵ��allocator
// reference: STLԴ������

#ifndef _CXS_ALLOCATOR_H_
#define _CXS_ALLOCATOR_H_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
#include "cxs-commons.h"

_CXS_NS_BEGIN

typedef std::size_t size_t;
typedef std::ptrdiff_t ptrdiff_t;

//����4��inline������Ϊ�˰ѷ���/�����ڴ�͹���/�����������뿪
//�����ڴ棬�������ù��캯��
template<class T>
inline T* _allocate(ptrdiff_t size, T*){
	std::set_new_handler(0);
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if(tmp == NULL){
		cerr << "out of memory" << endl;
		exit(1);
	}
	return tmp;
}

//�����ڴ棬����������������
template<class T>
inline void _deallocate(T* buffer){
	::operator delete(buffer);
}

//���ù��캯��
template<class T1, class T2>
inline void _construct(T1* p, const T2& value){
	new(p) T1(value);
}

//������������
template<class T>
inline void _destroy(T* ptr){
	ptr->~T();
}


template<class T>
class allocator{
public:
	//typedefs
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef T const* const_pointer;
	typedef T const& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template<class _other>
	struct rebind{
		typedef allocator<_other> other;
	};

public:
	// constructions & destruction
	allocator(){}
	allocator(const allocator&){}
	template<class _other>
	allocator(const allocator<_other>&){}
	~allocator(){}

public:
	//����ĳ������ĵ�ַ
	pointer address(reference x) const{
		return (pointer)&x;
	}

	const_pointer address(const_reference x) const{
		return (const_pointer)&x;
	}

	//���ÿɴ洢n��T����Ŀռ�
	pointer allocate(size_type n, const void* = 0){
		return _allocate(n, (T*)0);
	}

	//�黹�ռ�
	void deallocate(pointer p, size_type n){
		_deallocate(p);
	}

	//�����õ������
	size_type max_size() const{
		return (size_type)(UINT_MAX/sizeof(T));
	}

	void construct(pointer p, const T& x){
		_construct(p, x);
	}
	void destroy(pointer p){
		_destroy(p);
	}

};

_CXS_NS_END

#endif