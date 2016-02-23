#pragma once

#ifndef _CXS_ALLOCATOR_H_
#define _CXS_ALLOCATOR_H_

#include "cxs-commons.h"

_CXS_NS_BEGIN

template<class T>
class allocator{
public:
	//typedefs
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef T const* const_pointer;
	typedef T const& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template<class _other>
	struct rebind{
		typedef allocator<_other> other;
	};

public:
	// constructions & destruction
	allocator();
	allocator(const allocator&);
	template<class _other>
	allocator(const allocator<_other>&);
	~allocator();

public:
	pointer address(reference x) const; //返回某个对象的地址
	const_pointer address(const_reference x) const;
	pointer allocate(size_type n, const void* = 0); //配置可存储n个T对象的空间
	void deallocate(pointer p, size_type n); //归还空间
	size_type max_size() const; //可配置的最大量
	void construct(pointer p, const T& x); 
	void destroy(pointer p);

};

_CXS_NS_END

#include "allocator_impl.h"

#endif