#pragma once

//一些常用的功能，例如less, greater等

#ifndef _CXS_FUNCTIONAL_H_
#define _CXS_FUNCTIONAL_H_

#include "cxs-commons.h"

_CXS_NS_BEGIN

template<class T>
struct less{
	bool operator() (const T& first, const T& second) const{
		return first < second;
	}
};

template<class T>
struct greater{
	bool operator() (const T& first, const T& second) const{
		return first > second;
	}
};

template<class T>
struct equal{
	bool operator()(const T& first, const T& second) const{
		return first == second;
	}
};

template<class T>
struct equal_to{
	const T _benchmark;
	equal_to(const T& benchmark):_benchmark(benchmark){}
	bool operator()(const T& elem) const{
		return elem == _benchmark;
	}
};


_CXS_NS_END

#endif
