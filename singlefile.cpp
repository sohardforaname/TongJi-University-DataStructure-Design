#include <algorithm>
#include <cstring>
#include <stdexcept>

class String
{
private:
	char *buffer;
	size_t size;

public:
	String();
	String(const char *str_);
	String(const char *str_, size_t size_);
	String(const char ch_, size_t size_);
	String(const String &str_);
	~String();

	size_t GetSize() const;
	void Append(const String &str_);
	void Append(const char *str_);
	void Append(const char *str_, size_t size_);
	void Append(const char ch_);
	const char *GetCstr() const;
	const char &operator[](size_t index_) const;
	char &operator[](size_t index_);
	bool operator==(const String &str_) const;
};

String operator+(const String &str1_, const String &str2_);
String operator+(const String &str1_, const char *str2_);
String operator+(const String &str1_, const char ch2_);
String operator+(const char *str1_, const String &str2_);
String operator+(const char ch1_, const String &str2_);

const size_t newSize = 16;

String::String()
{
	this->size = newSize;
	this->buffer = new char[newSize];
}
String::String(const char *str_)
{
	this->size = strlen(str_);
	buffer = new char[this->size + 1];
	strcpy(this->buffer, str_);
	buffer[this->size] = 0;
}
String::String(const char *str_, size_t size_)
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
String::String(const String &str_)
{
	this->size = str_.size;
	buffer = new char[this->size + 1];
	strcpy(this->buffer, str_.buffer);
	buffer[this->size] = 0;
}
String::~String()
{
	delete[] this->buffer;
}

size_t String::GetSize() const
{
	return this->size;
}
void String::Append(const String &str_)
{
	char *buffer = new char[this->size + str_.size + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_.buffer);
	this->size += str_.size;
	buffer[this->size] = 0;
	delete[] this->buffer;
	this->buffer = buffer;
}
void String::Append(const char *str_)
{
	size_t size_ = strlen(str_);
	char *buffer = new char[this->size + size_ + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_);
	this->size += size_;
	buffer[this->size] = 0;
	delete[] this->buffer;
	this->buffer = buffer;
}
void String::Append(const char *str_, size_t size_)
{
	size_t size = std::min(strlen(str_), size_);
	char *buffer = new char[this->size + size + 1];
	strcpy(buffer, this->buffer);
	strcpy(buffer + this->size, str_);
	this->size += size;
	buffer[this->size] = 0;
	delete[] this->buffer;
	this->buffer = buffer;
}
void String::Append(const char ch_)
{
	char *buffer = new char[this->size + 2];
	strcpy(buffer, this->buffer);
	buffer[this->size] = ch_;
	buffer[++this->size] = 0;
	delete[] this->buffer;
	this->buffer = buffer;
}
const char *String::GetCstr() const
{
	return this->buffer;
}

char &String::operator[](size_t index_)
{
	if (index_ >= this->size || index_ < 0)
		throw std::out_of_range("index out of range");
	return buffer[index_];
}

const char &String::operator[](size_t index_) const
{
	if (index_ >= this->size || index_ < 0)
		throw std::out_of_range("index out of range");
	return buffer[index_];
}

String operator+(const String &str1_, const String &str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const String &str1_, const char *str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const String &str1_, const char ch2_)
{
	String str(str1_);
	str.Append(ch2_);
	return str;
}
String operator+(const char *str1_, const String &str2_)
{
	String str(str1_);
	str.Append(str2_);
	return str;
}
String operator+(const char ch1_, const String &str2_)
{
	String str(ch1_, 1);
	str.Append(str2_);
	return str;
}

bool String::operator==(const String &str_) const
{
	return this->size == str_.size && !strcmp(this->buffer, str_.buffer);
}

