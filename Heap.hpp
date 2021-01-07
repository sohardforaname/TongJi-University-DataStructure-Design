#pragma once

#include "Vector.hpp"

template<class T>
class Heap
{
private:
	Vector<T>buffer;

	void HeapAdjustUp(size_t index_)
	{
		size_t cur = index_;
		size_t par = (cur - 1) / 2;
		T tmp = buffer[index_];

		while (cur > 0)
		{
			if (!(buffer[par] < tmp))
				break;
			buffer[cur] = buffer[par];
			cur = par;
			par = (par - 1) / 2;

		}

		buffer[cur] = tmp;
	}
	void HeapAdjustDown(size_t beg_, size_t end_)
	{
		size_t cur = beg_;
		size_t lc = (beg_ << 1) + 1;
		T tmp = buffer[beg_];

		while (lc <= end_)
		{
			if (lc < end_ && buffer[lc] < buffer[lc + 1])
				++lc;
			if (!(tmp < buffer[lc]))
				break;
			buffer[cur] = buffer[lc];
			cur = lc;
			lc = (lc << 1) + 1;
		}

		buffer[cur] = tmp;
	}

public:
	Heap() {}
	Heap(const Heap& heap_) : buffer(heap_.buffer) {}
	~Heap() {}

	size_t GetSize()
	{
		return buffer.GetSize();
	}

	void Push(const T& val_)
	{
		buffer.PushBack(val_);
		HeapAdjustUp(buffer.GetSize() - 1);
	}

	void Pop()
	{
		if (!buffer.GetSize())
			throw std::out_of_range("empty heap");
		std::swap(buffer[0], buffer[buffer.GetSize() - 1]);
		buffer.PopBack();
		if (buffer.GetSize())
			HeapAdjustDown(0, buffer.GetSize() - 1);
	}

	const T& GetTop()
	{
		return buffer[0];
	}
};