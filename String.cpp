#include "String.h"

const size_t newSize = 16;

String::String()
{
	this->size = newSize;
	this->buffer = new char[newSize];
}
String::String(const char* str_)
{
	this->size = strlen(str_);
	buffer = new char[this->size + 1];
	strcpy(this->buffer, str_);
	buffer[this->size] = 0;
}
String::String(const char* str_, size_t size_)
{
	this->size = std::min(size_, strlen(str_));
	buffer = new char[this->size + 1];
	memcpy(this->buffer, str_, this->size);
	buffer[this->size] = 0;
}
String::String(const char ch_, size_t size_)
{
	this->size = size_;
	buffer = new char[this->size + 1];
	buffer[this->size] = 0;
	memset(buffer, ch_, size_);
}
String::String(const String& str_)
{
	this->size = str_.size;
	buffer = new char[this->size + 1];
	strcpy(this->buffer, str_.buffer);
	buffer[this->size] = 0;
}
String::~String()
{
	delete[]this->buffer;
}

size_t String::GetSize() const
{
	return this->size;
}
void String::Append(const String& str_)
{
	char* buffer = new char[this->size + str_.size + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_.buffer);
	this->size += str_.size;
	buffer[this->size] = 0;
	delete[]this->buffer;
	this->buffer = buffer;
}
void String::Append(const char* str_)
{
	size_t size_ = strlen(str_);
	char* buffer = new char[this->size + size_ + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_);
	this->size += size_;
	buffer[this->size] = 0;
	delete[]this->buffer;
	this->buffer = buffer;
}
void String::Append(const char* str_, size_t size_)
{
	size_t size = std::min(strlen(str_), size_);
	char* buffer = new char[this->size + size + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_);
	this->size += size;
	buffer[this->size] = 0;
	delete[]this->buffer;
	this->buffer = buffer;
}
void String::Append(const char ch_)
{
	char* buffer = new char[this->size + 2];
	strcpy(buffer, this->buffer);
	buffer[this->size] = ch_;
	buffer[++this->size] = 0;
	delete[]this->buffer;
	this->buffer = buffer;
}
const char* String::GetCstr() const
{
	return this->buffer;
}

char& String::operator[](size_t index_)
{
	if (index_ >= this->size || index_ < 0)
		throw std::out_of_range("index out of range");
	return buffer[index_];
}

const char& String::operator[](size_t index_) const
{
	if (index_ >= this->size || index_ < 0)
		throw std::out_of_range("index out of range");
	return buffer[index_];
}

String operator+(const String& str1_, const String& str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const String& str1_, const char* str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const String& str1_, const char ch2_)
{
	String str(str1_);
	str.Append(ch2_);
	return str;
}
String operator+(const char* str1_, const String& str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const char ch1_, const String& str2_)
{
	String str(ch1_, 1);
	str.Append(str2_);
	return str;
}

bool String::operator==(const String& str_) const
{
	return this->size == str_.size && !strcmp(this->buffer, str_.buffer);
}