/**
 * @file deque.hpp
 * @brief Double-ended queue with efficient front and back operations
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <iostream>

/**
 * @class Deque
 * @brief Double-ended queue using circular buffer
 * 
 * @details Implements a deque (double-ended queue) allowing efficient
 * insertion and deletion at both ends. Uses circular buffer with
 * dynamic resizing for optimal space and time complexity. Provides
 * random access to elements.
 * 
 * @tparam T Type of elements stored in the deque
 * 
 * @ingroup linear_containers
 */
template<class T>
class Deque {
public:
	/**
	 * @class Iterator
	 * @brief Forward iterator for circular buffer traversal
	 * 
	 * @details Provides sequential access to deque elements handling
	 * the circular nature of the underlying buffer transparently.
	 */
	class Iterator {
	private:
		T* data_;              ///< Pointer to buffer
		size_t capacity_;      ///< Buffer capacity
		size_t head_;          ///< Head index in buffer
		size_t current_index_; ///< Current logical index
		size_t position_;      ///< Current position in iteration

	public:
		Iterator(T* data, size_t capacity, size_t head, size_t position);

		T& operator*() const;
		Iterator& operator++();
		bool operator!=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
	};

	using value_type		= T;              ///< Type of stored elements
	using size_type			= unsigned long;  ///< Type for sizes and indices
	using reference			= T&;             ///< Reference to element
	using const_reference	= const T&;       ///< Const reference to element
	using pointer			= T*;             ///< Pointer to element
	using const_pointer		= const T*;       ///< Const pointer to element
	using iterator			= Iterator;       ///< Iterator type
	using const_iterator	= const Iterator; ///< Const iterator type

	Deque();
	Deque(size_type count, const T &value);
	Deque(const Deque &other);
	Deque(Deque &&other) noexcept;
	template <class Container>
	Deque(const Container& other);
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
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;

private:
	pointer		data_;      ///< Pointer to circular buffer
	size_type	size_;      ///< Number of elements in deque
	size_type	capacity_;  ///< Current buffer capacity
	size_type	head_;      ///< Index of front element
	size_type	tail_;      ///< Index of back element

	void reserve();
	void shrink_to_fit();
	void order();
};

#include "src/deque.tpp"

#endif
