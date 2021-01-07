#pragma once

#include "List.hpp"
#include "Vector.hpp"
#include <utility>

template<class K, class V, class HashFunc = hash<K>>
class HashTable
{
private:
	Vector<List<std::pair<K, V>>> buffer;
	size_t size;

private:
	static bool cmp(const K& key_, const std::pair<K, V>& node_)
	{
		return key_ == node_.first;
	}
	ListNode<std::pair<K, V>>* _Find(const K& key_)
	{
		return this->buffer
			.At(HashFunc()(key_) % buffer.GetSize())
			.FindNode(key_, HashTable::cmp);
	}
	void Rehash()
	{
		// todo: adjust hash table size
	}

public:
	//HashTable() : size(0), buffer() { buffer.Resize(newSize >> 1); }
	HashTable() : size(0), buffer(newSize >> 1) {}
	HashTable(const HashTable& table_) : size(table_.size), buffer(table_.buffer) {}
	~HashTable() {}

	V* Find(const K& key_)
	{
		auto ptr = _Find(key_);
		return ptr ? &(ptr->dat->second) : nullptr;
	}
	void Insert(const K& key_, const V& value_)
	{
		auto ptr = _Find(key_);
		if (!ptr)
		{
			this->buffer.At(HashFunc()(key_) % buffer.GetSize())
				.PushFront({ key_, value_ });
			++size;
		}
		else
			ptr->dat->second = value_;
	}
	void Erase(const K& key_)
	{
		auto ptr = _Find(key_);
		if (!ptr)
			return;
		this->buffer.At(HashFunc()(key_) % buffer.GetSize()).Erase(ptr);
		--size;
	}
	V& operator[](const K& key_)
	{
		auto ptr = Find(key_);
		if (ptr != nullptr)
			return *ptr;
		Insert(key_, V());
		return *Find(key_);
	} 
	size_t GetSize() const
	{
		return this->size;
	}
};