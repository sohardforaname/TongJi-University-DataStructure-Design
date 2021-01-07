#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <stdexcept>
#include <algorithm>

//class String;

class String
{
private:
	char* buffer;
	size_t size;

public:
	String();
	String(const char* str_);
	String(const char* str_, size_t size_);
	String(const char ch_, size_t size_);
	String(const String& str_);
	~String();

	size_t GetSize() const;
	void Append(const String& str_);
	void Append(const char* str_);
	void Append(const char* str_, size_t size_);
	void Append(const char ch_);
	const char* GetCstr() const;
	const char& operator[](size_t index_) const;
	char& operator[](size_t index_);
	bool operator==(const String& str_) const;
};

String operator+(const String& str1_, const String& str2_);
String operator+(const String& str1_, const char* str2_);
String operator+(const String& str1_, const char ch2_);
String operator+(const char* str1_, const String& str2_);
String operator+(const char ch1_, const String& str2_);