#pragma once
#include <iostream>

template<class T>
class Queue {
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

	Queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

	Queue(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
		for (size_type i = 0; i < count; i++)
			push_back(value);
	}

	Queue(const Queue &other) : head_(nullptr), tail_(nullptr), size_(0) {
		pointer cur = other.head_;
		while (cur) {
			push_back(cur->data);
			cur = cur->next;
		}
	}

	Queue(Queue &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
		other.head_ = nullptr;
		other.size_ = 0;
	}

	~Queue() {
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

	Queue &operator=(const Queue &other) {
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

	Queue &operator=(Queue &&other) {
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

	void enqueue(const_reference value) {
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

	value_type dequeue() {
		if (head_ == nullptr) throw std::out_of_range("erase index out of range");
		value_type value = tail_->data;
		if (head_ == tail_) {
			delete head_;
			head_ = nullptr;
		}
		pointer previous = tail_->prev;
		delete tail_;
		tail_ = previous;
		--size_;
		return value;
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