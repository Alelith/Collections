#pragma once

template<class T>
class LinkedList {
public:
	struct Node {
		T			data;
		Node		*next;

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

	LinkedList() noexcept : head_(nullptr), size_(0) {}

	LinkedList(size_type count, const T &value) : size_(count) {
		for (int i = 0; i < count; i++)
			push_back(value);
	}

	LinkedList(const LinkedList &other) : head_(nullptr), size_(0) {
		pointer cur = other.head_;
		while (cur) {
			push_back(cur);
			cur = cur->next;
		}
	}

	LinkedList(LinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
		other.head_ = nullptr;
		other.size_ = 0;
	}

	~LinkedList() {
		clear();
	}

private:
	pointer		head_;
	size_type	size_;
};