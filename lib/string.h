#pragma once

#ifndef _CXS_STRING_H_
#define _CXS_STRING_H

#include "cxs-commons.h"
#include "vector.h"
#include "allocator.h"

_CXS_NS_BEGIN

class string: public vector<char>{
public:
	string():_vecT(){}
	string(const char* str);
	string(const string& _right);
	string(string&& _right);
	~string();

public:
	string& operator=(const string& _right);
	string& operator=(string&& _right);
	string& operator+=(const string& _right);
	string operator+(const string& _right);
	string operator+(const char* _right);
	string operator+(char c);
	bool operator==(const string& _right) const;
	bool operator!=(const string& _right) const;
	bool operator>=(const string& _right) const;
	bool operator<=(const string& _right) const;
	bool operator>(const string& _right) const;
	bool operator<(const string& _right) const;
	bool operator==(const char* _right) const;
	bool operator!=(const char* _right) const;
	bool operator>=(const char* _right) const;
	bool operator<=(const char* _right) const;
	bool operator>(const char* _right) const;
	bool operator<(const char* _right) const;

public:
	string& replace (size_type pos,  size_type len,  const string& str);
	string& replace (iterator i1, iterator i2, const string& str);
	string& replace (size_type pos,  size_type len,  const string& str,
                 size_type subpos, size_type sublen);
	string& replace (size_type pos,  size_type len,  const char* s);
	string& replace (iterator i1, iterator i2, const char* s);
	string& replace (size_type pos,  size_type len,  const char* s, size_type n);
	string& replace (iterator i1, iterator i2, const char* s, size_type n);
	string& replace (size_type pos,  size_type len,  size_type n, char c);
	string& replace (iterator i1, iterator i2, size_type n, char c);
	template <class InputIterator>
	string& replace (iterator i1, iterator i2,
                   InputIterator first, InputIterator last);
	
	void swap(string& _right);

public:
	const char* c_str() const;
	const char* data() const;
	size_type copy(char* s, size_type len, size_type pos = 0) const;
	//find
	size_type find(const string& str, size_type pos = 0) const;
	size_type find(const char* s, size_type pos = 0) const;
	size_type find(const char* s, size_type pos, size_type n) const;
	size_type find(char c, size_type pos = 0) const;
	//rfind
	size_type rfind(const string& str, size_type pos) const;
	size_type rfind(const char* s, size_type pos) const;
	size_type rfind(const char* s, size_type pos, size_type n) const;
	size_type rfind(char c, size_type pos) const;
	//find_first_of
	size_type find_first_of(const string& str, size_type pos = 0) const;
	size_type find_first_of(const char* s, size_type pos = 0) const;
	size_type find_first_of(const char* s, size_type pos, size_type n) const;
	size_type find_first_of(char c, size_type pos = 0) const;
	//find_last_of
	size_type find_last_of(const string& str, size_type pos) const;
	size_type find_last_of(const char* s, size_type pos) const;
	size_type find_last_of(const char* s, size_type pos, size_type n) const;
	size_type find_last_of(char c, size_type pos) const;
	//find_first_not_of
	size_type find_first_not_of(const string& str, size_type pos = 0) const;
	size_type find_first_not_of(const char* s, size_type pos = 0) const;
	size_type find_first_not_of(const char* s, size_type pos, size_type n) const;
	size_type find_first_not_of(char c, size_type pos = 0) const;
	//find_last_not_of
	size_type find_last_not_of(const string& str, size_type pos) const;
	size_type find_last_not_of(const char* s, size_type pos) const;
	size_type find_last_not_of(const char* s, size_type pos, size_type n) const;
	size_type find_last_not_of(char c, size_type pos) const;
	//substr
	string substr(size_type pos, size_type len) const;
	//compare
	int compare(const string& str) const;
	int compare (size_type pos, size_type len, const string& str) const;
	int compare (size_type pos, size_type len, const string& str,
	             size_type subpos, size_type sublen) const;
	int compare (const char* s) const;
	int compare (size_type pos, size_type len, const char* s) const;
	int compare (size_type pos, size_type len, const char* s, size_type n) const;
	//length
	size_type length() const{return _size;}
	
};

string operator+(const char* str1, const string& str2);
string operator+(char c, const string& str2);
bool operator==(const char* str1, const string& str2);
bool operator!=(const char* str1, const string& str2);
bool operator>=(const char* str1, const string& str2);
bool operator<=(const char* str1, const string& str2);
bool operator>(const char* str1, const string& str2);
bool operator<(const char* str1, const string& str2);
std::istream& operator>>(std::istream& in, string& str);
std::ostream& operator<<(std::ostream& in, const string& str);
std::istream& getline (std::istream& in, string& str, char delim = '\n');


_CXS_NS_END

#endif