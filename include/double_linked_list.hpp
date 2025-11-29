#pragma once
#include <iostream>

template<class T>
class DoubleLinkedList {
public:
	struct Node {
		T			data;
		Node		*next;
		Node		*prev;

		Node(const T &value);
	};

	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= Node*;
	using const_pointer		= const Node*;
	using iterator			= Node*;
	using const_iterator	= const Node*;

	DoubleLinkedList() noexcept;
	DoubleLinkedList(size_type count, const T &value);
	DoubleLinkedList(const DoubleLinkedList &other);
	DoubleLinkedList(DoubleLinkedList &&other) noexcept;
	~DoubleLinkedList();

	reference operator[](size_type index);
	DoubleLinkedList &operator=(const DoubleLinkedList &other);
	DoubleLinkedList &operator=(DoubleLinkedList &&other);

	void clear() noexcept;
	const_reference at(size_type index) const;
	void add(const_reference value);
	pointer insert(size_type index, const_reference value);
	value_type erase(size_type index);

	size_type size() const noexcept;
	bool empty() const noexcept;
	pointer head() noexcept;
	const_pointer head() const noexcept;
	pointer tail() noexcept;
	const_pointer tail() const noexcept;

private:
	pointer		head_;
	pointer		tail_;
	size_type	size_;
};

template<class T>
DoubleLinkedList<T>::Node::Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		add(value);
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		add(cur->data);
		cur = cur->next;
	}
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

template<class T>
typename DoubleLinkedList<T>::reference DoubleLinkedList<T>::operator[](size_type index) {
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
		for (size_type i = size_ - 1; i > index; i--)
			cur = cur->prev;
	}
	return cur->data;
}

template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(const DoubleLinkedList &other) {
	if (this != &other) {
		clear();
		pointer cur = other.head_;
		while (cur) {
			add(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

template<class T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(DoubleLinkedList &&other) {
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

template<class T>
void DoubleLinkedList<T>::clear() noexcept {
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

template<class T>
typename DoubleLinkedList<T>::const_reference DoubleLinkedList<T>::at(size_type index) const {
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
		for (size_type i = size_ - 1; i > index; i--)
			cur = cur->prev;
	}
	return cur->data;
}

template<class T>
void DoubleLinkedList<T>::add(const_reference value) {
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

template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::insert(size_type index, const_reference value) {
	if (index > size_) throw std::out_of_range("insert index out of range");
	pointer new_node = new Node(value);
	if (index == 0) {
		new_node->next = head_;
		if (head_) head_->prev = new_node;
		head_ = new_node;
		if (size_ == 0) tail_ = new_node;
	}
	else if (index == size_) {
		new_node->prev = tail_;
		if (tail_) tail_->next = new_node;
		tail_ = new_node;
		if (size_ == 0) head_ = new_node;
	}
	else {
		pointer cur = head_;
		for (size_type i = 0; i < index - 1; ++i) cur = cur->next;
		new_node->next = cur->next;
		new_node->prev = cur;
		cur->next->prev = new_node;
		cur->next = new_node;
	}
	size_++;
	return new_node;
}

template<class T>
typename DoubleLinkedList<T>::value_type DoubleLinkedList<T>::erase(size_type index) {
	if (index >= size_ || head_ == nullptr) throw std::out_of_range("erase index out of range");
	value_type val;
	if (index == 0) {
		pointer to_delete = head_;
		val = to_delete->data;
		head_ = head_->next;
		if (head_) head_->prev = nullptr;
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
	if (to_delete->next) 
		to_delete->next->prev = cur;
	if (tail_ == to_delete)
		tail_ = cur;
	delete to_delete;
	size_--;
	return val;
}

template<class T>
typename DoubleLinkedList<T>::size_type DoubleLinkedList<T>::size() const noexcept { return size_; }

template<class T>
bool DoubleLinkedList<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::head() noexcept { return head_; }

template<class T>
typename DoubleLinkedList<T>::const_pointer DoubleLinkedList<T>::head() const noexcept { return head_; }

template<class T>
typename DoubleLinkedList<T>::pointer DoubleLinkedList<T>::tail() noexcept { return tail_; }

template<class T>
typename DoubleLinkedList<T>::const_pointer DoubleLinkedList<T>::tail() const noexcept { return tail_; }