template <class T>
class Vector
{
private:
	T *dat;
	size_t size, capacity;

private:
	void Reserve(size_t capacity_)
	{
		if (this->capacity >= capacity_)
			return;
		//T* dat_ = reinterpret_cast<T*>(malloc(sizeof(T) * capacity_));
		T *dat_ = (T *)malloc(sizeof(T) * capacity_);
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
		dat = (T *)malloc(sizeof(T) * this->capacity);
	}
	Vector(size_t size_)
	{
		this->size = size_;
		this->capacity = std::max(size_, newSize);
		dat = (T *)malloc(sizeof(T) * this->capacity);
		for (size_t i = 0; i < this->size; ++i)
			new (dat + i) T();
	}
	Vector(size_t size_, const T &dat_)
	{
		this->size = size_;
		this->capacity = std::max(size_, newSize);
		dat = (T *)malloc(sizeof(T) * this->capacity);
		for (size_t i = 0; i < this->size; ++i)
			new (dat + i) T(dat_);
	}
	Vector(const Vector &vec_)
	{
		this->size = vec_.size;
		this->capacity = vec_.capacity;
		dat = (T *)malloc(sizeof(T) * this->capacity);
		for (size_t i = 0; i < this->size; ++i)
			new (dat + i) T(vec_.dat[i]);
	}
	~Vector()
	{
		for (size_t i = 0; i < this->size; ++i)
			; //this->dat[i].~T();
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
				new (dat + size++) T();
		else
			for (size_t i = this->size; i > size_; --i)
				PopBack();
		this->size = size_;
	}
	void PushBack(const T &dat_)
	{
		if (this->size == this->capacity)
			Reserve(this->capacity + (this->capacity >> 1));
		new (dat + size++) T(dat_);
	}
	void PopBack()
	{
		--this->size;
		if (this->size < (this->capacity >> 2))
			Reserve(this->capacity >> 1);
	}
	void Append(const Vector &vec_)
	{
		if (this->capacity < this->size + vec_.size)
			Reserve(this->size + vec_.size);
		for (size_t i = 0; i < vec_.size; ++i)
			this->dat[i + this->size] = vec_.dat[i];
		this->size += vec_.size;
	}
	void Erase(const size_t &index_)
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
	T &At(size_t index_)
	{
		if (index_ >= this->size)
			throw std::out_of_range("index out of range");
		return dat[index_];
	}
	T &operator[](size_t index_)
	{
		return At(index_);
	}
	const T &At(size_t index_) const
	{
		if (index_ >= this->size)
			throw std::out_of_range("index out of range");
		return dat[index_];
	}
	const T &operator[](size_t index_) const
	{
		return At(index_);
	}
	bool operator==(const Vector &vec_)
	{
		if (this->size != vec_.size)
			return false;
		for (size_t i = 0; i < this->size; ++i)
			if (!(this->dat[i] == vec_.dat[i]))
				return false;
		return true;
	}
	bool operator!=(const Vector &vec_)
	{
		return !(*this == vec_);
	}
};

template <class T>
struct ListNode
{
	ListNode *next;
	ListNode *prev;
	T *dat;
	ListNode() : next(nullptr), prev(nullptr), dat(nullptr) {}
	ListNode(const T &dat_) : next(nullptr), prev(nullptr), dat(new T(dat_)) {}
	~ListNode() { delete dat; }
};

template <class T>
class List
{
private:
	ListNode<T> head;
	size_t size;

public:
	List() : head(), size(0)
	{
		this->head.next = &this->head;
		this->head.prev = &this->head;
	}
	List(const List &list_) : size(list_.size)
	{
		this->head.next = &this->head;
		this->head.prev = &this->head;
		ListNode<T> *newHead = &this->head, *newPtr = this->head.next;
		const ListNode<T> *oldHead = &(list_.head), *oldPtr = (list_.head).next;
		while (oldPtr != oldHead)
		{
			newPtr = new ListNode<T>();
			newPtr->dat = new T(*(oldPtr->dat));
			newPtr->prev = newHead;
			newHead->next = newPtr;
			newPtr = newPtr->next;
			newHead = newHead->next;
			oldPtr = oldPtr->next;
		}
		this->head.prev = newHead;
		newHead->next = &(this->head);
	}
	~List()
	{
		ListNode<T> *ptr = this->head.next, *cur;
		while (ptr != &(this->head))
		{
			cur = ptr;
			ptr = ptr->next;
			delete cur;
		}
	}

