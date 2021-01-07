#pragma once

#include "HashTable.hpp"
#include "Hash.h"

template<class K, class Ar, class V>
class Trie
{
private:
	Vector<HashTable<K, size_t>> buffer;
	HashTable<size_t, V>indexTable;

public:
	Trie() : buffer(1) {}
	Trie(const Trie& trie_) 
		: buffer(trie_.buffer), indexTable(trie_.indexTable) {}
	~Trie() {}
	void Insert(const Ar& array_, const V& val_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K& nxt = array_[i];
			auto ptr = buffer[root].Find(nxt);
			if (!ptr)
			{
				buffer[root].Insert(nxt, buffer.GetSize());
				root = buffer.GetSize();
				buffer.PushBack(HashTable<K, size_t>());
			}
			else
				root = *ptr;
		}
		indexTable[root] = val_;
	}
	void Erase(const Ar& array_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K& nxt = array_[i];
			auto ptr = buffer[root].Find(nxt);
			if (!ptr)
				return;
			root = *ptr;
		}
		indexTable.Erase(root);
	}
	V* Find(const Ar& array_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K& nxt = array_[i];
			auto ptr = buffer[root].Find(nxt);
			if (!ptr)
				return nullptr;
			root = *ptr;
		}
		return indexTable.Find(root);
	}
	V* operator[](const Ar& array_)
	{
		return Find(array_);
	}
	size_t GetSize() const
	{
		return indexTable.GetSize();
	}
};

