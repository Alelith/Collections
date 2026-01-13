#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template<class T>
class Stack {
public:
	using value_type		= T;
	using size_type			= unsigned long;
	using reference			= T&;
	using const_reference	= const T&;
	using pointer			= T*;
	using const_pointer		= const T*;
	using iterator			= T*;
	using const_iterator	= const T*;

	Stack() noexcept;
	Stack(size_type count, const T &value);
	Stack(const Stack &other);
	Stack(Stack &&other) noexcept;
	~Stack();

	reference operator[](size_type index);
	Stack &operator=(const Stack &other);
	Stack &operator=(Stack &&other) noexcept;

	void clear() noexcept;
	const_reference at(size_type index) const;
	void push(const_reference value);
	value_type pop();

	size_type size() const noexcept;
	size_type capacity() const noexcept;
	bool empty() const noexcept;
	pointer data() noexcept;
	const_pointer data() const noexcept;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;

private:
	pointer		data_;
	size_type	size_;
	size_type	capacity_;

	void reserve(size_type new_cap);
	void shrink_to_fit();
};

#include "stack.tpp"

#endif // STACK_HPP
