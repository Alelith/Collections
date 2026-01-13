#ifndef QUEUE_HPP
#define QUEUE_HPP

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

#include "src/queue.tpp"

#endif // QUEUE_HPP
