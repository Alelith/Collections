/**
 * @file vector.hpp
 * @brief Dynamic array container with automatic memory management
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

/**
 * @defgroup linear_containers Linear Container Module
 * @brief Sequential container data structures
 * 
 * @details This module provides efficient implementations of fundamental
 * linear data structures including vectors, linked lists, stacks,
 * queues, and deques. All containers are template-based to support
 * generic programming with any data type.
 * 
 * @section module_features_sec Features
 * - Dynamic vectors with automatic capacity management
 * - Single and double linked lists with efficient insertion
 * - Stack (LIFO) and Queue (FIFO) adapters
 * - Deque with efficient front and back operations
 * - STL-compatible iterators and type aliases
 * - Exception-safe operations with proper RAII
 * - Move semantics for optimal performance
 * 
 * @section module_usage_sec Usage
 * All containers provide common interfaces: constructors for various
 * initialization scenarios, element access methods, modifiers, and
 * capacity queries. Iterators enable range-based operations and STL
 * algorithm compatibility.
 */

/**
 * @class Vector
 * @brief Dynamic array with automatic capacity management
 * 
 * @details Implements a resizable array that automatically grows as
 * elements are added. Provides random access to elements in constant
 * time and efficient addition at the end. Memory is allocated
 * dynamically and grows exponentially to amortize allocation costs.
 * 
 * @tparam T Type of elements stored in the vector
 * 
 * @ingroup linear_containers
 */
template<class T>
class Vector {
public:
	using value_type		= T;              ///< Type of stored elements
	using size_type			= unsigned long;  ///< Type for sizes and indices
	using reference			= T&;             ///< Reference to element
	using const_reference	= const T&;       ///< Const reference to element
	using pointer			= T*;             ///< Pointer to element
	using const_pointer		= const T*;       ///< Const pointer to element
	using iterator			= T*;             ///< Iterator type
	using const_iterator	= const T*;       ///< Const iterator type

	Vector() noexcept;
	Vector(size_type count, const T &value);
	Vector(const Vector &other);
	Vector(Vector &&other) noexcept;
	template <class Container>
	Vector(const Container& other);
	~Vector();

	reference operator[](size_type index);
	Vector &operator=(const Vector &other);
	Vector &operator=(Vector &&other) noexcept;

	void clear() noexcept;
	const_reference at(size_type index) const;
	void add(const_reference value);
	pointer insert(size_type index, const_reference value);
	value_type erase(size_type index);

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

#include "src/vector.tpp"

#endif