	void PushBack(const T &val_)
	{
		ListNode<T> *ptr = new ListNode<T>(val_);
		this->head.prev->next = ptr;
		ptr->prev = this->head.prev;
		this->head.prev = ptr;
		ptr->next = &(this->head);
		++this->size;
	}
	void PushFront(const T &val_)
	{
		ListNode<T> *ptr = new ListNode<T>(val_);
		this->head.next->prev = ptr;
		ptr->next = this->head.next;
		this->head.next = ptr;
		ptr->prev = &(this->head);
		++this->size;
	}
	void PopBack()
	{
		if (!this->size)
			throw std::out_of_range("no element to be popped");
		ListNode<T> *ptr = this->head.prev;
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete ptr;
	}
	void PopFront()
	{
		if (!this->size)
			throw std::out_of_range("no element to be popped");
		ListNode<T> *ptr = this->head.next;
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete ptr;
	}
	template <class Ty1, class EqualFunc>
	ListNode<T> *FindNode(const Ty1 &ty1_, const EqualFunc &func)
	{
		ListNode<T> *ptr = this->head.next;
		while (ptr != &(this->head))
		{
			if (func(ty1_, *(ptr->dat)))
				return ptr;
			ptr = ptr->next;
		}
		return nullptr;
	}
	void Erase(ListNode<T> *ptr_)
	{
		if (!ptr_)
			throw std::runtime_error("Nullptr");
		ptr_->prev->next = ptr_->next;
		ptr_->next->prev = ptr_->prev;
		--this->size;
		delete ptr_;
	}
};

const size_t cBeginVal = 998244353;
const size_t mulFactor = 16777619;

template <class T>
struct hash
{
	static size_t GetHash(const unsigned char *valPtr, const size_t &size)
	{
		size_t beginVal = cBeginVal;
		for (size_t i = 0; i < size; ++i)
			beginVal = (beginVal ^ valPtr[i]) * mulFactor;
		return beginVal;
	}

	size_t operator()(const T &key)
	{
		return this->GetHash(reinterpret_cast<const unsigned char *>(&key), sizeof(T));
	}
};

#include <utility>

template <class K, class V, class HashFunc = hash<K>>
class HashTable
{
private:
	Vector<List<std::pair<K, V>>> buffer;
	size_t size;

private:
	static bool cmp(const K &key_, const std::pair<K, V> &node_)
	{
		return key_ == node_.first;
	}
	ListNode<std::pair<K, V>> *_Find(const K &key_)
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
	HashTable() : size(0), buffer(newSize >> 1) {}
	HashTable(const HashTable &table_) : size(table_.size), buffer(table_.buffer) {}
	~HashTable() {}

	V *Find(const K &key_)
	{
		auto ptr = _Find(key_);
		return ptr ? &(ptr->dat->second) : nullptr;
	}
	void Insert(const K &key_, const V &value_)
	{
		auto ptr = _Find(key_);
		if (!ptr)
		{
			this->buffer.At(HashFunc()(key_) % buffer.GetSize())
				.PushFront({key_, value_});
			++size;
		}
		else
			ptr->dat->second = value_;
	}
	void Erase(const K &key_)
	{
		auto ptr = _Find(key_);
		if (!ptr)
			return;
		this->buffer.At(HashFunc()(key_) % buffer.GetSize()).Erase(ptr);
		--size;
	}
	V &operator[](const K &key_)
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

template <class K, class Ar, class V>
class Trie
{
private:
	Vector<HashTable<K, size_t>> buffer;
	HashTable<size_t, V> indexTable;

public:
	Trie() : buffer(1) {}
	Trie(const Trie &trie_)
		: buffer(trie_.buffer), indexTable(trie_.indexTable) {}
	~Trie() {}
	void Insert(const Ar &array_, const V &val_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K &nxt = array_[i];
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
	void Erase(const Ar &array_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K &nxt = array_[i];
			auto ptr = buffer[root].Find(nxt);
			if (!ptr)
				return;
			root = *ptr;
		}
		indexTable.Erase(root);
	}
	V *Find(const Ar &array_)
	{
		size_t root = 0;
		for (size_t i = 0; i < array_.GetSize(); ++i)
		{
			const K &nxt = array_[i];
			auto ptr = buffer[root].Find(nxt);
			if (!ptr)
				return nullptr;
			root = *ptr;
		}
		return indexTable.Find(root);
	}
	V *operator[](const Ar &array_)
	{
		return Find(array_);
	}
	size_t GetSize() const
	{
		return indexTable.GetSize();
	}
};

template <class T>
class Heap
{
private:
	Vector<T> buffer;

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
	Heap(const Heap &heap_) : buffer(heap_.buffer) {}
	~Heap() {}

