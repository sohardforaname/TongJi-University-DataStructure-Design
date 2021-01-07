#pragma once

const size_t cBeginVal = 998244353;
const size_t mulFactor = 16777619;

template<class T>
struct hash
{
	static size_t GetHash(const unsigned char* valPtr, const size_t& size)
	{
		size_t beginVal = cBeginVal;
		for (size_t i = 0; i < size; ++i)
			beginVal = (beginVal ^ valPtr[i]) * mulFactor;
		return beginVal;
	}

	size_t operator()(const T& key)
	{
		return this->GetHash(reinterpret_cast<const unsigned char*>(&key), sizeof(T));
	}
};