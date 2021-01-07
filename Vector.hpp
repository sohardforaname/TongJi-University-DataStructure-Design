#pragma once

#include <stdexcept>

const size_t newSize = 16;

template<class T>
class Vector
{
private:
	T* dat;
	size_t size, capacity;

private:
	void Reserve(size_t capacity_)
	{
		if (this->capacity >= capacity_)
			return;
		//T* dat_ = reinterpret_cast<T*>(malloc(sizeof(T) * capacity_));
		T* dat_ = (T*)malloc(sizeof(T) * capacity_);
		for (size_t i = 0; i < this->size; ++i)
			new (dat_ + i) T(dat[i]);
		for (size_t i = 0; i < this->size; ++i)
			this->dat[i].~T();
		free(dat);
		dat = dat_;
		this->capacity = capacity_;
	}

public:
	Vector() 
	{
		this->size = 0;
		this->capacity = newSize;
		dat = (T*)malloc(sizeof(T) * this->capacity);
	}
	Vector(size_t size_) 
	{
		this->size = size_;
		this->capacity = std::max(size_, newSize);
		dat = (T*)malloc(sizeof(T) * this->capacity);
		for (size_t i = 0; i < this->size; ++i)
			new (dat + i) T();
	}
	Vector(size_t size_, const T& dat_)
	{
		this->size = size_;
		this->capacity = std::max(size_, newSize);
		dat = (T*)malloc(sizeof(T) * this->capacity);
		for(size_t i =0 ;i<this->size; ++i)
			new (dat + i) T(dat_);
	}
	Vector(const Vector& vec_)
	{
		this->size = vec_.size;
		this->capacity = vec_.capacity;
		dat = (T*)malloc(sizeof(T) * this->capacity);
		for (size_t i = 0; i < this->size; ++i)
			new (dat + i) T(vec_.dat[i]);
	}
	~Vector()
	{
		for (size_t i = 0; i < this->size; ++i)
			;//this->dat[i].~T();
		free(dat);
	}

	size_t GetSize() const
	{
		return this->size;
	}
	size_t GetCapacity()
	{
		return this->capacity;
	}
	void Resize(size_t size_)
	{
		Reserve(size_ + (size_ >> 1));
		if (this->size <= size_)
			for (size_t i = this->size; i < size_; ++i)
				new(dat + size++) T();
		else
			for (size_t i = this->size; i > size_; --i)
				PopBack();
		this->size = size_;
	}
	void PushBack(const T& dat_)
	{
		if (this->size == this->capacity)
			Reserve(this->capacity + (this->capacity >> 1));
		new(dat + size++) T(dat_);
	}
	void PopBack()
	{
		--this->size;
		if (this->size < (this->capacity >> 2))
			Reserve(this->capacity >> 1);
	}
	void Append(const Vector& vec_)
	{
		if (this->capacity < this->size + vec_.size)
			Reserve(this->size + vec_.size);
		for (size_t i = 0; i < vec_.size; ++i)
			this->dat[i + this->size] = vec_.dat[i];
		this->size += vec_.size;
	}
	void Erase(const size_t& index_)
	{
		if (index_ >= this->size)
			throw std::out_of_range("index out of range");
		for (size_t i = index_; i < this->size - 1; ++i)
		{
			dat[i].~T();
			new (dat + i) T(dat[i + 1]);
		}
		--this->size;
		if (this->size < (this->capacity >> 2))
			Reserve(this->capacity >> 1);
	}
	T& At(size_t index_)
	{
		if (index_ >= this->size)
			throw std::out_of_range("index out of range");
		return dat[index_];
	}
	T& operator[](size_t index_)
	{
		return At(index_);
	}
	const T& At(size_t index_) const
	{
		if (index_ >= this->size)
			throw std::out_of_range("index out of range");
		return dat[index_];
	}
	const T& operator[](size_t index_) const
	{
		return At(index_);
	}
	bool operator==(const Vector& vec_)
	{
		if (this->size != vec_.size)
			return false;
		for (size_t i = 0; i < this->size; ++i)
			if (!(this->dat[i] == vec_.dat[i]))
				return false;
		return true;
	}
	bool operator!=(const Vector& vec_)
	{
		return !(*this == vec_);
	}
};