/**
 * @file stack.hpp
 * @brief Stack container with LIFO (Last-In-First-Out) operations
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

/**
 * @class Stack
 * @brief LIFO stack container using dynamic array
 * 
 * @details Implements a stack data structure where elements are added
 * and removed from the same end (top). Follows Last-In-First-Out
 * principle. Implemented using dynamic array for efficient memory
 * usage and cache locality.
 * 
 * @tparam T Type of elements stored in the stack
 * 
 * @ingroup linear_containers
 */
template<class T>
class Stack {
public:
	using value_type		= T;              ///< Type of stored elements
	using size_type			= unsigned long;  ///< Type for sizes and indices
	using reference			= T&;             ///< Reference to element
	using const_reference	= const T&;       ///< Const reference to element
	using pointer			= T*;             ///< Pointer to element
	using const_pointer		= const T*;       ///< Const pointer to element
	using iterator			= T*;             ///< Iterator type
	using const_iterator	= const T*;       ///< Const iterator type

	Stack() noexcept;
	Stack(size_type count, const T &value);
	Stack(const Stack &other);
	Stack(Stack &&other) noexcept;
	template <class Container>
	Stack(const Container& other);
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
	pointer		data_;      ///< Pointer to dynamically allocated array
	size_type	size_;      ///< Number of elements currently stored
	size_type	capacity_;  ///< Current allocated capacity

	void reserve(size_type new_cap);
	void shrink_to_fit();
};

#include "internal/stack.tpp"

#endif
