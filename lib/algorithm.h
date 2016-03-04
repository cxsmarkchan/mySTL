#pragma once
//algorithm.h
//一些相关的算法和通用操作

#ifndef _CXS_ALGORITHM_H_
#define _CXS_ALGORITHM_H_

#include <iostream>
#include "cxs-commons.h"

_CXS_NS_BEGIN

//swap
template<class T>
void swap(T& var1, T& var2){
	T tmp = std::move(var1);
	var1 = std::move(var2);
	var2 = std::move(tmp);
}

_CXS_NS_END

#endif