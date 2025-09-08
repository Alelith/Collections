#pragma once
#include <iostream>

template<class T>
class LinkedList {
public:
	struct Node {
		T			data;
		Node		*next;

		Node(const T &value) : data(value), next(nullptr) {}
	};

	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= Node*;
	using const_pointer		= const Node*;
	using iterator			= Node*;
	using const_iterator	= const Node*;

	LinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

	LinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
		for (size_type i = 0; i < count; i++)
			push_back(value);
	}

	LinkedList(const LinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
		pointer cur = other.head_;
		while (cur) {
			push_back(cur->data);
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

	reference operator[](size_type index) {
		if (index >= size_)
			throw std::out_of_range("Index out of range");
		pointer cur = head_;
		for (size_type i = 0; i < index; i++)
			cur = cur->next;
		return cur->data;
	}

	LinkedList &operator=(const LinkedList &other) {
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

	LinkedList &operator=(LinkedList &&other) {
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
		pointer cur = head_;
		for (size_type i = 0; i < index; i++)
			cur = cur->next;
		return cur->data;
	}

	void add(const_reference value) {
		pointer new_node = new Node(value);
		if (!tail_ && !head_) {
			tail_ = new_node;
			head_ = new_node;
		}
		else {
			tail_->next = new_node;
			tail_ = new_node;
		}
		size_++;
	}

	pointer insert(size_type index, const_reference value) {
		if (index > size_) throw std::out_of_range("insert index out of range");
		pointer new_node = new Node(value);
		if (index == 0) { // Insert at head
			new_node->next = head_;
			head_ = new_node;
			if (size_ == 0) tail_ = new_node;
		}
		else {
			pointer cur = head_;
			for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
			new_node->next = cur->next;
			cur->next = new_node;
			if (new_node->next == nullptr) tail_ = new_node;
		}
		size_++;
		return new_node;
	}

	value_type erase(size_type index) {
		if (index >= size_ || head_ == nullptr) throw std::out_of_range("erase index out of range");
		value_type val;
		if (index == 0) {
			pointer to_delete = head_;
			val = to_delete->data;
			head_ = head_->next;
			if (tail_ == to_delete) tail_ = nullptr;
			delete to_delete;
			size_--;
			return val;
		}
		pointer cur = head_;
		for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
		pointer to_delete = cur->next;
		val = to_delete->data;
		cur->next = to_delete->next;
		if (tail_ == to_delete)
			tail_ = cur;
		delete to_delete;
		size_--;
		return val;
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