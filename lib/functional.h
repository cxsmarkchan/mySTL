#pragma once

//һЩ���õĹ��ܣ�����less, greater��

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

_CXS_NS_END

#endif
