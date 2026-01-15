#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <iostream>

template<class T>
class Deque {
public:
	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= T*;
	using const_pointer		= const T*;
	using iterator			= T*;
	using const_iterator	= const T*;

	Deque();
	Deque(size_type count, const T &value);
	Deque(const Deque &other);
	Deque(Deque &&other) noexcept;
	~Deque();

	reference operator[](size_type index);
	Deque &operator=(const Deque &other);
	Deque &operator=(Deque &&other) noexcept;

	void clear() noexcept;
	const_reference at(size_type index) const;
	void push_back(const_reference value);
	void push_front(const_reference value);
	value_type pop_back();
	value_type pop_front();

	size_type size() const noexcept;
	size_type capacity() const noexcept;
	size_type head() const noexcept;
	size_type tail() const noexcept;
	bool empty() const noexcept;
	pointer data() noexcept;
	const_pointer data() const noexcept;

private:
	pointer		data_;
	size_type	size_;
	size_type	capacity_;
	size_type	head_;
	size_type	tail_;

	void reserve();
	void shrink_to_fit();
	void order();
};

#include "internal/deque.tpp"

#endif // DEQUE_HPP
