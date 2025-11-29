#pragma once
#include <iostream>

template<class T>
class Queue {
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

	Queue() noexcept;
	Queue(size_type count, const T &value);
	Queue(const Queue &other);
	Queue(Queue &&other) noexcept;
	~Queue();

	reference operator[](size_type index);
	Queue &operator=(const Queue &other);
	Queue &operator=(Queue &&other);

	void clear() noexcept;
	const_reference at(size_type index) const;
	void enqueue(const_reference value);
	value_type dequeue();

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
Queue<T>::Node::Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}

template<class T>
Queue<T>::Queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template<class T>
Queue<T>::Queue(size_type count, const T &value) : head_(nullptr), tail_(nullptr), size_(0) {
	for (size_type i = 0; i < count; i++)
		enqueue(value);
}

template<class T>
Queue<T>::Queue(const Queue &other) : head_(nullptr), tail_(nullptr), size_(0) {
	pointer cur = other.head_;
	while (cur) {
		enqueue(cur->data);
		cur = cur->next;
	}
}

template<class T>
Queue<T>::Queue(Queue &&other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
	other.head_ = nullptr;
	other.size_ = 0;
}

template<class T>
Queue<T>::~Queue() {
	clear();
}

template<class T>
typename Queue<T>::reference Queue<T>::operator[](size_type index) {
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
Queue<T> &Queue<T>::operator=(const Queue &other) {
	if (this != &other) {
		clear();
		pointer cur = other.head_;
		while (cur) {
			enqueue(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

template<class T>
Queue<T> &Queue<T>::operator=(Queue &&other) {
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
void Queue<T>::clear() noexcept {
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
typename Queue<T>::const_reference Queue<T>::at(size_type index) const {
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
void Queue<T>::enqueue(const_reference value) {
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
typename Queue<T>::value_type Queue<T>::dequeue() {
	if (head_ == nullptr) throw std::out_of_range("Empty queue");
	value_type value = head_->data;
	if (head_ == tail_) {
		delete head_;
		head_ = nullptr;
		tail_ = nullptr;
		--size_;
		return value;
	}
	pointer next = head_->next;
	delete head_;
	head_ = next;
	if (head_) head_->prev = nullptr;
	--size_;
	return value;
}

template<class T>
typename Queue<T>::size_type Queue<T>::size() const noexcept { return size_; }

template<class T>
bool Queue<T>::empty() const noexcept { return size_ == 0; }

template<class T>
typename Queue<T>::pointer Queue<T>::head() noexcept { return head_; }

template<class T>
typename Queue<T>::const_pointer Queue<T>::head() const noexcept { return head_; }

template<class T>
typename Queue<T>::pointer Queue<T>::tail() noexcept { return tail_; }

template<class T>
typename Queue<T>::const_pointer Queue<T>::tail() const noexcept { return tail_; }