	size_t GetSize()
	{
		return buffer.GetSize();
	}

	void Push(const T &val_)
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

	const T &GetTop()
	{
		return buffer[0];
	}
};

#include <cstdio>

struct Edge
{
	size_t w, to;
	Edge() {}
	Edge(const size_t &_w, const size_t &_to) : w(_w), to(_to) {}
	bool operator<(const Edge &e) const
	{
		return w > e.w;
	}
};
Vector<Vector<Edge>> G;
size_t edgeCount;
size_t nodeCount;

Vector<size_t> dis, pre;
Vector<bool> vis, exist;

Heap<Edge> q;

size_t dijkstra(const size_t &s, const size_t &t, Vector<int> &path)
{
	dis.Resize(G.GetSize());
	pre.Resize(G.GetSize());
	vis.Resize(G.GetSize());
	for (size_t i = 0; i < dis.GetSize(); ++i)
		dis[i] = INT_MAX;
	for (size_t i = 0; i < vis.GetSize(); ++i)
		vis[i] = 0;

	dis[s] = 0;
	q.Push(Edge(0, s));
	while (q.GetSize())
	{
		Edge e = q.GetTop();
		q.Pop();
		if (vis[e.to])
			continue;
		int u = e.to;
		vis[u] = 1;
		for (size_t i = 0; i < G[u].GetSize(); ++i)
		{
			int v = G[e.to][i].to, w = G[e.to][i].w;
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				pre[v] = u;
				q.Push(Edge(dis[v], v));
			}
		}
	}
	path.Resize(0);
	size_t cur = t;
	while (cur != s)
	{
		path.PushBack(cur);
		cur = pre[cur];
	}
	path.PushBack(cur);
	return dis[t];
}

Trie<char, String, int> mpStrToInt;
Vector<String> mpIntToStr;

void PrintPath(const Vector<int> &path)
{
	printf("path: \n");
	for (size_t i = path.GetSize() - 1; int(i) >= 0; --i)
		printf("%s%s", mpIntToStr[path[i]].GetCstr(), i ? " -> " : "\n");
}

bool LoadGraph(const char *filePath)
{
	char *buffer = new char[1 << 10];
	FILE *fp = fopen(filePath, "r");
	if (!fp)
		return printf("Can't load graph from: %s\n", filePath), false;
	fscanf(fp, "%u", &nodeCount);
	for (size_t i = 0; i < nodeCount; ++i)
	{
		fscanf(fp, "%s", buffer);
		mpStrToInt.Insert(String(buffer), i);
		mpIntToStr.PushBack(String(buffer));
	}
	exist.Resize(nodeCount);
	for (size_t i = 0; i < exist.GetSize(); ++i)
		exist[i] = true;
	;
	G.Resize(nodeCount);
	fscanf(fp, "%u", &edgeCount);
	for (size_t i = 0; i < edgeCount; ++i)
	{
		fscanf(fp, "%s", buffer);
		int u = *mpStrToInt.Find(String(buffer));
		fscanf(fp, "%s", buffer);
		int v = *mpStrToInt.Find(String(buffer));
		size_t w;
		fscanf(fp, "%u", &w);
		G[u].PushBack(Edge(w, v));
		//G[v].PushBack(Edge(w, u));
	}
	fclose(fp);
	delete[] buffer;
	return true;
}

void StoreGraph(const char *filePath)
{
	FILE *fp = fopen(filePath, "w");
	fprintf(fp, "%u\n", mpStrToInt.GetSize());
	for (size_t i = 0; i < mpIntToStr.GetSize(); ++i)
		if (exist[i])
			fprintf(fp, "%s\n", mpIntToStr[i].GetCstr());
	fprintf(fp, "%u\n", edgeCount);
	for (size_t i = 0; i < G.GetSize(); ++i)
		for (size_t j = 0; exist[i] && j < G[i].GetSize(); ++j)
			fprintf(fp, "%s %s %u\n", mpIntToStr[i].GetCstr(),
					mpIntToStr[G[i][j].to].GetCstr(), G[i][j].w);
	fclose(fp);
}

