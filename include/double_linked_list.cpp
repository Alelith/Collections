#pragma once
#include <iostream>

template<class T>
class DoubleLinkedList {
public:
	struct Node {
		T			data;
		Node		*next;
		Node		*prev;

		Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
	};

	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= Node*;
	using const_pointer		= const Node*;
	using iterator			= Node*;
	using const_iterator	= const Node*;

	DoubleLinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

	DoubleLinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
		for (size_type i = 0; i < count; i++)
			push_back(value);
	}

	DoubleLinkedList(const DoubleLinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
		pointer cur = other.head_;
		while (cur) {
			push_back(cur->data);
			cur = cur->next;
		}
	}

	DoubleLinkedList(DoubleLinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
		other.head_ = nullptr;
		other.size_ = 0;
	}

	~DoubleLinkedList() {
		clear();
	}

	reference operator[](size_type index) {
		pointer cur;
		if (index <= size_ / 2) {
			cur = head_;
			for (size_type i = 0; i < index; i++)
				cur = cur->next;
		}
		else {
			cur = tail_;
			for (size_type i = size_ - 1; i > index; i--)
				cur = cur->prev;
		}
		return cur->data;
	}

	DoubleLinkedList &operator=(const DoubleLinkedList &other) {
		if (this != &other) {
			clear();
			pointer cur = other.head_;
			while (cur) {
				push_back(cur->data);
				cur = cur->next;
			}
		}
		return *this;
	}

	DoubleLinkedList &operator=(DoubleLinkedList &&other) {
		if (this != &other) {
			clear();
			head_ = other.head_;
			tail_ = other.tail_;
			size_ = other.size_;
			other.head_ = nullptr;
			other.tail_ = nullptr;
			other.size_ = 0;
		}
		return *this;
	}

	void push_back(const_reference value) {
		pointer new_node = new Node(value);
		if (!tail_ && !head_) {
			tail_ = new_node;
			head_ = new_node;
		}
		else {
			tail_->next = new_node;
			new_node->prev = tail_;
			tail_ = new_node;
		}
		size_++;
	}

	void pop_back() {
		if (!tail_) return;
		if (head_ == tail_) {
			delete tail_;
			head_ = tail_ = nullptr;
		}
		else {
			pointer prev = tail_->prev;
			delete tail_;
			tail_ = prev;
			tail_->next = nullptr;
		}
		size_--;
	}

	void clear() noexcept {
		pointer cur = head_;
		while (cur) {
			pointer temp = cur->next;
			delete cur;
			cur = temp;
		}
		head_ = nullptr;
		tail_ = nullptr;
		size_ = 0;
	}

	const_reference at(size_type index) const {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		pointer cur;
		if (index <= size_ / 2) {
			cur = head_;
			for (size_type i = 0; i < index; i++)
				cur = cur->next;
		}
		else {
			cur = tail_;
			for (size_type i = size_; i > index; i--)
				cur = cur->prev;
		}
		return cur->data;
	}

	size_type size() const noexcept { return size_; }
	bool empty() const noexcept { return size_ == 0; }
	pointer head() noexcept { return head_; }
	const_pointer head() const noexcept { return head_; }
	pointer tail() noexcept { return tail_; }
	const_pointer tail() const noexcept { return tail_; }

private:
	pointer		head_;
	pointer		tail_;
	size_type	size_;
};