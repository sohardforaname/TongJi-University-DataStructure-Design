#pragma once

#include <stdexcept>

template<class T>
struct ListNode
{
	ListNode* next;
	ListNode* prev;
	T* dat;
	ListNode() : next(nullptr), prev(nullptr), dat(nullptr) {}
	ListNode(const T& dat_) : next(nullptr), prev(nullptr), dat(new T(dat_)) {}
	~ListNode() { delete dat; }
};

template<class T>
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
	List(const List& list_) : size(list_.size)
	{
		this->head.next = &this->head;
		this->head.prev = &this->head;
		ListNode<T>* newHead = &this->head, * newPtr = this->head.next;
		const ListNode<T>* oldHead = &(list_.head), * oldPtr = (list_.head).next;
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
		ListNode<T>* ptr = this->head.next, * cur;
		while (ptr != &(this->head))
		{
			cur = ptr;
			ptr = ptr->next;
			delete cur;
		}
	}

	void PushBack(const T& val_)
	{
		ListNode<T>* ptr = new ListNode<T>(val_);
		this->head.prev->next = ptr;
		ptr->prev = this->head.prev;
		this->head.prev = ptr;
		ptr->next = &(this->head);
		++this->size;
	}
	void PushFront(const T& val_)
	{
		ListNode<T>* ptr = new ListNode<T>(val_);
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
		ListNode<T>* ptr = this->head.prev;
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete ptr;
	}
	void PopFront()
	{
		if (!this->size)
			throw std::out_of_range("no element to be popped");
		ListNode<T>* ptr = this->head.next;
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete ptr;
	}
	template<class Ty1, class EqualFunc>
	ListNode<T>* FindNode(const Ty1& ty1_, const EqualFunc& func)
	{
		ListNode<T>* ptr = this->head.next;
		while (ptr != &(this->head))
		{
			if (func(ty1_, *(ptr->dat)))
				return ptr;
			ptr = ptr->next;
		}
		return nullptr;
	}
	void Erase(ListNode<T>* ptr_)
	{
		if (!ptr_)
			throw std::runtime_error("Nullptr");
		ptr_->prev->next = ptr_->next;
		ptr_->next->prev = ptr_->prev;
		--this->size;
		delete ptr_;
	}

};