void AddPoint(const String &point)
{
	auto ptr1 = mpStrToInt.Find(point);
	if (ptr1)
		return;
	nodeCount++;
	mpStrToInt.Insert(point, mpIntToStr.GetSize());
	exist.PushBack(true);
	mpIntToStr.PushBack(point);
	G.PushBack(Vector<Edge>());
}

void DeletePoint(const String &point)
{
	const auto ptr1 = mpStrToInt.Find(point);
	if (!ptr1)
		return;
	for (size_t i = 0; i < G.GetSize(); ++i)
	{
		if (i == *ptr1)
			continue;
		Vector<int> v;
		for (size_t j = 0; j < G[i].GetSize(); ++j)
			if (G[i][j].to == *ptr1)
				v.PushBack(j);
		for (int j = v.GetSize() - 1; j >= 0; --j)
			G[i].Erase(v[j]);
		edgeCount -= v.GetSize();
	}
	edgeCount -= G[*ptr1].GetSize();
	--nodeCount;
	exist[*ptr1] = false;
	mpStrToInt.Erase(point);
}

void AddEdge(const String &from, const String &to, size_t w)
{
	AddPoint(from);
	AddPoint(to);
	G[*mpStrToInt[from]].PushBack(Edge(w, *mpStrToInt[to]));
}

void DeleteEdge(const String &from, const String &to)
{
	auto ptr1 = mpStrToInt.Find(from);
	if (!ptr1)
		return;
	auto ptr2 = mpStrToInt.Find(to);
	if (!ptr2)
		return;
	for (size_t i = 0; i < G[*ptr1].GetSize(); ++i)
		if (G[*ptr1][i].to == *ptr2)
		{
			G[*ptr1].Erase(i);
			break;
		}
	--edgeCount;
}

char op[10], buf1[1 << 4], buf2[1 << 4];
size_t w;

void PrintMenu()
{
	printf("What do you want to do?\n");
	printf("1. Load Graph\n");
	printf("2. Store Graph\n");
	printf("3. Add an edge\n");
	printf("4. Delete an edge\n");
	printf("5. Add a point\n");
	printf("6. Delete a point\n");
	printf("7. Get the shortest path\n");
	printf("press number to choose, 0 to exit\n");
}

Vector<int> p;
int main()
{
	while (1)
	{
		PrintMenu();
		scanf("%s", op);
		printf("\n");

		if (op[0] == '0')
			break;
		switch (op[0] - '0')
		{
		case 1:
			printf("Input the path of the file\n");
			scanf("%s", buf1);
			LoadGraph(buf1);
			break;

		case 2:
			printf("Input the path of the file\n");
			scanf("%s", buf1);
			StoreGraph(buf1);
			break;

		case 3:
			printf("Input the point from ans point to and weight\n");
			scanf("%s%s%u", buf1, buf2, &w);
			AddEdge(buf1, buf2, w);
			break;

		case 4:
			printf("Input the point from ans point to\n");
			scanf("%s%s", buf1, buf2);
			DeleteEdge(buf1, buf2);
			break;

		case 5:
			printf("Input the point\n");
			scanf("%s", buf1);
			AddPoint(buf1);
			break;

		case 6:
			printf("Input the point\n");
			scanf("%s", buf1);
			DeletePoint(buf1);
			break;

		case 7:
			printf("Input the point from ans point to\n");
			scanf("%s%s", buf1, buf2);
			{
				auto ptr1 = mpStrToInt[buf1];
				auto ptr2 = mpStrToInt[buf2];
				if (!ptr1 || !ptr2)
				{
					printf("not such point on the graph\n");
					break;
				}
				printf("%u\n", dijkstra(
								   *ptr1, *ptr2, p));
				PrintPath(p);
				break;
			}

		default:
			printf("Order not found\n");
		}

		system("pause");
		system("cls");
	}
	return 0;
}